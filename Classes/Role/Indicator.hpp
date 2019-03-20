//
//  Indicator.hpp
//  battleheart
//
//  Created by finalObject on 2019/1/28.
//

#ifndef Indicator_hpp
#define Indicator_hpp





#include <stdio.h>
#include "allHead.hpp"
USING_NS_CC;
using namespace std;

class BaseRole;
class Indicator:public Node{
public:
    static Indicator * create( BaseRole * thisRole);
    bool init( BaseRole * thisRole);
    virtual void draw(Renderer* renderer,const Mat4& transform,uint32_t flags) override;
    
    void onDraw(const Mat4& transform,uint32_t flags);
    CustomCommand _customCommand;
    void purge();
public:
    BaseRole * thisRole;
    Vec2 shiftIndicator;
//    vector<int> circles;
 
    
};

#endif /* Indicator_hpp */
