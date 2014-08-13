//
//  cb_jni.h
//  RunQuickly
//
//  Created by yuyu on 14-8-12.
//
//

#ifndef __RunQuickly__cb_jni__
#define __RunQuickly__cb_jni__


#include "cocos2d.h"
#include <platform/android/jni/JniHelper.h>

//c++调用java
const char kCPNativeJavaClassName[] = "org.cbparty.jnilib.CBNativeInterface";
const char kCPNativeJavaMethodName[] = "NativeInvoke";

extern "C"
{
    extern std::string cpCallJava(const std::string &class_name, const std::string &method_name, const std::string &param1, const std::string &param2);
    extern std::string cpCallJavaSimple(const std::string method, const std::string &param);
}


#endif /* defined(__RunQuickly__cb_jni__) */
