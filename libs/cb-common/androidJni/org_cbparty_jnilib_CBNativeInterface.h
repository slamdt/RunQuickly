//
//  org_cbparty_jnilib_CBNativeInterface.h
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//
#include <jni.h>

#ifndef __RunQuickly__org_cbparty_jnilib_CBNativeInterface__
#define __RunQuickly__org_cbparty_jnilib_CBNativeInterface__

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Class:     org_cbparty_jnilib_CBNativeInterface
     * Method:    CallC
     * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_org_cbparty_jnilib_CBNativeInterface_CallC
    (JNIEnv *, jobject, jstring, jstring);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__RunQuickly__org_cbparty_jnilib_CBNativeInterface__) */
