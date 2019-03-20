//
//  PhysicManager.cpp
//  battleheart
//
//  Created by finalObject on 2018/12/19.
//

#include "PhysicManager.hpp"
#include "BaseRole.hpp"
#include <time.h>
PhysicManager * PhysicManager::create(vector<BaseRole*> *roles){
    PhysicManager * physicManager = new PhysicManager();
    if(physicManager && physicManager->init(roles)){
        physicManager->autorelease();
    }
    else{
        CC_SAFE_DELETE(physicManager);
        return nullptr;
    }
    return physicManager;
}
bool PhysicManager::init(vector<BaseRole*> *roles){
    this->roles = roles;
    schedule(CC_SCHEDULE_SELECTOR(PhysicManager::statesUpdate), 1/60);
    return true;
}
void PhysicManager::statesUpdate(float dt){
    for (int i=0; i<roles->size(); i++) {
        //碰撞检测
        auto role1 = roles->at(i);
        for (int j=i+1; j<roles->size(); j++) {
            auto role2 = roles->at(j);
            dis = sqrt(pow(role1->getPositionX()-role2->getPositionX(),2)+pow((role1->getPositionY()*Y_SCALE-role2->getPositionY()*Y_SCALE),2));
            if (dis<role1->getPlace()+role2->getPlace()){
                changePlace(i,j);
            }
        }
        
        //图层设置
        auto poX =-role1->getPositionY();
        role1->setLocalZOrder(poX);
    }
    
}
void PhysicManager::changePlace(int i,int j){
    auto role1 = roles->at(i);
    auto role2 = roles->at(j);
    int c1,c2;
    if (role1->getWeight()>role2->getWeight()){
        c1=i,c2=j;
    }else if(role1->getWeight()<role2->getWeight()){
        c1=j,c2=i;
    }else{
        if(rand()%2==0){
            c1=i,c2=j;
        }else{
            c1=j,c2=i;
        }
    }
    //如果位置完全重叠
    
    if(role1->getPosition()==role2->getPosition()){
        int randAng = rand()%360;
        float shiftX = (roles->at(c2)->getPlace()+roles->at(c1)->getPlace())*cos(randAng*1.0/(M_PI * 2));
        float shiftY = (roles->at(c2)->getPlace()+roles->at(c1)->getPlace())*sin(randAng*1.0/(M_PI * 2));
        roles->at(c2)->setPosition(roles->at(c1)->getPosition()+Vec2(shiftX,shiftY));
        
    }else{
        //没有完全重叠
        roles->at(c2)->setPosition((roles->at(c2)->getPosition()-roles->at(c1)->getPosition())*(roles->at(c2)->getPlace()+roles->at(c1)->getPlace())/dis+roles->at(c1)->getPosition());
        
    }
    return;
}
