//
//  Indicator.cpp
//  battleheart
//
//  Created by finalObject on 2019/1/28.
//

#include "Indicator.hpp"
#include "BaseRole.hpp"
Indicator * Indicator::create(BaseRole * thisRole){
    Indicator * indicator = new Indicator();
    if(indicator && indicator->init(thisRole)){
        indicator->autorelease();
    }
    else{
        CC_SAFE_DELETE(indicator);
        return nullptr;
    }
    return indicator;
}

bool Indicator::init(BaseRole * thisRole){
    this->thisRole = thisRole;

    this->shiftIndicator = Vec2(0,thisRole->getPlace()*4.5);
    this->setScaleY(1.0/Y_SCALE);
    
    return true;
}
void Indicator::draw(Renderer* renderer,const Mat4& transform,uint32_t flags){
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Indicator::onDraw, this,transform,flags);
    renderer->addCommand(&_customCommand);
}

void Indicator::onDraw(const Mat4& transform,uint32_t flags){
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    int tmpR = 0;
    //先画体积圈
    DrawPrimitives::setDrawColor4B(200, 200, 255, 255);
    for(int i=0;i<INDICATOR_WIDTH;i++){
        DrawPrimitives::drawCircle(Point(0, 0),thisRole->getPlace()+i, M_PI * 2, 100, false);
    }
    tmpR = tmpR+INDICATOR_STEP+INDICATOR_WIDTH;
    
    //玩家控制圈
    if (thisRole->getIsControl()==true){
        DrawPrimitives::setDrawColor4B(51, 204, 0, 255);
        for(int i=0;i<INDICATOR_WIDTH;i++){
            DrawPrimitives::drawCircle(Point(0, 0),thisRole->getPlace()+i+tmpR, M_PI * 2, 100, false);
        }
        tmpR = tmpR+INDICATOR_STEP+INDICATOR_WIDTH;
    }
    
    //被选择圈
    if (thisRole->getIsFocus()==true){
        switch (this->thisRole->getForce()) {
            case FORCE_0:
                DrawPrimitives::setDrawColor4B(51, 153, 255, 255);
                break;
            case FORCE_1:
                DrawPrimitives::setDrawColor4B(204, 51, 51, 255);
                break;
            case FORCE_2:
                DrawPrimitives::setDrawColor4B(255, 255, 0, 255);
                break;
            default:
                DrawPrimitives::setDrawColor4B(0,0,0,255);
                break;
        }
        
        for(int i=0;i<INDICATOR_WIDTH;i++){
            DrawPrimitives::drawCircle(Point(0, 0),thisRole->getPlace()+i+tmpR, M_PI * 2, 100, false);
        }
    }
    

    
    
    
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}

void Indicator::purge(){
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParent();
}
