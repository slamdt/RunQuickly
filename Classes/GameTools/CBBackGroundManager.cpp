//
//  CBBackGroundManager.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-22.
//
//

#include "CBBackGroundManager.h"
#include "CBPlatform.h"
#include "ShitLayer.h"

SINGLETON_IMPL(CBBackGroundManager);

bool CBBackGroundManager::init() {
    CCLOG("do noting");
    return true;
}

void CBBackGroundManager::enterBackGround() {
    if (ShitLayer::getShitState()) {
        CBPlatform::shared()->enterBackGround("earnInBG");
    } else {
        CBPlatform::shared()->enterBackGround("");
    }
}

void CBBackGroundManager::enterForeGround() {
    CBPlatform::shared()->enterForeGround();
}