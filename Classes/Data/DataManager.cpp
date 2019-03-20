//
//  DataManager.cpp
//  battleheart
//
//  Created by finalObject on 2019/1/28.
//

#include "DataManager.hpp"
#include "BaseRole.hpp"

DataManager * DataManager::create(ValueMap valueMap){
    DataManager * dataManager = new DataManager();
    if(dataManager && dataManager->init(valueMap)){
        dataManager->autorelease();
    }else{
        CC_SAFE_DELETE(dataManager);
        return nullptr;
    }
    return dataManager;
}
bool DataManager::init(ValueMap valueMap){
    //
//    int initData[BIG_NUM];//初始数据
//    int growData[BIG_NUM];//成长数据
    //initData和growData会从初始化的函数中赋值
    initData[HP] = valueMap["HP_INIT"].asInt();
    growData[HP] = valueMap["HP_GROW"].asInt();
    initData[SP] = valueMap["SP_INIT"].asInt();
    growData[SP] = valueMap["SP_GROW"].asInt();
    initData[HPR] = valueMap["HPR_INIT"].asInt();
    growData[HPR] = valueMap["HPR_GROW"].asInt();
    initData[SPR] = valueMap["SPR_INIT"].asInt();
    growData[SPR] = valueMap["SPR_GROW"].asInt();
    initData[ATK] = valueMap["ATK_INIT"].asInt();
    growData[ATK] = valueMap["ATK_GROW"].asInt();
    initData[ATKSPD] = valueMap["ATKSPD_INIT"].asInt();
    growData[ATKSPD] = valueMap["ATKSPD_GROW"].asInt();
    initData[ATKRANGE] = valueMap["ATKRANGE_INIT"].asInt();
    growData[ATKRANGE] = valueMap["ATKRANGE_GROW"].asInt();
    initData[MAG] = valueMap["MAG_INIT"].asInt();
    growData[MAG] = valueMap["MAG_GROW"].asInt();
    initData[ARM] = valueMap["ARM_INIT"].asInt();
    growData[ARM] = valueMap["ARM_GROW"].asInt();
    initData[ORI] = valueMap["ORI_INIT"].asInt();
    growData[ORI] = valueMap["ORI_GROW"].asInt();
    initData[SPD] = valueMap["SPD_INIT"].asInt();
    growData[SPD] = valueMap["SPD_GROW"].asInt();
    
    //拉仇恨的能力
    initData[HATE_SCALE]= valueMap["HATE_SCALE"].asInt();
    growData[HATE_SCALE] = 0;
    //这个几是0
    initData[CRIT]=growData[CRIT]=100;
    initData[DODGE]=growData[DODGE]=0;
    
    
    level = 1;
    setNowHp(-1);//表示初始状态，会在updatePowerData里更新数值
    setNowSp(-1);
    for (int i=0; i<BIG_NUM; i++) {
        equipDataAbsolute[i]=0;
        equipDataRelative[i]=1;
        abilityDataAbsolute[i]=0;
        abilityDataRelative[i]=1;
    }
    updatePowerData();
    //启动回血定时器，TICKTIME秒执行一次，
    //以前都是这么用，1.0/60，意思是一秒执行60次，这是频率
    schedule(CC_SCHEDULE_SELECTOR(DataManager::recovery), R_TICKTIME);
    return true;
}
void DataManager::upgrade(){
    setLevel(getLevel()+1);
    updatePowerData();
}
void DataManager::addEffect(int dataAbsolute[BIG_NUM],float dataRelative[BIG_NUM],int equipOrAbility)//装备或者技能生效的时候需要执行的函数
{
    switch (equipOrAbility) {
        case EQUIP:
            for (int i=0; i<BIG_NUM; i++) {
                equipDataAbsolute[i]=equipDataAbsolute[i]+dataAbsolute[i];
                equipDataRelative[i]=equipDataRelative[i]+dataRelative[i];
            }
            break;
        case ABILITY:
            for (int i=0; i<BIG_NUM; i++) {
                abilityDataAbsolute[i]=abilityDataAbsolute[i]+dataAbsolute[i];
                abilityDataRelative[i]=abilityDataRelative[i]+dataRelative[i];
            }
            break;
        default:
            break;
    }
    updatePowerData();
}
void DataManager::removeEffect(int dataAbsolute[BIG_NUM],float dataRelative[BIG_NUM],int equipOrAbility)//装备或者技能失效时需要执行的函数
{
    switch (equipOrAbility) {
        case EQUIP:
            for (int i=0; i<BIG_NUM; i++) {
                equipDataAbsolute[i]=equipDataAbsolute[i]-dataAbsolute[i];
                equipDataRelative[i]=equipDataRelative[i]-dataRelative[i];
            }
            break;
        case ABILITY:
            for (int i=0; i<BIG_NUM; i++) {
                abilityDataAbsolute[i]=abilityDataAbsolute[i]-dataAbsolute[i];
                abilityDataRelative[i]=abilityDataRelative[i]-dataRelative[i];
            }
            break;
        default:
            break;
    }
    updatePowerData();
}
void DataManager::updatePowerData(){
    float hpPer = getNowHp()*1.0/getSingleData(HP);
    float spPer = getNowSp()*1.0/getSingleData(SP);
    
    //先叠加所有绝对数值,然后乘上两个相对加成
    for (int i=0; i<BIG_NUM; i++) {
        //其他影响可以为负数，但是最后的属性不能为负
        powerData[i]=(initData[i]+growData[i]*getLevel()+equipDataAbsolute[i]+abilityDataAbsolute[i])*equipDataRelative[i]*abilityDataRelative[i];
        if(powerData[i]<=0&&i<SMALL_NUM){
            CCLOG("%d什么鬼，能力怎么变成负数了",i);
        }
    }
    
    //<=0应该是初始状态，所以让当前蓝量和血量变成和上限相同
    if(getNowHp()<=0){
        setNowHp(getSingleData(HP));
    }else{
        setNowHp(getSingleData(HP)*hpPer);
    }
    if(getNowSp()<=0){
        setNowSp(getSingleData(SP));
    }else{
        setNowSp(getSingleData(SP)*spPer);
    }

    return;
}
int DataManager::getSingleData(int whichData){
    return powerData[whichData];
}
void DataManager::recovery(float dt){
    if(getNowHp()>0&&getNowHp()<getSingleData(HP)){
        setNowHp(getNowHp()+getSingleData(HPR)/(R_NUM/R_TICKTIME));
        if(getNowHp()>getSingleData(HP)){
            setNowHp(getSingleData(HP));
        }
    }
    if(getNowSp()<getSingleData(SP)){
        setNowSp(getNowSp()+getSingleData(SPR)/(R_NUM/R_TICKTIME));
        if(getNowSp()>getSingleData(SP)){
            setNowSp(getSingleData(SP));
        }
    }
}
void DataManager::purge(){
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
