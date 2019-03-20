//
//  BaseRole.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#include "BaseRole.hpp"
#include "StandAbility.hpp"
#include "BaseAbility.hpp"
#include "MoveAbility.hpp"
#include "BloodBar.hpp"
#include "AbilityMaster.hpp"
#include "FlyBlood.hpp"
#include "BaseController.hpp"
#include "Indicator.hpp"
#include "DataManager.hpp"
#include "Hostility.hpp"
#include "AutoController.hpp"
BaseRole * BaseRole::createWithProperty(const std::string& plist,BaseController * controller){
    BaseRole * baseRole = new BaseRole();
    if(baseRole && baseRole->init(plist,controller)){
        baseRole->autorelease();
    }
    else{
        CC_SAFE_DELETE(baseRole);
        return nullptr;
    }
    return baseRole;
}
bool BaseRole::init(const std::string& plist,BaseController * controller){
    
    //储存控制器
    this->controller = controller;
    this->autoController = AutoController::create(this,controller->roles);
    this->addChild(this->autoController);
    //找一个合适的id
    setId();
    
    //初始化属性
    ValueMap tmpData = FileUtils::getInstance()->getValueMapFromFile(plist);
    dataManager = DataManager::create(tmpData);
    this->addChild(dataManager);
    //配置表中读取数据
    this->setSizeScale(tmpData["sizeScale"].asFloat());
    this->setPlace(tmpData["place"].asInt());
    this->setForce(tmpData["force"].asInt());
    this->setRoleName(tmpData["roleName"].asString());
    this->setRoleType(tmpData["roleType"].asString());
    this->setWeight(tmpData["weight"].asInt());
    this->setAtkEffectFrame(tmpData["atkEffectFrame"].asInt());


 
    //初始化指示器
    indicator = Indicator::create(this);
    this->addChild(indicator);
    
    //初始化身体
    body = Sprite::create();
    body->setScale(this->getSizeScale());
    this->addChild(body);
    
    
    
    //初始化血条
    bloodBar = BloodBar::create(this);
    this->addChild(bloodBar);
    
    
    
    
    //初始化id条
    nameLabel = Label::createWithSystemFont(this->getRoleName(), "", 15);
    nameLabel->setPosition(Vec2(0,bloodBar->getPositionY()+bloodBar->getBarHeight()+bloodBar->shiftBar.y+10));
    switch (getForce()) {
        case FORCE_0:
            nameLabel->setColor(Color3B(51, 153, 255));
            break;
        case FORCE_1:
            nameLabel->setColor(Color3B(204, 51, 51));
            break;
        case FORCE_2:
            nameLabel->setColor(Color3B(255, 255, 0));
            break;
        default:
            break;
    }
    
    this->addChild(nameLabel);

    //初始化技能
    //站立
    auto abilityMaster = AbilityMaster::getInstance();
    abilityMaster->addAbilityById(STAND, this, 's');
    
    //移动
    abilityMaster->addAbilityById(MOVE, this, 'x');
    //普通攻击
    abilityMaster->addAbilityById(ATTACK, this, 'a');

    //默认没有被选择
    this->setIsFocus(false);
    this->setIsControl(false);
    //初始化技能状态
    this->setStopLovel(0);
    this->setRecentAbility(STAND);
    //开始站立
    abilityMaster->standMap.at(getId())->start();

    

    
    
    
    return true;
}
void BaseRole::setId(){
    for(int i=0;i<ROLES_MAXNUM;i++){
        bool isOk = true;
        for(int j=0;j<this->controller->roles->size();j++){
            if(this->controller->roles->at(j)->getId()==i){
                isOk=false;
            }
        }
        if(isOk==true){
            this->setId(i);
            return;
        }
    }
    CCLOG("too many roles");
    return;
}
bool BaseRole::getHit(int type,int damage,BaseRole * fromWho){
    //这里的damage已经是面板伤害了，对方能力已经修正到这个damage上了
    //然后没有物理穿透和法术穿透
    //闪避判断
    srand(time(0));
    if (rand()%PER_NUM<dataManager->getSingleData(DODGE)){
        damage=0;
    }
    //对damage进行修正进行修正
    switch (type) {
        case AD:
            damage = damage *100/(100+dataManager->getSingleData(ARM));
            break;
        case AP:
            damage = damage *100/(100+dataManager->getSingleData(ORI));
            break;
        case AD_CRIT:
            damage = damage *100/(100+dataManager->getSingleData(ARM));
            break;
        case AP_CRIT:
            damage = damage *100/(100+dataManager->getSingleData(ORI));
            break;
        case REAL:
            break;
        default:
            CCLOG("what?");
            break;
    }
    //增加仇恨,这里是伤害，奶的话，暂时还没有加入
    if (damage>=0){
        Hostility::getInstance()->addHostilityByHit(this, fromWho, damage, DEFAULT_DELAYTIME);
    }
    
    //扣血
    dataManager->setNowHp(dataManager->getNowHp()-damage);
    //启动飞血特效
    FlyBlood  * flyBlood = FlyBlood::create(type, damage);
    flyBlood->setPositionY(this->getPlace()*3);
    flyBlood->setPositionX(this->getPlace());
    this->addChild(flyBlood);
    flyBlood->start();
    //判断是死是活
    if (dataManager->getNowHp()<=0){
        getKilled();
        return true;
    }else{
        //重新出发站立
        if(this->getStopLovel()<1&&this->recentAbility!=MOVE){
            AbilityMaster::getInstance()->standMap.at(getId())->start();
        }
        //貌似不需要更新，因为不会改变别的东西，只是改变血量
        //defense->updatePowerData();
        return false;
    }

    
}
void BaseRole::getKilled(){
    //先从abiliMaster中删除这个角色，他现在已经无法释放技能了
    AbilityMaster::getInstance()->removeRole(this);
    //删除别人对她的仇恨
    Hostility::getInstance()->clearHostilityById(this->getId());
    //删除自动控制器
    this->autoController->purge();
    this->autoController = nullptr;
    //删除属性
    this->dataManager->purge();
    //删除身体
    this->body->stopAllActions();
    this->body->removeAllChildrenWithCleanup(true);
    this->body->removeFromParent();
    //删除血条
    this->bloodBar->purge();
    //删除指示器
    this->indicator->purge();
    //如果有控制器，告诉控制器死了
    if(this->getIsControl()){this->controller->setThisRole(nullptr);}
    if(this->getIsFocus()){this->controller->setTargetRole(nullptr);}
    
    //从所有角色中删除自己
    vector<BaseRole *>::iterator it=this->controller->roles->begin();
    while( it<this->controller->roles->end())
        
    {
        auto index =distance(this->controller->roles->begin(),it);
        auto tmpRole = this->controller->roles->at(index);
        if (tmpRole->getId()==this->getId())
        {
            this->controller->roles->erase(it);
            break;
        }
        it++;
        
    }
    //删除其他东西
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
void BaseRole::updateNameLabel(){
    nameLabel->setString(this->getRoleName());
    switch (getForce()) {
        case FORCE_0:
            nameLabel->setColor(Color3B(51, 153, 255));
            break;
        case FORCE_1:
            nameLabel->setColor(Color3B(204, 51, 51));
            break;
        case FORCE_2:
            nameLabel->setColor(Color3B(255, 255, 0));
            break;
        default:
            break;
    }
}
