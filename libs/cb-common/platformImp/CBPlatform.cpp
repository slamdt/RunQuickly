//
//  CBPlatform.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#include "CBPlatform.h"
#include "cocos2d.h"

CBPlatformImpl* CBPlatform::_shared = NULL;

CBPlatformImpl* CBPlatform::shared() {
    if (!_shared) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        _shared = new CBPlatformAndroid();
#else
        _shared = new CBPlatformImpl();
#endif
    }
    return _shared;
}