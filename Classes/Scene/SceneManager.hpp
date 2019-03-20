//
//  SceneManager.hpp
//  testCpp-mobile
//
//  Created by finalObject on 2018/12/5.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class SceneManager{
public:
    Scene * loadScene;
    Scene * openScene;
    Scene * mainScene;
    
    void createLoadScene();
    void goOpenScene();
    void goMainScene();
};

#endif /* SceneManager_hpp */
