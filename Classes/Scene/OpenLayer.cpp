//
//  OpenLayer.cpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#include "OpenLayer.hpp"
bool OpenLayer::init(){
    Size winSize = Director::getInstance()->getWinSize();
    Label * label =Label::createWithTTF("BattleHeart", "fonts/Marker Felt.ttf", 48);
    label->setPosition(Vec2(winSize.width/2,winSize.height*3/4));
    label->setColor(Color3B(255,255,255));
    this->addChild(label);
    
    MenuItem * menuItem1 = MenuItemLabel::create(Label::createWithTTF("start", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
    menuItem1->setTag(101);
    menuItem1->setPosition(Vec2(winSize.width/2,winSize.height*0.3));
    
    MenuItem * menuItem2 = MenuItemLabel::create(Label::createWithTTF("exit","fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
    menuItem2->setTag(102);
    menuItem2->setPosition(Vec2(winSize.width/2,winSize.height*0.15));
    
    auto menu = Menu::create(menuItem1,menuItem2,NULL);
    menu->setPosition(Vec2(0,0));
    
    this->addChild(menu);
    
    return true;
}
void OpenLayer::menuCallBack(Ref * pSender){
    switch (((MenuItem *)pSender)->getTag()) {
        case 101:
            tsm->goMainScene();
            break;
        case 102:
            Director::getInstance()->end();
            break;
        default:
            break;
    }
    
}

