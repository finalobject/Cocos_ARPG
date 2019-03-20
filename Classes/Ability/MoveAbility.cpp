//
//  MoveAbility.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/16.
//

#include "MoveAbility.hpp"
#include "StandAbility.hpp"
#include "BaseRole.hpp"
#include "AbilityMaster.hpp"
#include "DataManager.hpp"

MoveAbility * MoveAbility::create(BaseRole* thisRole){
    MoveAbility * moveAbility = new MoveAbility();
    if(moveAbility && moveAbility->init(thisRole)){
        moveAbility->autorelease();
    }else{
        CC_SAFE_DELETE(moveAbility);
    }
    return moveAbility;
}
bool MoveAbility::init(BaseRole* thisRole){
    this->setThisRole(thisRole);
    this->setAbilityName("move");
    this->setStopLevel(0);
    this->setId(MOVE);
    this->setType(NEED_POINT);//需要点
    //准备动画
    auto frameCache = SpriteFrameCache::getInstance();
    auto plistPath =String::createWithFormat("animation//%s//%s_%s.plist",thisRole->getRoleType().data(),thisRole->getRoleType().data(),this->getAbilityName().data());
    frameCache->addSpriteFramesWithFile(plistPath->getCString());
    Vector<SpriteFrame*> vec;
    for (int i=1;i<=14;i++){
        auto name = String::createWithFormat("%s_%s_%d.png",thisRole->getRoleType().data(),this->getAbilityName().data(),i);
        vec.pushBack(frameCache->getSpriteFrameByName(name->getCString()));
    }
    animation = Animation::createWithSpriteFrames(vec);
    animation->setDelayPerUnit(0.05f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    animation->retain();

    this->retain();
    
    return true;
}

void MoveAbility::start(Vec2 target){
    //移动能够打断的技能比较少，level比较低
    if (thisRole->getStopLovel()<1){
        
        //制作移动动画
        animation->setDelayPerUnit(0.05f/(thisRole->dataManager->getSingleData(SPD)*1.0/SPEED_SCALE/100));
        
        float moveTime = (sqrt(pow(thisRole->getPositionY()*Y_SCALE-target.y*Y_SCALE,2)+pow(thisRole->getPositionX()-target.x,2)))/(thisRole->dataManager->getSingleData(SPD)*1.0/SPEED_SCALE);
        auto simpleMove = Sequence::create(MoveTo::create(moveTime, target),CallFunc::create([&](){
            end();
        }), NULL);
        simpleMove->setTag(getId()*10+1);
        //控制朝向
        if(target.x<thisRole->getPositionX()){
            thisRole->body->setScaleX(-thisRole->getSizeScale());
        }else if(target.x>thisRole->getPositionX()){
            thisRole->body->setScaleX(thisRole->getSizeScale());
        }
        if(thisRole->getRecentAbility()==MOVE){
            //如果正在跑步，不走正常的打断途径
            //只停止移动，不停止动画
            thisRole->stopAllActionsByTag(getId()*10+1);
            thisRole->runAction(simpleMove);
        }else{
             AbilityMaster::getInstance()->stopAbilityForRole(this->getId(), thisRole);
            //本身也很容易被打断
            thisRole->setStopLovel(this->getStopLevel());
            //还需要移动，和移动后的停止，这部分要加入

            thisRole->runAction(simpleMove);
//            auto animateInMove =Sequence::create(DelayTime::create(0.01),Animate::create(animation), NULL);
            auto animateInMove =Sequence::create(Animate::create(animation), NULL);

            animateInMove->setTag(getId()*10+2);
            thisRole->body->runAction(animateInMove);
        }
        
        return ;
    }else{
        //打断失败
        return ;
        
    }
    
}
//被打断时执行
void MoveAbility::stop(){
    thisRole->body->stopAllActionsByTag(getId()*10+2);
    thisRole->stopAllActionsByTag(getId()*10+1);
}
void MoveAbility::end(){
    auto standMap =AbilityMaster::getInstance()->standMap;
    standMap.at(thisRole->getId())->start();
    
}
