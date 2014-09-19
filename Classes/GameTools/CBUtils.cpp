//
//  CBUtils.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-29.
//
//

#include "CBUtils.h"

const char* CBStringFormInterger(int value) {
    CCString *str = CCString::createWithFormat("%d",value);
    return str->getCString();
}