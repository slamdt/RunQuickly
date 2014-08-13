//
//  CBPlatformAndroid.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#include "CBPlatform.h"
#include "cb_jni.h"

void CBPlatformAndroid::quitGame() {
    CCLOG("c++ call quit game");
    cpCallJavaSimple("quitGame","");
}
