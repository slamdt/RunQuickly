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
#include "CBPlatform.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#define WINSIZE GameLayer::instance()->winSize
#define FONT_NAME "FZYHJW--GB1-0" 

enum LAYER_TYPE{
    SHIT_LAYER = 1,
};

class GameLayer : public CCLayer{
public:
    static CCScene* scene();
    static GameLayer* instance();
    bool init();
    
    void CreateLayer(LAYER_TYPE type);
    // 得到屏幕尺寸
    CCSize winSize;
    
    //返回键调用函数
    virtual void keyBackClicked();
private:
};

#endif /* defined(__RunQuickly__GameLayer__) */