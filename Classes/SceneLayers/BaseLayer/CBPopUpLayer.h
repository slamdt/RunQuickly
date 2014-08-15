//
//  CBPopUpLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#ifndef __RunQuickly__CBPopUpLayer__
#define __RunQuickly__CBPopUpLayer__

#include "CBLayer.h"

class CBPopUpLayer : public CBLayer {
public:
    virtual bool init();
    // 捕获触摸点
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
};
#endif /* defined(__RunQuickly__CBPopUpLayer__) */
