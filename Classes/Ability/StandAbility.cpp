//
//  StandAbility.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/16.
//

#include "StandAbility.hpp"
#include "BaseRole.hpp"
#include "AbilityMaster.hpp"

StandAbility * StandAbility::create(BaseRole * thisRole){
    StandAbility * standAbility = new StandAbility();
    if(standAbility && standAbility->init(thisRole)){
        standAbility->autorelease();
    }else{
        CC_SAFE_DELETE(standAbility);
    }
    return standAbility;
}
bool StandAbility::init(BaseRole * thisRole){
    
    this->setThisRole(thisRole);
    this->setAbilityName("stand");
    this->setType(NICE);//不需要参数
    this->setStopLevel(0);
    this->setId(STAND);
    //准备动画
    auto frameCache = SpriteFrameCache::getInstance();
    auto plistPath =String::createWithFormat("animation//%s//%s_%s.plist",thisRole->getRoleType().data(),thisRole->getRoleType().data(),this->getAbilityName().data());
    frameCache->addSpriteFramesWithFile(plistPath->getCString());
    //frameCache->addSpriteFramesWithFile("knight/knight_default.plist");
    Vector<SpriteFrame*> vec;
    for (int i=1;i<=15;i++){
        auto name = String::createWithFormat("%s_%s_%d.png",thisRole->getRoleType().data(),this->getAbilityName().data(),i);
        vec.pushBack(frameCache->getSpriteFrameByName(name->getCString()));
    }
    animation = Animation::createWithSpriteFrames(vec);
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    animation->retain();

    this->retain();
    
    return true;
}
void StandAbility::start(){
    
    if (thisRole->getStopLovel()<1&&thisRole->getRecentAbility()!=ATTACK){
        AbilityMaster::getInstance()->stopAbilityForRole(this->getId(), thisRole);
        
        //本身也很容易被打断
        thisRole->setStopLovel(this->getStopLevel());
        //还需要移动，和移动后的停止，这部分要加入
        auto tmp =Sequence::create(Animate::create(animation), NULL);
//        auto tmp =Sequence::create(DelayTime::create(0.01),Animate::create(animation), NULL);
        tmp->setTag(getId()+1);
        thisRole->body->runAction(tmp);

    }
    else{
        //打断失败
        
    }
    return ;
}
//被打断时执行
void StandAbility::stop(){
    thisRole->body->stopAllActionsByTag(getId()+1);
}
void StandAbility::end(){
    
}
