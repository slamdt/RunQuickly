//
//  CBShareManager.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#include "CBShareManager.h"

SINGLETON_IMPL(CBShareManager)
bool CBShareManager::init() {
    CCLOG("do nothing");
    return true;
}

void CBShareManager::shotScreen() {
    GameLayer_->addChild(shotScreenLayer::create());
}


bool shotScreenLayer::init() {
    if (!CBPopUpLayer::init()) {
        return false;
    }
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture *texture = CCRenderTexture::create(winsize.width, winsize.height, kCCTexture2DPixelFormat_RGBA8888);
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
    getFileName();
    //texture->saveToFile(file_name.c_str(), kCCImageFormatJPEG);//不能用这个，因为文件这个方法的内部实现文件路径改变了
    //用CCImage的saveTofile方法，他内部的实现不会重新组合文件路径
    CCImage *pImage = texture->newCCImage();
    pImage->saveToFile(file_name.c_str());
    CC_SAFE_DELETE(pImage);
    
    CCSprite *textureNode = texture->getSprite();
    textureNode->setScale(0.7);
    textureNode->retain();
    textureNode->removeFromParentAndCleanup(true);
    textureNode->setPosition(ccp(winsize.width/2,winsize.height/2));
//    textureNode->setFlipX(true);//左右（水平）翻转
    textureNode->setFlipY(true);//上下（竖直）翻转
    this->addChild(textureNode);
    
    CCMenuItemLabel *shareBtn = CCMenuItemLabel::create(CCLabelTTF::create("分享", FONT_NAME, 20), this, menu_selector(shotScreenLayer::shareBtnDown));
    shareBtn->setColor(ccc3(255, 0, 0));
    shareBtn->setPosition(ccp(winsize.width * 0.4, winsize.height * 0.2));
    
    CCMenuItemLabel *backBtn = CCMenuItemLabel::create(CCLabelTTF::create("返回", FONT_NAME, 20),this,menu_selector(shotScreenLayer::back));
    backBtn->setColor(ccc3(255, 0, 0));
    backBtn->setPosition(ccp(winsize.width * 0.6, winsize.height * 0.2));
    
    CCMenu *menu = CCMenu::create(shareBtn,backBtn,NULL);
    menu->setTouchPriority(getTouchPriority());
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    
    return true;
}

void shotScreenLayer::getFileName() {
    std::string dir = CBPlatform::shared()->MakeFilePath(cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath());
    file_name = dir + "best.jpg";
}

void shotScreenLayer::shareBtnDown() {
    const char *tip = "赚这么多钱，你比城步吴彦祖都牛逼！";
    CBPlatform::shared()->sharedResult(file_name.c_str(), tip);
}

void shotScreenLayer::back() {
    this->removeFromParentAndCleanup(true);
    CBPlatform::shared()->showPopAd();
}