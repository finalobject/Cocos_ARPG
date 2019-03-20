//
//  Data.hpp
//  battleheart
//
//  Created by finalObject on 2019/1/28.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
USING_NS_CC;
using namespace std;

#include "allHead.hpp"

class DataManager:public Node{
public:
    static DataManager * create(ValueMap valueMap);
    virtual bool init(ValueMap valueMap);
private:
    void updatePowerData();
    void recovery(float dt);//回血回蓝
    CC_SYNTHESIZE(int, nowHp, NowHp);
    CC_SYNTHESIZE(int, nowSp, NowSp);
    CC_SYNTHESIZE(int, level, Level);
    int powerData[BIG_NUM];
    int initData[BIG_NUM];//初始数据
    int growData[BIG_NUM];//成长数据
    int equipDataAbsolute[BIG_NUM];//装备绝对数据
    float equipDataRelative[BIG_NUM];//装备相对数据
    int abilityDataAbsolute[BIG_NUM];//技能绝对数据
    float abilityDataRelative[BIG_NUM];//技能相对数据
    
public:
    int getSingleData(int whichData);
    void upgrade();
    void addEffect(int dataAbsolute[BIG_NUM],float dataRelative[BIG_NUM],int equipOrAbility);//装备或者技能生效的时候需要执行的函数
    void removeEffect(int dataAbsolute[BIG_NUM],float dataRelative[BIG_NUM],int equipOrAbility);//装备或者技能失效时需要执行的函数
    //技能里计算出伤害，然后承受伤害的计算，和实际的扣血在这里完成，返回false表示还活着，true表示角色死亡
    void purge();
};
#endif /* DataManager_hpp */
