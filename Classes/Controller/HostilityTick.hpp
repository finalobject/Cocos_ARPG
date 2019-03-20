//
//  HostilityTick.hpp
//  battleheart
//
//  Created by finalObject on 2019/2/2.
//

#ifndef HostilityTick_hpp
#define HostilityTick_hpp

#include <stdio.h>
#include "allHead.hpp"
USING_NS_CC;
using namespace std;

class BaseRole;
//这个东西，是用来延迟之后消除仇恨的，因为仇恨有一个有效期，默认是10秒，
class HostilityTick:public Node{
public:
    static HostilityTick * create(BaseRole* toWho,BaseRole* fromWho,int num,int delayTime,int flag);
    bool init(BaseRole* toWho,BaseRole* fromWho,int num,int delayTime,int flag);
    void effect();
public:
    BaseRole* toWho;
    BaseRole* fromWho;
    int number;
    int flag;
    
};
#endif /* HostilityTick_hpp */
