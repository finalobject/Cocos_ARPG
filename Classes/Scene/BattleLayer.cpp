//
//  BattleLayer.cpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#include "BattleLayer.hpp"
#include "BaseRole.hpp"
#include "BaseController.hpp"
#include "PhysicManager.hpp"
#include "AbilityMaster.hpp"
#include "Hostility.hpp"

#include "BloodBar.hpp"



bool BattleLayer::init(){
    Size winSize = Director::getInstance()->getWinSize();
    MenuItemLabel * menuItem = MenuItemLabel::create(Label::createWithSystemFont("Back", "", 30),CC_CALLBACK_1(BattleLayer::menuCallBack, this) );
    menuItem->setPosition(Vec2(winSize.width*0.9,winSize.height*0.9));
    auto menu = Menu::create(menuItem,NULL);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu);

    //控制器初始化
    auto bc = BaseController::create(&roles);
    this->addChild(bc);
    //玩家角色
    roles.push_back(BaseRole::createWithProperty("roleData/knight_data.plist",bc));
    roles.at(0)->setPosition(Vec2(winSize.width/2,winSize.height/2));
    //roles.at(0)->setThisHp(400);
    this->addChild(roles.at(0));
    //启动控制器
    bc->startWithRole(roles.at(0));
    //机器人角色
    //1阵营
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(1)->setPosition(Vec2(winSize.width/2-320,winSize.height/2-0));
    this->addChild(roles.at(1));
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(2)->setPosition(Vec2(winSize.width/2-320,winSize.height/2+160));
    this->addChild(roles.at(2));
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(3)->setPosition(Vec2(winSize.width/2-320,winSize.height/2-160));
    this->addChild(roles.at(3));
    
    //2阵营
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(4)->setPosition(Vec2(winSize.width/2+320,winSize.height/2-0));
    roles.at(4)->setForce(2);
    roles.at(4)->updateNameLabel();
    this->addChild(roles.at(4));
    
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(5)->setPosition(Vec2(winSize.width/2+320,winSize.height/2+160));
    roles.at(5)->setForce(2);
    roles.at(5)->updateNameLabel();
    this->addChild(roles.at(5));
    
    
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(6)->setPosition(Vec2(winSize.width/2+320,winSize.height/2-160));
    roles.at(6)->setForce(2);
    roles.at(6)->updateNameLabel();
    this->addChild(roles.at(6));
    
    //友军
    roles.push_back(BaseRole::createWithProperty("roleData/robot_data.plist",bc));
    roles.at(7)->setPosition(Vec2(winSize.width/2,winSize.height/2+160));
    roles.at(7)->setForce(0);
    roles.at(7)->updateNameLabel();
    this->addChild(roles.at(7));
    
    //物理引擎管理
    PhysicManager * pManger = PhysicManager::create(&roles);
    this->addChild(pManger);
    
    //仇恨管理初始化
    auto host =Hostility::getInstance();
    this->addChild(host);
    host->clearAllHostility();
    host->setRoles(&roles);

    return true;
}

void BattleLayer::menuCallBack(Ref * pSender){
    tsm->goOpenScene();
}
