//
//  BaseAbility.cpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#include "BaseAbility.hpp"
BaseAbility * BaseAbility::create(){
    BaseAbility * baseAbility = new BaseAbility();
    if(baseAbility && baseAbility->init()){
        baseAbility->autorelease();
    }else{
        CC_SAFE_DELETE(baseAbility);
    }
    return baseAbility;
}
bool BaseAbility::init(){
    return true;
}
void BaseAbility::start(){

}
void BaseAbility::stop(){
    
}
void BaseAbility::end(){
    
}

