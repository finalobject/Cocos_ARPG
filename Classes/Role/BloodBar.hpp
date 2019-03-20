//
//  BloodBar.hpp
//  battleheart
//
//  Created by finalObject on 2018/12/18.
//

#ifndef BloodBar_hpp
#define BloodBar_hpp

#include <stdio.h>
USING_NS_CC;
class BaseRole;
class BloodBar:public Node{
public:
    static BloodBar * create( BaseRole * thisRole);
    bool init( BaseRole * thisRole);
    virtual void draw(Renderer* renderer,const Mat4& transform,uint32_t flags) override;

    void onDraw(const Mat4& transform,uint32_t flags);
    CustomCommand _customCommand;
    void purge();
public:
    BaseRole * thisRole;
    Vec2 shiftBar;
    CC_SYNTHESIZE(int, barWidth, BarWidth);
    CC_SYNTHESIZE(int, barHeight, BarHeight);
    

    
    
};
#endif /* BloodBar_hpp */
