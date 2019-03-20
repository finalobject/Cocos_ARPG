//
//  AbilityMaster.cpp
//  battleheart
//
//  Created by finalObject on 2018/12/22.
//

#include "AbilityMaster.hpp"
#include "StandAbility.hpp"
#include "MoveAbility.hpp"
#include "AttackAbility.hpp"
#include "BaseRole.hpp"
USING_NS_CC;
static AbilityMaster* abilityMaster=nullptr;
AbilityMaster * AbilityMaster::getInstance(){
    if (abilityMaster==nullptr){
        abilityMaster=new (std::nothrow)AbilityMaster();
        abilityMaster->init();
    }
    return abilityMaster; 
}
bool AbilityMaster::init(){
    //初始化abilityMap
    for (int i=0; i<ROLES_MAXNUM; i++) {
        for (int j=0; j<KEYS_MAXNUM; j++) {
            abilityMap[i][j]=0;
        }
    }
    return true;
}
void AbilityMaster::addAbilityById(int ability,BaseRole * thisRole,char key){
    //首先在abilityMap上根据角色id和键位绑定上对应的技能种类
    //然后在对应技能的map上创建好技能
    if (thisRole->getId()>=ROLES_MAXNUM){
        CCLOG("Id is too big");
        return;
    }
    //绑定技能种类
    //如果已经有技能，就先删除
    if(abilityMap[thisRole->getId()][key-'a']!=0){removeAbilityById(thisRole, key);}
    abilityMap[thisRole->getId()][key-'a']=ability;
    
    switch (ability) {
        case STAND:
        {
            auto tmpStand = StandAbility::create(thisRole);
            tmpStand->retain();
            standMap.insert(thisRole->getId(), tmpStand);
            break;
        }
        case MOVE:
        {
            auto tmpMove = MoveAbility::create(thisRole);
            tmpMove->retain();
            moveMap.insert(thisRole->getId(), tmpMove);
            break;
        }
        case ATTACK:
        {
            auto tmpAttack = AttackAbility::create(thisRole);
            tmpAttack->retain();
            attackMap.insert(thisRole->getId(), tmpAttack);
            break;
        }
        default:
            break;
    }
}
int AbilityMaster::getAbility(BaseRole * thisRole,char key){
    return abilityMap[thisRole->getId()][key-'a'];
}
int AbilityMaster::spell(BaseRole * thisRole,char key){
    int ability = getAbility(thisRole, key);
    switch (ability) {
        case STAND:
        {
            standMap.at(thisRole->getId())->start();
            return NICE;
            break;
        }
        case MOVE:
        {
            return NEED_POINT;
            break;
        }
        case ATTACK:
        {
            return NEED_ROLE;
            break;
        }
        default:
            break;
    }
    return NICE;
    
}
void AbilityMaster::spell(BaseRole * thisRole,char key,Vec2 targetPlace){
    int ability = getAbility(thisRole, key);
    switch (ability) {
        case MOVE:
        {
            moveMap.at(thisRole->getId())->start(targetPlace);
            break;
        }
        default:
        {
            CCLOG("the skill does not need a point");
            break;
        }
    }
    return;
}
void AbilityMaster::spell(BaseRole * thisRole,char key,BaseRole * tarRole){
    int ability = getAbility(thisRole, key);
    switch (ability) {
        case ATTACK:
        {
            attackMap.at(thisRole->getId())->start(tarRole);
            break;
        }
        default:
        {
            CCLOG("the skill does not need a role");
            break;
        }
    }
    return;
}
void AbilityMaster::stopAbilityForRole(int ability,BaseRole* thisRole){
    switch (thisRole->getRecentAbility()) {
        case STAND:
        {
            standMap.at(thisRole->getId())->stop();
            break;
        }
        case MOVE:{
            moveMap.at(thisRole->getId())->stop();
            break;
        }
        case ATTACK:{
            attackMap.at(thisRole->getId())->stop();
            break;
        }
        default:
            break;
    }
    thisRole->setRecentAbility(ability);

    return;
}
void AbilityMaster::removeAbilityById(BaseRole * thisRole,char key){
    
    switch (abilityMap[thisRole->getId()][key-'a']) {
        case STAND:
        {
            standMap.at(thisRole->getId())->release();
            standMap.erase(thisRole->getId());
            break;
        }
        case MOVE:
        {
            moveMap.at(thisRole->getId())->release();
            moveMap.erase(thisRole->getId());
            break;
        }
        case ATTACK:
        {
            attackMap.at(thisRole->getId())->release();
            attackMap.erase(thisRole->getId());
            break;
        }
        default:
            break;
    }
    abilityMap[thisRole->getId()][key-'a']=0;
    return;
}
//回收部分
void AbilityMaster::removeRole(BaseRole * thisRole){
    addDeadRole(thisRole);
    removeAbilityById(thisRole,'x');
    removeAbilityById(thisRole,'a');
    removeAbilityById(thisRole,'s');
    return;
}
void AbilityMaster::addDeadRole(BaseRole * thisRole){
    this->deadRoles.push_back(thisRole);
    return;
}
//判断死了没
bool AbilityMaster::areYouDead(BaseRole * thisRole){
    for (int i=0; i<deadRoles.size(); i++) {
        if(deadRoles.at(i)==thisRole){
            return true;
        }
    }
    return false;
}
