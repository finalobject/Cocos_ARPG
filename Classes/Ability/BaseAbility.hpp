//
//  BaseAbility.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#ifndef BaseAbility_hpp
#define BaseAbility_hpp

#include <stdio.h>
#include "allHead.hpp"

USING_NS_CC;



class BaseRole;

class BaseAbility:public Ref{
public:
    static BaseAbility * create();
    virtual bool init();
    void start();
    void stop();//目前放不进去
    void end();//自己结束
public:
    CC_SYNTHESIZE(BaseRole *,thisRole,ThisRole);
    CC_SYNTHESIZE(std::string,abilityName,AbilityName);
    CC_SYNTHESIZE(int, cd, Cd);
    CC_SYNTHESIZE(bool, isReady, IsReady);
    CC_SYNTHESIZE(int, range, Range);
    CC_SYNTHESIZE(int, id, Id);
    CC_SYNTHESIZE(int, stopLevel, StopLevel);//是否容易呗其他技能打断
    CC_SYNTHESIZE(int, type, Type);//0-不需要参数，1需要点，2需要英雄
};

#endif /* BaseAbility_hpp */
