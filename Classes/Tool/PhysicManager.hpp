//
//  PhysicManager.hpp
//  battleheart
//
//  Created by finalObject on 2018/12/19.
//

#ifndef PhysicManager_hpp
#define PhysicManager_hpp

#include <stdio.h>
USING_NS_CC;
using namespace std;

class BaseRole;
class PhysicManager:public Node{
public:
    static PhysicManager * create(vector<BaseRole*> *roles);
    bool init(vector<BaseRole*> *roles);
    void statesUpdate(float dt);
    void changePlace(int i,int j);
public:
    vector<BaseRole*> *roles;
    double dis;

    
    
    
    
};
#endif /* PhysicManager_hpp */
