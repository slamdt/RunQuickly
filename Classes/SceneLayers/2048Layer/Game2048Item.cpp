//
//  Game2048Item.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-28.
//
//

#include "Game2048Item.h"

bool Game2048Item::init() {
    if (!CCNode::init()) {
        return false;
    }
    itemValue = 0;
    nextItemValue = 0;
    nexPosIndex = posIndex;
    this->setContentSize(CCSizeMake(itemSize, itemSize));
    this->setPosition(itemPos);
    return true;
}

void Game2048Item::makeContent(int value) {
    itemValue = value;
    nextItemValue = itemValue;
    itemColor = CCLayerColor::create(ccc4(188, 188, 188, 255), itemSize, itemSize);
    this->addChild(itemColor);
    itemTxt = CCLabelTTF::create(CBStringFormInterger(itemValue), FONT_NAME, 20);
    itemTxt->setPosition(this->getContentSize()/2);
    this->addChild(itemTxt);
}

void Game2048Item::valueAdd(int addValue) {
    nextItemValue += addValue;
    valueChaged = true;
}