//
//  AbilityMaster.hpp
//  battleheart
//
//  Created by finalObject on 2018/12/22.
//

#ifndef AbilityMaster_hpp
#define AbilityMaster_hpp

#include <stdio.h>
#include "allHead.hpp"
USING_NS_CC;
using namespace std;

class BaseRole;
class MoveAbility;
class StandAbility;
class AttackAbility;
class BaseAbility;

class AbilityMaster:public Ref{
    //流程是这样的，创建的时候，输入对应的角色id，技能种类和按键位置
        //首先在abilityMap上根据角色id和键位绑定上对应的技能种类
        //然后在对应技能的map上创建好技能
    //调用的时候，首先执行无参的spell
        //如果对应技能 的type是0，直接执行
        //如果是1，返回NEED_POINT
        //如果是2，返回NEED_ROLE
    //你这里还要提供一个东西，储存一下死掉角色的指针，虽然已经被释放了，但是可以存起来，有危险的函数想调用，先看一下你这个角色死了没有
public:
    static AbilityMaster * getInstance();
    bool init();
    //添加技能
    void addAbilityById(int ability,BaseRole * thisRole,char key);
    void removeAbilityById(BaseRole * thisRole,char key);
    //执行技能
    int spell(BaseRole * thisRole,char key);
    void spell(BaseRole * thisRole,char key,Vec2 targetPlace);
    void spell(BaseRole * thisRole,char key,BaseRole * tarRole);
    void stopAbilityForRole(int ability,BaseRole* thisRole);
    //回收部分
    void removeRole(BaseRole * thisRole);
    //有人死了,这个函数会在removeRole中执行
    void addDeadRole(BaseRole * thisRole);
    //判断死了没
    bool areYouDead(BaseRole * thisRole);
private:
    int getAbility(BaseRole * thisRole,char key);
public:
    Map<int, StandAbility*> standMap;//int是对应角色的id
    Map<int, MoveAbility*> moveMap;
    Map<int, AttackAbility*> attackMap;
    //Map<int,Map<char,ABILITY>>abilityMap;
    
    int abilityMap[ROLES_MAXNUM][KEYS_MAXNUM];
    //存着死掉的人
    vector<BaseRole *> deadRoles;
};

#endif /* AbilityMaster_hpp */
