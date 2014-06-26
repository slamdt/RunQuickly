//
//  GameLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//
//

#ifndef __RunQuickly__GameLayer__
#define __RunQuickly__GameLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class GameLayer : public CCLayer {
public:
    static CCScene* scene();
    static GameLayer* instance();
    bool init();
private:
};

#endif /* defined(__RunQuickly__GameLayer__) */