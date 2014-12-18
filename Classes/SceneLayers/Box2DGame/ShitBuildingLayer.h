//
//  ShitBuildingLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-12-15.
//
//

#ifndef __RunQuickly__ShitBuildingLayer__
#define __RunQuickly__ShitBuildingLayer__

#include "GameLayer.h"
#include "Box2D/Box2D.h"

const int ptm_ratio = 32;
const float GRAVITY = 15.0f;

class ShitBuildingLayer : public CBScreenLayer {
public:
    virtual bool init();
    CREATE_FUNC(ShitBuildingLayer);
    
    void update(float dt);
    void makeScreenEgdge();
    void makeShit();
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
private:
    b2World *world;
    b2Joint *disJoint;
};



#endif /* defined(__RunQuickly__ShitBuildingLayer__) */
