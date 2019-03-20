//
//  AutoController.cpp
//  battleheart
//
//  Created by finalObject on 2019/1/30.
//

#include "AutoController.hpp"
#include "Hostility.hpp"
#include "BaseRole.hpp"
#include "DataManager.hpp"
#include "AbilityMaster.hpp"
AutoController * AutoController::create(BaseRole* thisRole,vector<BaseRole *> *roles){
    AutoController * autoController = new AutoController();
    if(autoController && autoController->init(thisRole,roles)){
        autoController->autorelease();
    }else{
        CC_SAFE_DELETE(autoController);
    }
    return autoController;
}
bool AutoController::init(BaseRole* thisRole,vector<BaseRole *> *roles){
    this->roles = roles;
    this->thisRole = thisRole;
    this->targetRole = nullptr;
    this->targetAbility = 0;

    //启动定时器，1s执行一次
    this->schedule(CC_SCHEDULE_SELECTOR(AutoController::statesUpdate), 1/1);
    return true;
}
void AutoController::statesUpdate(float dt){
    //首先确定目标，如果被控制了怎么样，完全auto怎么样
    if (thisRole->getIsControl()==true){
        //不设置目标
    }else{
        BaseRole * host = Hostility::getInstance()->getTarget(this->thisRole);
        if (host!=nullptr){
            this->targetRole = host;
        }
    }
    //只要没有找到合适的目标，不做操作
    if(this->targetRole==nullptr){return;}
    if(AbilityMaster::getInstance()->areYouDead(this->targetRole)){
        this->targetRole = nullptr;
        return; 
    }
    
    //如果是完全控制的机器人，获取一个需要使用的技能
    if(this->thisRole->getIsControl() == false){this->targetAbility = getAbility();}
    
    //如果没有合适的攻击手段，不做操作
    if(this->targetAbility==0){return;}
    
    auto dis = sqrt(pow(thisRole->getPositionX()-targetRole->getPositionX(),2)+pow((thisRole->getPositionY()*Y_SCALE-targetRole->getPositionY()*Y_SCALE),2))*1.0;
    if(dis*RANGE_SCALE<thisRole->dataManager->getSingleData(ATKRANGE)){
        AbilityMaster::getInstance()->spell(thisRole, 'a', targetRole);
        this->targetAbility = 0;
    }else{
        AbilityMaster::getInstance()->spell(thisRole, 'x', targetRole->getPosition());
    }
    
    return;
}
int AutoController::getAbility(){
    return ATTACK;
}
void AutoController::purge(){
    roles= nullptr;
    thisRole= nullptr;
    targetRole =nullptr;
    this->unschedule(CC_SCHEDULE_SELECTOR(AutoController::statesUpdate));
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
