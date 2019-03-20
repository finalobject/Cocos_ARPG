//
//  LoadLayer.hpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#ifndef LoadLayer_hpp
#define LoadLayer_hpp

#include <stdio.h>
#include  "cocos2d.h"
#include "SceneManager.hpp"
USING_NS_CC;
class LoadLayer:public Layer{
public:
    CREATE_FUNC(LoadLayer);
    virtual bool init();
    void onSchedulenOnce(float dt);
public:
    SceneManager * tsm;
};

#endif /* LoadLayer_hpp */
