//
//  MoveAbility.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/16.
//

#ifndef MoveAbility_hpp
#define MoveAbility_hpp

#include <stdio.h>
#include "BaseAbility.hpp"

USING_NS_CC;

class BaseRole;
class MoveAbility:public BaseAbility{
public:
    static MoveAbility * create(BaseRole* thisRole);
    virtual bool init(BaseRole* thisRole);
    void start(Vec2 target);
    void stop();
    void end();
public:
    Animation* animation;

};
#endif /* MoveAbility_hpp */
