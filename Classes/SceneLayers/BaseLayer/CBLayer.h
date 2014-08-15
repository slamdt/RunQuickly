//
//  CBLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#ifndef __RunQuickly__CBLayer__
#define __RunQuickly__CBLayer__
#include "cocos2d.h"
using namespace cocos2d;

class CBLayer : public CCLayer {
    CC_SYNTHESIZE(int, _touchPriority, TouchPriority);
    CC_SYNTHESIZE(bool, _isSwallowTouch, IsSwallowTouch);
public:
    CBLayer(): _touchPriority(0),_isSwallowTouch(false)
    {
        
    }
    
    virtual bool init();
    
    // 覆盖CCLayer实现，注册触摸事件派发器
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, _touchPriority, _isSwallowTouch);
    }
    
    // 覆盖CCLayer缺省实现，默认不捕获触摸点
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){return false;}
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){}
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){}
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent){}
};

#endif /* defined(__RunQuickly__CBLayer__) */
