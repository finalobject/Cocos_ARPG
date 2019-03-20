//
//  FlyBlood.hpp
//  battleheart-desktop
//
//  Created by finalObject on 2018/12/15.
//

#ifndef FlyBlood_hpp
#define FlyBlood_hpp

//物理红，暴击橙色，魔法蓝，暴击紫色，真实白
#include <stdio.h>
USING_NS_CC;
using namespace std;



class FlyBlood:public Node{
public:
    static FlyBlood * create(int type,int damage);
    bool init(int type,int damage);
    void start();
    void end();
public:
    Label * label;

};

#endif /* FlyBlood_hpp */
