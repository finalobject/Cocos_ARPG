//
//  StandAbility.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/16.
//

#ifndef StandAbility_hpp
#define StandAbility_hpp

#include <stdio.h>
#include "BaseAbility.hpp"

USING_NS_CC;

class BaseRole;
class StandAbility:public BaseAbility{
public:
    static StandAbility * create(BaseRole * thisRole);
    virtual bool init(BaseRole * thisRole);
    void start();
    void stop();
    void end();
public:
    Animation* animation;
};

#endif /* StandAbility_hpp */
