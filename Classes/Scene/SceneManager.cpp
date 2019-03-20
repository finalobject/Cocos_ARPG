//
//  SceneManager.cpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#include "SceneManager.hpp"
#include "LoadLayer.hpp"
#include "OpenLayer.hpp"
#include "BattleLayer.hpp"
#include "cocos2d.h"
USING_NS_CC;
void SceneManager::createLoadScene(){
    loadScene = Scene::create();
    LoadLayer * layer = LoadLayer::create();
    layer->tsm = this;
    loadScene->addChild(layer);
    
}
void SceneManager::goOpenScene(){
    openScene = Scene::create();
    OpenLayer * layer = OpenLayer::create();
    layer->tsm = this;
    openScene->addChild(layer);
    
    Director::getInstance()->replaceScene(openScene);
    
}
void SceneManager::goMainScene(){
    mainScene = Scene::create();
    BattleLayer * layer = BattleLayer::create();
    layer->tsm = this;
    mainScene->addChild(layer);
    
    Director::getInstance()->replaceScene(mainScene);
}
