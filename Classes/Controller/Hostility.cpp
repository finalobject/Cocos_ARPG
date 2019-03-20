//
//  Hostility.cpp
//  battleheart
//
//  Created by finalObject on 2019/1/30.
//

#include "Hostility.hpp"
#include "BaseRole.hpp"
#include "HostilityTick.hpp"
#include "AbilityMaster.hpp"

static Hostility* hostility = nullptr;
Hostility * Hostility::getInstance(){
    if(hostility == nullptr){
        hostility = new (std::nothrow)Hostility();
        hostility->init();
    }
    return hostility;
}

bool Hostility::init(){
    this->roles = nullptr;
    //初始化所有仇恨
    for(int i=0;i<ROLES_MAXNUM;i++){
        for(int j=0;j<ROLES_MAXNUM;j++){
            selfHostility[i][j]=0;
        }
    }
    return true;
}
void Hostility::clearAllHostility(){
    for(int i=0;i<ROLES_MAXNUM;i++){
        for(int j=0;j<ROLES_MAXNUM;j++){
            selfHostility[i][j]=0;
        }
    }
    return;
}
void Hostility::setRoles(vector<BaseRole *> *roles){
    this->roles = roles;
}
//添加仇恨，第一个参数是被攻击的那个人，第二个参数是攻击人，然后就是仇恨数量，然后是多少时间消除，默认10s
void Hostility::addHostilityByHit(BaseRole* toWho,BaseRole* fromWho,int number,int delayTime){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return;}
    //添加自己的仇恨
    selfHostility[toWho->getId()][fromWho->getId()]+=number;
    //添加队伍仇恨
    int forceFlag = toWho->getForce();
    for(int i=0;i<roles->size();i++){
        if(roles->at(i)->getForce()==forceFlag&&roles->at(i)->getId()!=toWho->getId()){
            selfHostility[roles->at(i)->getId()][fromWho->getId()]+=number*TEAM_SCALE;
        }
    }

    this->addChild(HostilityTick::create(toWho, fromWho, number, delayTime, HIT));

    
    return;
}

void Hostility::removeHostilityByHit(BaseRole* toWho,BaseRole* fromWho,int number){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return;}
    if(toWho==nullptr||fromWho==nullptr){return;}
    if(AbilityMaster::getInstance()->areYouDead(toWho)||AbilityMaster::getInstance()->areYouDead(fromWho)){
        return;
    }
    //添加自己的仇恨
    selfHostility[toWho->getId()][fromWho->getId()]-=number;
    
    
    //添加队伍仇恨
    int forceFlag = toWho->getForce();
    for(int i=0;i<roles->size();i++){
        if(roles->at(i)->getForce()==forceFlag&&roles->at(i)->getId()!=toWho->getId()){
            selfHostility[roles->at(i)->getId()][fromWho->getId()]-=number*TEAM_SCALE;
        }
    }
    return;
}


//回复，会添加其他势力仇恨。回复势力是按照被回复者为基准，不是施法者
void Hostility::addHostilityByHeal(BaseRole* toWho,BaseRole* fromWho,int number,int delayTime){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return;}
    int forceFlag = toWho->getForce();
    for(int i=0;i<roles->size();i++){
        if(roles->at(i)->getForce()!=forceFlag){
            selfHostility[roles->at(i)->getId()][fromWho->getId()]+=number*HEAL_SCALE;
        }
    }
    //然后需要延迟之后，减去这部分仇恨
    //怎么写呢
    HostilityTick::create(toWho, fromWho, number, delayTime, HEAL);
    
    return;
    
}
void Hostility::removeHostilityByHeal(BaseRole* toWho,BaseRole* fromWho,int number){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return;}
    int forceFlag = toWho->getForce();
    for(int i=0;i<roles->size();i++){
        if(roles->at(i)->getForce()!=forceFlag){
            selfHostility[roles->at(i)->getId()][fromWho->getId()]-=number*HEAL_SCALE;
        }
    }
}
//返回一个没有死掉的仇恨最高的目标
BaseRole* Hostility::getTarget(BaseRole* who){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return nullptr;}
    long int maxHostility =0 ;
    BaseRole* targetRole = nullptr;
    //直接这样搜索出来的肯定是还活着的
    for(int i=0;i<roles->size();i++){
        if(selfHostility[who->getId()][roles->at(i)->getId()]>maxHostility){
            maxHostility = selfHostility[who->getId()][roles->at(i)->getId()];
            targetRole = roles->at(i);
        }
    }
    //肯定返回空
    return targetRole;
}
void Hostility::clearHostilityById(int id){
    if(roles==nullptr){CCLOG("ROLES IS NULLPTR");return;}
    for(int i=0;i<ROLES_MAXNUM;i++){
        selfHostility[i][id]=0;
    }
}
void Hostility::purge(){
    this->roles = nullptr;
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
