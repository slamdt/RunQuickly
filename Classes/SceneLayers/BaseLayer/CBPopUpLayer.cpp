//
//  CBPopUpLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#include "CBPopUpLayer.h"

bool CBPopUpLayer::init() {
    if (!CBLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    setIsSwallowTouch(true);
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 170), winsize.width, winsize.height);
    this->addChild(layer);
    return true;
}