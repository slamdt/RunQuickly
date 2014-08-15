//
//  CBLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#include "CBLayer.h"

bool CBLayer::init() {
    if(!CCLayer::init()) {
        return false;
    }
    return true;
}