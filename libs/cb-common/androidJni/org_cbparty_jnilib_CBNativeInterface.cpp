//
//  org_cbparty_jnilib_CBNativeInterface.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#include "org_cbparty_jnilib_CBNativeInterface.h"
#include <iostream>
#include "cocos2d.h"
#include "CBPlatform.h"

JNIEXPORT jstring JNICALL Java_org_cbparty_jnilib_CBNativeInterface_CallC
(JNIEnv *env, jobject obj, jstring _jmethod, jstring _jparam) {
    std::string method = env->GetStringUTFChars(_jmethod, 0);
    std::string param = env->GetStringUTFChars(_jparam, 0);
    CCLOG("on Jni CallC, %s,%s",method.c_str(),param.c_str());
    if (method.compare("QuitGameSure") == 0) {
        cocos2d::CCDirector::sharedDirector()->end();
    } else if (method.compare("updateEarn") == 0) {
        CBPlatform::shared()->getPlatformDelegate()->updateEarned(atoi(param.c_str()));
    }
    return env->NewStringUTF("");
}