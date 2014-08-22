//
//  RunQuicklyAppDelegate.cpp
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "CBBackGroundManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEglView = CCEGLView::sharedOpenGLView();
    //===================多分辨率处理========================
    pDirector->setOpenGLView(pEglView);
    pDirector->setContentScaleFactor(2);
    CCSize winSize = pDirector->getWinSize();
    CCLOG("original frame size:%f, %f", pEglView->getFrameSize().width, pEglView->getFrameSize().height);
    CCLOG("winsize is : %f,%f",winSize.width,winSize.height);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS 
    if (getTargetPlatform()== kTargetIpad) {
        pEglView->setDesignResolutionSize(320, 480, kResolutionShowAll);
        
    } else {
        if(pEglView->getFrameSize().height == 1136) {
            pEglView->setDesignResolutionSize(320, 568, kResolutionShowAll);
        }
        else {
            pEglView->setDesignResolutionSize(320, 480, kResolutionShowAll);
        }
    }
#else
    int ratioLow = 1500;
    int ratioHigh = 1775;
    
    int targetHeight = pEglView->getFrameSize().height;
    int targetWidth = pEglView->getFrameSize().width;
    
    if (targetWidth * ratioHigh < targetHeight * 1000) {
        CCLog("taller than iPhone 5");
        pEglView->setDesignResolutionSize(320, 568, kResolutionShowAll);
    } else if (targetWidth * ratioHigh == targetHeight * 1000) {
        CCLog("same ratio with iPhone 5");
        pEglView->setDesignResolutionSize(320, 568, kResolutionShowAll);
    } else if (targetWidth * ratioLow == targetHeight * 1000) {
        CCLog("same ratio with iPhone 4");
        pEglView->setDesignResolutionSize(320, 480, kResolutionShowAll);
    } else if (targetWidth * ratioLow > targetHeight * 1000) {
        CCLog("wider than iPhone 4");
        pEglView->setDesignResolutionSize(320,
                                          480, kResolutionExactFit);
    } else {
        CCLog("between iPhone 4 and iPhone 5");
        pEglView->setDesignResolutionSize(320,
                                          pEglView->getFrameSize().height / pEglView->getFrameSize().width * 320, kResolutionShowAll);
    }
#endif
    CCLOG("new frame size:%f, %f", CCEGLView::sharedOpenGLView()->getFrameSize().width, CCEGLView::sharedOpenGLView()->getFrameSize().height);
    
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    CCDirector::sharedDirector()->setDepthTest(false);

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CBBackGroundManager::shared()->enterBackGround();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CBBackGroundManager::shared()->enterForeGround();
}
