//
//  Game2048Item.h
//  RunQuickly
//
//  Created by yuyu on 14-8-28.
//
//

#ifndef __RunQuickly__Game2048Item__
#define __RunQuickly__Game2048Item__

#include "GameLayer.h"

class Game2048Item : public CCNode {
public:
    Game2048Item(int _posIndex,int _itemSize,CCPoint _itemPos):posIndex(_posIndex),itemSize(_itemSize),itemPos(_itemPos),valueChaged(false){
        
    }
    void makeContent(int value);
    void valueAdd(int addValue);
    virtual bool init();
private:
    CC_SYNTHESIZE_READONLY(int, posIndex, PosIndex) ;
    CC_SYNTHESIZE(int, nexPosIndex, NextPosIndex);
    CC_SYNTHESIZE_READONLY(int, itemValue, ItemValue);
    CC_SYNTHESIZE(int, nextItemValue, NextItemValue);
    CC_SYNTHESIZE(bool, valueChaged, ValueChaged);
    CCLayerColor *itemColor;
    int itemSize;
    CCLabelTTF *itemTxt;
    CCPoint itemPos;
};

#endif /* defined(__RunQuickly__Game2048Item__) */
