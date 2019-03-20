//
//  OpenLayer.hpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#ifndef OpenLayer_hpp
#define OpenLayer_hpp

#include <stdio.h>
#include  "cocos2d.h"
#include "SceneManager.hpp"
USING_NS_CC;
class OpenLayer:public Layer{
public:
    CREATE_FUNC(OpenLayer);
    virtual bool init();
    void menuCallBack(Ref * pSender);
public:
    SceneManager * tsm;
    
};

#endif /* OpenLayer_hpp */
