//
//  CBPlatformAndroid.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#include "CBPlatform.h"
#include "cb_jni.h"
#include "cocos2d.h"
using namespace cocos2d;

void CBPlatformAndroid::quitGame() {
    CCLOG("c++ call quit game");
    cpCallJavaSimple("quitGame","");
}

void CBPlatformAndroid::sharedResult(const char *fileName, const char *tips) {
    const char* param = CCString::createWithFormat("%s###%s",fileName,tips)->getCString();
    cpCallJavaSimple("Share", param);
}

std::string CBPlatformAndroid::MakeFilePath(std::string cocos2dFilePath) {
    return cpCallJavaSimple("MakeFilePath", cocos2dFilePath);
}

void CBPlatformAndroid::showAdWall() {
    cpCallJavaSimple("showAdWall", "");
}

void CBPlatformAndroid::showPopAd() {
    cpCallJavaSimple("showPopAd", "");
}