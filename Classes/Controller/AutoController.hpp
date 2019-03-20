//
//  AutoController.hpp
//  battleheart
//
//  Created by finalObject on 2019/1/30.
//

#ifndef AutoController_hpp
#define AutoController_hpp

#include <stdio.h>
#include "allHead.hpp"
USING_NS_CC;
using namespace std;
class BaseRole;
class AutoController:public Node{
public:
    static AutoController * create(BaseRole* thisRole,vector<BaseRole *> *roles);
    virtual bool init(BaseRole* thisRole,vector<BaseRole *> *roles);
    void statesUpdate(float dt);
    void purge();
    int getAbility();//确定一个可以使用的技能，这里就是显示直接返回“a”,也就是普通攻击
public:
    vector<BaseRole *> *roles;
    BaseRole* thisRole;
    BaseRole* targetRole;
    int targetAbility;
};

#endif /* AutoController_hpp */
