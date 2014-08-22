//
//  CBPlatform.h
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#ifndef __RunQuickly__CBPlatform__
#define __RunQuickly__CBPlatform__

#include "cocos2d.h"
using namespace cocos2d;

class CBPlatformDelegate {
public:
    virtual void updateEarned(int extraTime) {};
};

class CBPlatformImpl {
public:
    virtual void quitGame() {};
    virtual void sharedResult(const char* fileName, const char* tips) {};
    virtual std::string MakeFilePath(std::string cocos2dFilePath) {return "";};
    virtual void showAdWall() {};
    virtual void showPopAd() {};
    virtual void enterBackGround(const char* method) {};
    virtual void enterForeGround() {};
    void setPlatformDelegate(CBPlatformDelegate *delgate) {_delegate = delgate;};
    CBPlatformDelegate *getPlatformDelegate() {return _delegate;};
private:
    CBPlatformDelegate *_delegate;
};

class CBPlatform {
public:
    static CBPlatformImpl* _shared;
    static CBPlatformImpl* shared();
};

class CBPlatformAndroid : public CBPlatformImpl {
public:
    virtual void quitGame();
    virtual void sharedResult(const char* fileName, const char* tips);
    virtual std::string MakeFilePath(std::string cocos2dFilePath);
    virtual void showAdWall();
    virtual void showPopAd();
    virtual void enterBackGround(const char* method);
    virtual void enterForeGround() ;
};
#endif /* defined(__RunQuickly__CBPlatform__) */
