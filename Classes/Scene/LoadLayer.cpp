//
//  LoadLayer.cpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#include "LoadLayer.hpp"
bool LoadLayer::init(){
    Size winSize = Director::getInstance()->getWinSize();
    Label * label = Label::createWithTTF("loading...", "fonts/Marker Felt.ttf", 32);
    label->setPosition(Vec2(winSize.width/2,winSize.height/2));
    this->addChild(label);
    scheduleOnce(CC_SCHEDULE_SELECTOR(LoadLayer::onSchedulenOnce), 2.0);
    return true;
}
void LoadLayer::onSchedulenOnce(float dt){
    tsm->goOpenScene();
}
