//
//  BaseRole.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#ifndef BaseRole_hpp
#define BaseRole_hpp

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>


#include "allHead.hpp"




using namespace std;
USING_NS_CC;

class DataManager;
class BaseController;
class Indicator;
class BloodBar;
class BaseAbility;
class StandAbility;
class MoveAbility;
class AutoController;


class BaseRole:public Node{
public:
    static BaseRole * createWithProperty(const std::string& plist,BaseController * controller);
    bool init(const std::string& plist,BaseController * controller);
    bool getHit(int type,int damage,BaseRole * fromWho);
    void getKilled();
    void updateNameLabel();
private:
    void setId();
public:
    //STATE type;
    CC_SYNTHESIZE(int, stopLevel, StopLovel);
    CC_SYNTHESIZE(int, recentAbility, RecentAbility);
    //是否呗选择
    CC_SYNTHESIZE(bool, isFocus, IsFocus);
    CC_SYNTHESIZE(bool, isControl, IsControl);
    
    CC_SYNTHESIZE(int,id,Id);
    
    Indicator * indicator;
    Sprite * body;
    BloodBar * bloodBar;
    Label * nameLabel;
    BaseController * controller;
    AutoController * autoController;
    DataManager * dataManager;
    
    
    //配置表中读取的数据
    CC_SYNTHESIZE(float, sizeScale, SizeScale);
    CC_SYNTHESIZE(int, weight, Weight);//边缘判断时候用来可以弹走轻的
    CC_SYNTHESIZE(int, force, Force);//阵营，0 1 2

    CC_SYNTHESIZE(std::string,roleName,RoleName);
    CC_SYNTHESIZE(std::string,roleType,RoleType);
    CC_SYNTHESIZE(int,place,Place);//受击打圆的半径
    CC_SYNTHESIZE(int, atkEffectFrame, AtkEffectFrame);//普通攻击在什么时候生效，关系到攻击后摇
    
    
    
};

#endif /* BaseRole_hpp */
