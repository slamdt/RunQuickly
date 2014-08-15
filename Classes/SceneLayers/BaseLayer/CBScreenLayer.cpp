//
//  CBScreenLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-15.
//
//

#include "CBScreenLayer.h"

bool CBScreenLayer::init() {
    if (!CBLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    setIsSwallowTouch(true);
    return true;
}