//
//  GameLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//
//

#ifndef __RunQuickly__GameLayer__
#define __RunQuickly__GameLayer__

#include "cocos2d.h"
#include "CCEditBox.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#define WINSIZE GameLayer::instance()->winSize
#define FONT_NAME "FZYHJW--GB1-0" 

class GameLayer : public CCLayer, public CCEditBoxDelegate {
public:
    static CCScene* scene();
    static GameLayer* instance();
    bool init();
    // 得到屏幕尺寸
    CCSize winSize;
    void beginShit();
    void endShit();
    void IncreateInner();
    void makeAnim(const char* str,int index);
    void aniEnd(CCObject *pSender);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
private:
    CCEditBox *nameEditbix, *monthEditBox;
    CCLabelTTF *monyEarn;
    double monthPay;
    const char* name;
    double rate;
    bool gameBegin;
    enum {
        TYPE_NAME = 1,
        TYPE_MONTH
    }EDITBOX_TYPE;
};

#endif /* defined(__RunQuickly__GameLayer__) */