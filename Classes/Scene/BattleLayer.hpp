//
//  BattleLayer.hpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#ifndef BattleLayer_hpp
#define BattleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SceneManager.hpp"
#include "time.h"

USING_NS_CC;
using namespace std;
class BaseRole;
class BattleLayer:public Layer{
public:
    CREATE_FUNC(BattleLayer);
    virtual bool init();
    
    void menuCallBack(Ref * pSender);
    
public:
    SceneManager * tsm;
    vector<BaseRole *> roles;

};

#endif /* ControlLayer_hpp */
