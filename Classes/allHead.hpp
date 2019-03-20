//
//  allHead.hpp
//  battleheart
//
//  Created by finalObject on 2019/2/1.
//

#ifndef allHead_hpp
#define allHead_hpp

#include <stdio.h>


//DataManager
//所有的人物属性
#define HP 0
#define SP 1
#define HPR 2
#define SPR 3
#define ATK 4
#define ATKSPD 5
#define ATKRANGE 6
#define MAG 7
#define ARM 8
#define ORI 9
#define SPD 10
//攻击速度数值为1000s发动普通攻击数量
#define PER_NUM 1000
//所有用百分数表示的数值，都乘1000
//HPR,SPR表示每50s的回复量,所以lol数据直接乘10就行
#define R_NUM 50
#define R_TICKTIME 2

//移动速度调节参数
#define SPEED_SCALE 4.0
#define RANGE_SCALE 2.0

//HP,SP,HPR,SPR,ATK,ATKSPD,ATKRANGE,MAG,ARM,ORI,SPD，
//生命值，法力值，生命回复，法力回复，攻击力，攻击速度，攻击射程，法术攻击，护甲，魔抗，移动速度
//10来自初始数据/成长数据/装备加持数据/技能加持数据（buff属于技能加持范围）
//初始数据和成长数据都是绝对值累加
//装备和技能加持有绝对值，也有百分比

#define CRIT 11
#define DODGE 12
//暴击率，回避率
//这两个属性初始数据和成长数据均为0

#define HATE_SCALE 13
//HATE_SCALE是拉仇恨的能力，正常应该是1k

//
#define BIG_NUM 14
#define SMALL_NUM 11

//装备还是技能
#define EQUIP 1
#define ABILITY 2



//AbilityMaster
//伤害种类
#define AD 1
#define AD_CRIT 2
#define AP 3
#define AP_CRIT 4
#define REAL 5
#define AP_COST 6

#define CRIT_SCALE 1.5
#define FRIEND_SCALE 0.5

//定义技能编号
#define STAND 1
#define MOVE 2
#define ATTACK 3

#define NICE 0
#define NEED_POINT 1
#define NEED_ROLE 2


#define ROLES_MAXNUM 10
#define KEYS_MAXNUM 26


//BaseRole
#define Y_SCALE 1.5

//Indicator
#define INDICATOR_STEP 2
#define INDICATOR_WIDTH 2

//Hostility
#define FORCE_NUM 3
#define FORCE_0 0
#define FORCE_1 1
#define FORCE_2 2
#define DEFAULT_DELAYTIME 10
//别人的血量回复计算仇恨时候的比例
#define HEAL_SCALE 0.8
//打在队友身上的伤害，仇恨的比例
#define TEAM_SCALE 0.5
#define HIT 1
#define HEAL 2

#endif /* allHead_hpp */
