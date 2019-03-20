//
//  BaseController.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#ifndef BaseController_hpp
#define BaseController_hpp

#include <stdio.h>
USING_NS_CC;
using namespace std;
class BaseRole;
class BaseController:public Node{
public:
    static BaseController * create(vector<BaseRole *> *roles);
    virtual bool init(vector<BaseRole *> *roles);
    void startWithRole(BaseRole * thisRole);
public:
    vector<BaseRole *> *roles;
private:
    char thisCmd;
    BaseRole * thisRole;
    Vec2 targetPoint;
    BaseRole * targetRole;
public:
    void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    void onMouseUp(cocos2d::Event * event);


    bool setTargetRoleByPoint(Vec2 targetPlace);
    void setTargetRoleBySwitch();
    
    void setThisRole(BaseRole * another);
    void setTargetRole(BaseRole * another);
};
#endif /* MyController_hpp */
