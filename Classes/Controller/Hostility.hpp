//
//  Hostility.hpp
//  battleheart
//
//  Created by finalObject on 2019/1/30.
//
//belong to AIController
#ifndef Hostility_hpp
#define Hostility_hpp

#include <stdio.h>
#include "allHead.hpp"
USING_NS_CC;
using namespace std;

//这也是一个静态类
//这个仇恨类，使用的时候，首先需要在layer里面，初始化，setRoles，然后addChild上这个类，不然之后的那个延迟动作就不能执行
//然后添加到人物收到伤害或者回复的时候自动触发，应该都是在getHit里面了，以后也不用动
//然后获取，就是在autoController里面，获取最大的那个哥们
class BaseRole;
class Hostility:public Node{
public:
    static Hostility * getInstance();
    bool init();
    
    void setRoles(vector<BaseRole *> *roles);

    //添加仇恨，第一个参数是被攻击的那个人，第二个参数是攻击人，然后就是仇恨数量，然后是多少时间消除，默认10s
    void addHostilityByHit(BaseRole* toWho,BaseRole* fromWho,int number,int delayTime);
    void removeHostilityByHit(BaseRole* toWho,BaseRole* fromWho,int number);
    //回复，会添加其他势力仇恨。回复势力是按照被回复者为基准，不是施法者
    void addHostilityByHeal(BaseRole* toWho,BaseRole* fromWho,int number,int delayTime);
    void removeHostilityByHeal(BaseRole* toWho,BaseRole* fromWho,int number);
    //返回一个没有死掉的仇恨最高的目标
    BaseRole* getTarget(BaseRole* who);
    //删除死掉的角色的仇恨
    void clearHostilityById(int id);
    void clearAllHostility();
    void purge();
private:
    //个人仇恨，包括自己被打的仇恨和敌人回血的仇恨
    //第一个下标是自己的标号，第二个下标是对于不同人的仇恨
    long int selfHostility[ROLES_MAXNUM][ROLES_MAXNUM];

    
    vector<BaseRole *> *roles;
};
#endif /* Hostility_hpp */
