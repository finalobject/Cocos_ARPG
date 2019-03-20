//
//  BloodBar.cpp
//  battleheart
//
//  Created by finalObject on 2018/12/18.
//

#include "BloodBar.hpp"
#include "BaseRole.hpp"
#include "DataManager.hpp"
BloodBar * BloodBar::create(BaseRole * thisRole){
    BloodBar * bloodBar = new BloodBar();
    if(bloodBar && bloodBar->init(thisRole)){
        bloodBar->autorelease();
    }
    else{
        CC_SAFE_DELETE(bloodBar);
        return nullptr;
    }
    return bloodBar;
}

bool BloodBar::init(BaseRole * thisRole){
    this->thisRole = thisRole;
    this->setBarWidth(80);
    this->setBarHeight(17);
    this->shiftBar = Vec2(-getBarWidth()/2,thisRole->getPlace()*4.5);


    return true;
}
void BloodBar::draw(Renderer* renderer,const Mat4& transform,uint32_t flags){
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(BloodBar::onDraw, this,transform,flags);
    renderer->addCommand(&_customCommand);
}

void BloodBar::onDraw(const Mat4& transform,uint32_t flags){
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    


    
    //画血条
    float spPer = thisRole->dataManager->getNowSp()*1.0F/thisRole->dataManager->getSingleData(SP);
    float hpPer = thisRole->dataManager->getNowHp()*1.0F/thisRole->dataManager->getSingleData(HP);
    
    Color4F color1,color2,color3;
    if (hpPer<0.3){
        color1 = Color4F(0.63,0,0,1);
        color2 = Color4F(0.78,0,0.27,1);
        color3 = Color4F(0.89,0.31,0.43,1);
    }else if(hpPer<0.6){
        color1 = Color4F(1,0.47,0,1);
        color2 = Color4F(1,0.71,0.05,1);
        color3 = Color4F(0.93,0.90,0.84,1);
    }else{
        color1 = Color4F(0,0.63,0,1);
        color2 = Color4F(0,0.78,0.27,1);
        color3 = Color4F(0.31,0.89,0.43,1);
    }
    
    float spWidthInAll = 0.35;
    Vec2 spStart = Vec2(1,1)+shiftBar;
    Vec2 spEnd =Vec2(barWidth-1,(barHeight-3)*spWidthInAll+1)+shiftBar;
    Vec2 hpStart =Vec2(1,(barHeight-3)*spWidthInAll+1+1)+shiftBar;
    Vec2 hpEnd = Vec2(barWidth-1,barHeight-1)+shiftBar;
    
    Vec2 spInStart = Vec2(2,2)+shiftBar;
    Vec2 spInEnd =Vec2(barWidth-1,(barHeight-3)*spWidthInAll+1)-Vec2(1,1)+shiftBar;
    Vec2 hpInStart =Vec2(1,(barHeight-3)*spWidthInAll+1+1)+Vec2(1,1)+shiftBar;
    Vec2 hpInEnd = Vec2(barWidth-2,barHeight-2)+shiftBar;
    //底座
    DrawPrimitives::drawSolidRect(Vec2(0,0)+shiftBar,Vec2(barWidth,barHeight)+shiftBar, Color4F(0.86, 0.78, 0.94, 1));
    //蓝条底框
    DrawPrimitives::drawSolidRect(spStart,spEnd, Color4F(0, 0, 0, 1));
    //红条底框
    DrawPrimitives::drawSolidRect(hpStart,hpEnd, Color4F(0, 0, 0, 1));
    
    //蓝条
    DrawPrimitives::drawSolidRect(spInStart,Vec2((spInEnd.x-spInStart.x)*spPer+spInStart.x,spInEnd.y),Color4F(0, 0.32,0.72, 1));
    //红条
    DrawPrimitives::drawSolidRect(hpInStart,Vec2((hpInEnd.x-hpInStart.x)*hpPer+hpInStart.x,hpInEnd.y),color1);
    DrawPrimitives::drawSolidRect(
                                  Vec2(hpInStart.x,(hpInEnd.y-hpInStart.y)*0.25+hpInStart.y),
                                  Vec2((hpInEnd.x-hpInStart.x)*hpPer+hpInStart.x,(hpInEnd.y-hpInStart.y)*0.45+hpInStart.y),
                                  color2);
    DrawPrimitives::drawSolidRect(
                                  Vec2(hpInStart.x,(hpInEnd.y-hpInStart.y)*0.45+hpInStart.y),
                                  Vec2((hpInEnd.x-hpInStart.x)*hpPer+hpInStart.x,(hpInEnd.y-hpInStart.y)*0.65+hpInStart.y),
                                  color3);
    //血量基数
    int step = 100;
    int maxHp = thisRole->dataManager->getSingleData(HP);
    DrawPrimitives::setDrawColor4B(0, 0, 0, 255);
    for (int i=step;i<maxHp-1;i=i+step){
        Vec2 tmp2 =Vec2((hpInEnd.x-hpInStart.x)*i/maxHp+hpInStart.x,hpInStart.y);
        Vec2 tmp1 =Vec2((hpInEnd.x-hpInStart.x)*i/maxHp+hpInStart.x,hpInEnd.y);
        if(i%(5*step)!=0){
            DrawPrimitives::drawLine(tmp1,(tmp2-tmp1)*0.6+tmp1);
        }else{
            DrawPrimitives::drawLine(tmp1,tmp2);
        }
//        DrawPrimitives::drawLine(tmp1,tmp2);
//        if (i%(5*step)==0){
//            DrawPrimitives::drawLine(tmp1+Vec2(1,0),tmp2+Vec2(1,0));
//        }
    }

    //DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(barWidth,barHeight), Color4F(0, 0, 0, 255));
//    DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
//    DrawPrimitives::drawRect(Vec2(0,0),Vec2(barWidth,barHeight));
//



    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}

void BloodBar::purge(){
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
