//
//  cb_jni.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-12.
//
//

#include "cb_jni.h"


extern "C"
{
    std::string cpCallJava(const std::string &class_name, const std::string &method_name,
                           const std::string &param1, const std::string &param2) {
        
        cocos2d::JniMethodInfo methodInfo;
        
        if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, class_name.c_str(),
                                                      method_name.c_str(), "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
            CCLOG("CBNativeInterface not found!, class:%s, method:%s", class_name.c_str(), method_name.c_str());
            return "";
        }
        
        jobject obj = NULL;
        jstring jstr = NULL;
        jstring arg1 = methodInfo.env->NewStringUTF(param1.c_str());
        jstring arg2 = methodInfo.env->NewStringUTF(param2.c_str());
        obj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, arg1, arg2);
        jstr = (jstring) obj;
        methodInfo.env->DeleteLocalRef(arg1);
        methodInfo.env->DeleteLocalRef(arg2);
        
        jboolean isCopy=false;
        const char *cstr = methodInfo.env->GetStringUTFChars(jstr, &isCopy);
        methodInfo.env->DeleteLocalRef(obj);
        
        std::string ret = "";
        if(isCopy && cstr){
            ret = std::string(cstr);
            methodInfo.env->ReleaseStringUTFChars(jstr, cstr);
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return ret;
    }
    
    std::string cpCallJavaSimple(const std::string method, const std::string &param) {
        return cpCallJava(kCPNativeJavaClassName, kCPNativeJavaMethodName, method, param);
    }
}