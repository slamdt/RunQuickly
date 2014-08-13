//
//  CBPlatform.h
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#ifndef __RunQuickly__CBPlatform__
#define __RunQuickly__CBPlatform__

#include <iostream>

class CBPlatformImpl {
public:
    virtual void quitGame() {};
};

class CBPlatform {
public:
    static CBPlatformImpl* _shared;
    static CBPlatformImpl* shared();
private:
};

class CBPlatformAndroid : public CBPlatformImpl {
public:
    virtual void quitGame();
    
};

#endif /* defined(__RunQuickly__CBPlatform__) */
