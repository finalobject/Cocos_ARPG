//
//  FlyBlood.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#include "FlyBlood.hpp"
#include "BaseRole.hpp"
#include "AbilityMaster.hpp"
#include <string>

FlyBlood * FlyBlood::create(int type,int damage){
    FlyBlood * flyBlood = new FlyBlood();
    if(flyBlood && flyBlood->init(type,damage)){
        flyBlood->autorelease();
    }
    else{
        CC_SAFE_DELETE(flyBlood);
        return nullptr;
    }
    return flyBlood;
}
bool FlyBlood::init(int type,int damage){
    label = Label::createWithSystemFont(to_string(-damage), "", 15);
    Color3B color;
    if (type==AD){
        color = Color3B(255, 77, 38);
    }else if(type==AD_CRIT){
        color = Color3B(255, 255, 0);
    }else if(type==AP){
        color = Color3B::BLUE;
    }else if(type==AP_CRIT){
        color = Color3B(183, 42, 143);
    }else if(type==REAL){
        color = Color3B::WHITE;
    }else if(type==AP_COST){
        color = Color3B::GRAY;
    }
    label->setColor(color);
    this->addChild(label);
    
    
    return true;
}
void FlyBlood::start(){
    auto easeIn = EaseExponentialIn::create(Spawn::create(MoveBy::create(.5f,Vec2(50,50)),FadeOut::create(.2f), NULL));
    auto highLight = Sequence::create(ScaleBy::create(0.1, 1.5), ScaleBy::create(0.1, 0.7),NULL);
    auto sequence = Sequence::create(highLight,easeIn,CallFunc::create([&](){this->end();}),NULL);
    label->runAction(sequence);
}
void FlyBlood::end(){
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}

