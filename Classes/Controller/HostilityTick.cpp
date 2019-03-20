//
//  HostilityTick.cpp
//  battleheart
//
//  Created by finalObject on 2019/2/2.
//

#include "HostilityTick.hpp"
#include "Hostility.hpp"
#include "BaseRole.hpp"
HostilityTick * HostilityTick::create(BaseRole* toWho,BaseRole* fromWho,int num,int delayTime,int flag){
    HostilityTick * hostilityTick = new HostilityTick();
    if(hostilityTick && hostilityTick->init(toWho,fromWho,num,delayTime,flag)){
        hostilityTick->autorelease();
    }else{
        CC_SAFE_DELETE(hostilityTick);
        return nullptr;
    }
    return hostilityTick;
}
bool HostilityTick::init(BaseRole* toWho,BaseRole* fromWho,int num,int delayTime,int flag){
    this->retain();
    this->toWho = toWho;
    this->fromWho = fromWho;
    this->number = num;
    this->flag = flag;
    auto myAction = Sequence::create(DelayTime::create(delayTime),CallFunc::create([&](){this->effect();}),NULL);
    this->runAction(myAction);
    return true;
}
void HostilityTick::effect(){
    if(this->flag == HIT)
    {
        Hostility::getInstance()->removeHostilityByHit(toWho,fromWho,number);
    }else if(this->flag == HEAL){
        Hostility::getInstance()->removeHostilityByHeal(toWho,fromWho,number);
        
    }
    
    
    this->toWho = nullptr;
    this->fromWho = nullptr;
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
    return;
}
