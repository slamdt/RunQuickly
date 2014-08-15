//
//  CBScreenLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-8-15.
//
//

#ifndef __RunQuickly__CBScreenLayer__
#define __RunQuickly__CBScreenLayer__

#include "CBLayer.h"

class CBScreenLayer : public CBLayer {
public:
    virtual bool init();
    
    // 捕获触摸点
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    
};

#endif /* defined(__RunQuickly__CBScreenLayer__) */
