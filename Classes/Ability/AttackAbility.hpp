//
//  AttackAbility.hpp
//  battleheart
//
//  Created by finalObject on 2018/12/27.
//

#ifndef AttackAbility_hpp
#define AttackAbility_hpp

#include <stdio.h>
#include "BaseAbility.hpp"

USING_NS_CC;

class BaseRole;
class AttackAbility:public BaseAbility{
public:
    static AttackAbility * create(BaseRole* thisRole);
    virtual bool init(BaseRole* thisRole);
    void start(BaseRole* targetRole);
    void stop();
    void abilityEffect();
    void end();
public:
    Animation* animation;
    BaseRole* targetRole;
    
};
#endif /* AttackAbility_hpp */
