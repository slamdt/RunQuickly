//
//  Game2048Layer.h
//  RunQuickly
//
//  Created by yuyu on 14-8-28.
//
//

#ifndef __RunQuickly__Game2048Layer__
#define __RunQuickly__Game2048Layer__

#include "GameLayer.h"
#include "Game2048Item.h"

typedef enum {
    POS_1 = 0,
    POS_2,
    POS_3,
    POS_4,
    POS_5,
    POS_6,
    POS_7,
    POS_8,
    POS_9,
    POS_10,
    POS_11,
    POS_12,
    POS_13,
    POS_14,
    POS_15,
    POS_16
}ITEM_POS;

class Game2048Layer : public CBScreenLayer{
public:
    CREATE_FUNC(Game2048Layer);
    virtual bool init();
    void back();
    void updateItemStatus();
    void moveOver();
    bool elementExis(const std::vector<int> &vector, int element);
    
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
private:
    virtual ~Game2048Layer();
    CCPoint POS[16];
    std::vector<Game2048Item *> items;
    bool touchMoved;
    bool itemMoved;
    bool adjustOver;
    CCPoint startPoint;
    float itemSize;
};

#endif /* defined(__RunQuickly__Game2048Layer__) */
