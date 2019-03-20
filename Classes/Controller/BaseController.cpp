//
//  BaseController.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#include "BaseController.hpp"
#include "BaseRole.hpp"
#include "MoveAbility.hpp"
#include "StandAbility.hpp"
#include "AbilityMaster.hpp"
#include "FlyBlood.hpp"

BaseController * BaseController::create(vector<BaseRole *> *roles){
    BaseController * baseController = new BaseController();
    if(baseController && baseController->init(roles)){
        baseController->autorelease();
    }else{
        CC_SAFE_DELETE(baseController);
    }
    return baseController;
}
bool BaseController::init(vector<BaseRole *> *roles){
    this->roles = roles;

    
   
    return true;
}
void BaseController::startWithRole(BaseRole * thisRole){
    setThisRole(thisRole);
    thisCmd = 0;
    targetPoint = Vec2(0,0);
    targetRole = nullptr;
    
    //键盘监听
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(BaseController::onKeyReleased, this);
    listenerkeyPad->onKeyPressed = CC_CALLBACK_2(BaseController::onKeyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    //鼠标监听
    //电脑鼠标
    auto listenerMouse = EventListenerMouse::create();
    listenerMouse->onMouseUp = CC_CALLBACK_1(BaseController::onMouseUp,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, this);
    
}
void BaseController::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{


}
void BaseController::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    if(this->thisRole==nullptr){return;}
    if (keycode == EventKeyboard::KeyCode::KEY_S)
    {
        AbilityMaster::getInstance()->spell(thisRole, 's');
    }else if(keycode == EventKeyboard::KeyCode::KEY_X){
        thisCmd = 'x';
    }else if(keycode == EventKeyboard::KeyCode::KEY_A){
        if(targetRole!=nullptr){
            AbilityMaster::getInstance()->spell(thisRole, 'a',targetRole);
        }else{
            thisCmd = 'a';
        }
    }else if(keycode == EventKeyboard::KeyCode::KEY_ESCAPE){
        thisCmd = 0;
        setTargetRole(nullptr);
    }else if(keycode == EventKeyboard::KeyCode::KEY_TAB){
        setTargetRoleBySwitch();
    }
}
void BaseController::onMouseUp(Event * event){
    if(this->thisRole==nullptr){return;}
    EventMouse * e = (EventMouse*)event;
    auto abilityMaster=AbilityMaster::getInstance();
    //如果是右键，执行移动函数
    if(e->getMouseButton()==EventMouse::MouseButton::BUTTON_RIGHT){
        if(setTargetRoleByPoint(Vec2(e->getCursorX(),e->getCursorY()))==true){
            abilityMaster->spell(thisRole, 'a',this->targetRole);
            thisCmd = 0;
        }else{
            abilityMaster->spell(thisRole, 'x',Vec2(e->getCursorX(),e->getCursorY()));
        }
    //如果是左键
    }else if(e->getMouseButton()==EventMouse::MouseButton::BUTTON_LEFT){
        //如果没有等待执行的命令，就选择一个角色
        if(thisCmd==0){
            setTargetRoleByPoint(Vec2(e->getCursorX(),e->getCursorY()));
            return;
        //如果有指令，先测试一下，如果需要点
        }else if(abilityMaster->spell(thisRole, thisCmd)==NEED_POINT){
            abilityMaster->spell(thisRole, thisCmd,Vec2(e->getCursorX(),e->getCursorY()));
            thisCmd=0;
        //如果需要角色
        }else if(abilityMaster->spell(thisRole, thisCmd)==NEED_ROLE){
            setTargetRoleByPoint(Vec2(e->getCursorX(),e->getCursorY()));
            if(targetRole!=nullptr){
                abilityMaster->spell(thisRole, thisCmd,targetRole);
            }
            thisCmd=0;

        }
        
    }
}
//这个是在鼠标点击的时候用
bool BaseController::setTargetRoleByPoint(Vec2 targetPlace){
    for (int i=0; i<roles->size(); i++) {
        auto tmpRole =roles->at(i);
        auto dis =sqrt(pow(targetPlace.x-tmpRole->getPositionX(),2)+pow(targetPlace.y*Y_SCALE-tmpRole->getPositionY()*Y_SCALE,2));
        if (dis<tmpRole->getPlace()){
            setTargetRole(tmpRole);
            return true;
        }
    }
    return false;
}
void BaseController::setTargetRoleBySwitch(){
    if(targetRole!=nullptr){
        int targetFoce = targetRole->getForce();
        int targetIndex = 0;
        //找打目标的位置，切换当然要从他后面开始切换
        for (int i=0; i<roles->size(); i++) {
            if(roles->at(i)->getId()==targetRole->getId()){
                targetIndex= i;
                break;
            }
        }
        for (int i=0; i<roles->size(); i++) {
            auto tmpRole =roles->at((i+targetIndex+1)%roles->size());
            if(tmpRole->getForce()==targetFoce){
                setTargetRole(tmpRole);
                return;
            }
        }
    }else if(thisRole!=nullptr){
        int thisForce = thisRole->getForce();
        for (int i=0; i<roles->size(); i++) {
            auto tmpRole = roles->at(i);
            if(tmpRole->getForce()!=thisForce){
                setTargetRole(tmpRole);
                return;
            }
        }
    }
}



void BaseController::setThisRole(BaseRole * another){
    if(this->thisRole!=nullptr){
        this->thisRole->setIsControl(false);
    }
    this->thisRole=another;
    if(this->thisRole!=nullptr){
        this->thisRole->setIsControl(true);
    }
    return;
}
void BaseController::setTargetRole(BaseRole * another){
    if(this->targetRole!=nullptr){
        this->targetRole->setIsFocus(false);
    }
    this->targetRole = another;
    if(this->targetRole!=nullptr){
        this->targetRole->setIsFocus(true);
    }
    return;
}
