//
//  AttackAbility.cpp
//  battleheart
//
//  Created by finalObject on 2018/12/27.
//

#include "AttackAbility.hpp"
#include "BaseRole.hpp"
#include "StandAbility.hpp"
#include "AbilityMaster.hpp"
#include "DataManager.hpp"
#include <time.h>


AttackAbility * AttackAbility::create(BaseRole * thisRole){
    AttackAbility * attackAbility = new AttackAbility();
    if(attackAbility && attackAbility->init(thisRole)){
        attackAbility->autorelease();
    }else{
        CC_SAFE_DELETE(attackAbility);
    }
    return attackAbility;
}
bool AttackAbility::init(BaseRole * thisRole){
    this->thisRole = thisRole;
    this->setAbilityName("attack");
    this->setType(NEED_ROLE);//需要任务
    this->setStopLevel(1);//略高
    this->setId(ATTACK);
    //准备动画
    auto frameCache = SpriteFrameCache::getInstance();
    auto plistPath =String::createWithFormat("animation//%s//%s_%s.plist",thisRole->getRoleType().data(),thisRole->getRoleType().data(),this->getAbilityName().data());
    frameCache->addSpriteFramesWithFile(plistPath->getCString());
    //frameCache->addSpriteFramesWithFile("knight/knight_default.plist");
    Vector<SpriteFrame*> vec;
    for (int i=1;i<=18;i++){
        auto name = String::createWithFormat("%s_%s_%d.png",thisRole->getRoleType().data(),this->getAbilityName().data(),i);
        vec.pushBack(frameCache->getSpriteFrameByName(name->getCString()));
    }
    animation = Animation::createWithSpriteFrames(vec);
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(true);
    animation->retain();


    this->retain();
    
    return true;
}
void AttackAbility::start(BaseRole* targetRole){
    
    //攻击打断等级也很低
    if (thisRole->getStopLovel()<1&&thisRole->getRecentAbility()!=ATTACK){
        this->targetRole = targetRole;
        //制作攻击动画的频率
        animation->setDelayPerUnit(0.05f/(thisRole->dataManager->getSingleData(ATKSPD)*1.0/PER_NUM));

        auto simpleAction = Sequence::create(DelayTime::create(0.05f/(thisRole->dataManager->getSingleData(ATKSPD)*1.0/PER_NUM)*thisRole->getAtkEffectFrame()),CallFunc::create([&](){
            abilityEffect();
        }), NULL);
        simpleAction->setTag(getId()*10+1);
        //控制朝向
        if(targetRole->getPositionX()<thisRole->getPositionX()){
            thisRole->body->setScaleX(-thisRole->getSizeScale());
        }else if(targetRole->getPositionX()>thisRole->getPositionX()){
            thisRole->body->setScaleX(thisRole->getSizeScale());
        }

        AbilityMaster::getInstance()->stopAbilityForRole(this->getId(), thisRole);
        //本身也很容易被打断
        thisRole->setStopLovel(this->getStopLevel());
        //还需要移动，和移动后的停止，这部分要加入
        
        thisRole->runAction(simpleAction);
        auto animateInAttack =Sequence::create(Animate::create(animation),CallFunc::create([&](){
                        end();
                    }),NULL);
        animateInAttack->setTag(getId()*10+2);
        thisRole->body->runAction(animateInAttack);

        
        return ;
    }else{
        //打断失败
        return ;
        
    }
}
//生效攻击
void AttackAbility::abilityEffect(){
    thisRole->setStopLovel(0);
    if (targetRole==nullptr||thisRole==nullptr){return;}
    if(AbilityMaster::getInstance()->areYouDead(targetRole)||AbilityMaster::getInstance()->areYouDead(thisRole)){
        return;
    }
    int damageType = AD;
    //面板伤害
    int damage = thisRole->dataManager->getSingleData(ATK);
    //是否触发暴击
    //这里的暴击率本来就需要乘1000，所以这样的话就不乘了
    srand(time(0));
    if (rand()%PER_NUM<thisRole->dataManager->getSingleData(CRIT)){
        damageType = AD_CRIT;
        damage = damage*CRIT_SCALE;
    }
    //是否是友军
    if(thisRole->getForce()==targetRole->getForce()){
        damage = damage * FRIEND_SCALE;
    }
    targetRole->getHit(damageType,damage,thisRole);
}
//被打断时执行
void AttackAbility::stop(){
    thisRole->stopActionByTag(getId()*10+1);
    thisRole->body->stopAllActionsByTag(getId()*10+2);
}
void AttackAbility::end(){
    thisRole->setStopLovel(0);
    thisRole->setRecentAbility(STAND);
    auto standMap =AbilityMaster::getInstance()->standMap;
    standMap.at(thisRole->getId())->start();
}
