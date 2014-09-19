//
//  Game2048Layer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-28.
//
//

#include "Game2048Layer.h"

Game2048Layer::~Game2048Layer() {
    items.erase(items.begin(), items.end());
}

bool Game2048Layer::init() {
    if (!CBScreenLayer::init()) {
        return false;
    }
    touchMoved = false;
    adjustOver = false;
    itemMoved = false;
    CCLayerColor *layerColor= CCLayerColor::create(ccc4(66, 66, 66, 255), WINSIZE.width, WINSIZE.height);
    this->addChild(layerColor);
    
    CCLabelTTF *tips = CCLabelTTF::create("毫无疑问，你就是下一个城步吴彦祖", FONT_NAME, 15);
    tips->setPosition(ccp(WINSIZE.width/2, WINSIZE.height * 0.8));
    tips->setColor(ccc3(255, 0, 0));
    this->addChild(tips,10);
    
    float bottomSize = WINSIZE.width * 0.8;
    itemSize = bottomSize * 0.2;
    float gap = bottomSize * 0.04;
    CCLayerColor *bottom = CCLayerColor::create(ccc4(88, 88, 88, 255), bottomSize,bottomSize);
    bottom->setPosition(ccp((WINSIZE.width - bottomSize)/2, (WINSIZE.height - bottomSize)/2));
    this->addChild(bottom);
    
    float posY = 0.0f;
    float posX = 0.0f;
    
    for (int row = 0; row < 4 ;row ++) {
        posY = bottom->getPositionY() + gap + row * (itemSize + gap);
        for (int colum = 0; colum < 4; colum++) {
            posX = bottom->getPositionX() + gap + colum * (itemSize + gap);
            POS[row * 4 + colum] = ccp(posX,posY);
        }
    }
    
    for (int i = POS_1 ; i <= POS_16; i ++) {
        Game2048Item *item = new Game2048Item(i,itemSize,POS[i]);
        item->init();
        if (i == POS_10 || i == POS_11) {
            item->makeContent(2);
        }
        items.push_back(item);
        this->addChild(item);
        item->release();
    }
    
    CCMenuItemLabel *backBtn = CCMenuItemLabel::create(CCLabelTTF::create("返回", FONT_NAME, 20), this, menu_selector(Game2048Layer::back));
    backBtn->setColor(ccc3(255, 0, 0));
    backBtn->setPosition(ccp(WINSIZE.width * 0.1, WINSIZE.height * 0.9));
    
    CCMenu *menu = CCMenu::create(backBtn,NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    return true;
}

void Game2048Layer::back() {
    this->removeFromParentAndCleanup(true);
}

bool Game2048Layer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    startPoint = this->convertTouchToNodeSpace(pTouch);
    return true;
}


void Game2048Layer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (!touchMoved) {
        itemMoved = false;
        CCPoint curPoint = this->convertTouchToNodeSpace(pTouch);
        if (curPoint.y - startPoint.y > 5) { //向上滑动
            touchMoved = true;
            for (int i = 0; i < 4; i ++) {
                int startPosIndex = POS_13 + i;
                for (int j = 1; j <= 3; j++ ) {
                    int targetPosIndex = startPosIndex - j * 4;
                    int prePosIndex = targetPosIndex;
                    int finalNexPosIndex = targetPosIndex;
                    bool valueChange = false;
                    Game2048Item *preItem = items[prePosIndex];
                    Game2048Item *targetItem = items[targetPosIndex];
                    if (targetItem->getNextItemValue() == 0)
                        continue;
                    while(prePosIndex < startPosIndex) {
                        prePosIndex += 4;
                        preItem = items[prePosIndex];
                        if (preItem->getNextItemValue() == 0) { //没有数字
                            finalNexPosIndex = prePosIndex;
                        } else { //有数字
                            int targetItemValue = targetItem->getItemValue();
                            if (!preItem->getValueChaged() && preItem->getNextItemValue() == targetItemValue) { //相同的数字叠加
                                finalNexPosIndex = prePosIndex;
                                valueChange = true;
                            } else {
                                break;
                            }
                        }
                    }
                    if (finalNexPosIndex != targetPosIndex) {
                        itemMoved = true;
                        if (valueChange) {
                            items[finalNexPosIndex]->valueAdd(targetItem->getItemValue());
                        } else {
                            items[finalNexPosIndex]->setNextItemValue(targetItem->getItemValue());
                        }
                        targetItem->setNextItemValue(0);
                        targetItem->setNextPosIndex(finalNexPosIndex);
                        
                    }
                }
            }
            if (itemMoved) updateItemStatus();
        } else if (curPoint.y - startPoint.y < -5) { //向下滑动
            touchMoved = true;
            for (int i = 0; i < 4; i ++) {
                int startPosIndex = POS_1 + i;
                for (int j = 1; j <= 3; j++ ) {
                    int targetPosIndex = startPosIndex + j * 4;
                    int prePosIndex = targetPosIndex;
                    int finalNexPosIndex = targetPosIndex;
                    bool valueChange = false;
                    Game2048Item *preItem = items[prePosIndex];
                    Game2048Item *targetItem = items[targetPosIndex];
                    if (targetItem->getNextItemValue() == 0)
                        continue;
                    while(prePosIndex > startPosIndex) {
                        prePosIndex -= 4;
                        preItem = items[prePosIndex];
                        if (preItem->getNextItemValue() == 0) { //没有数字
                            finalNexPosIndex = prePosIndex;
                        } else { //有数字
                            int targetItemValue = targetItem->getItemValue();
                            if (!preItem->getValueChaged() && preItem->getNextItemValue() == targetItemValue) { //相同的数字叠加
                                finalNexPosIndex = prePosIndex;
                                valueChange = true;
                            } else {
                                break;
                            }
                        }
                    }
                    if (finalNexPosIndex != targetPosIndex) {
                        itemMoved = true;
                        if (valueChange) {
                            items[finalNexPosIndex]->valueAdd(targetItem->getItemValue());
                        } else {
                            items[finalNexPosIndex]->setNextItemValue(targetItem->getItemValue());
                        }
                        targetItem->setNextItemValue(0);
                        targetItem->setNextPosIndex(finalNexPosIndex);
                        
                    }
                }
            }
            if (itemMoved) updateItemStatus();
        } else if (curPoint.x - startPoint.x > 5) { //向右滑动
            touchMoved = true;
            for (int i = 0; i < 4; i ++) {
                int startPosIndex = POS_4 + i * 4;
                for (int j = 1; j <= 3; j++ ) {
                    int targetPosIndex = startPosIndex - j;
                    int prePosIndex = targetPosIndex;
                    int finalNexPosIndex = targetPosIndex;
                    bool valueChange = false;
                    Game2048Item *preItem = items[prePosIndex];
                    Game2048Item *targetItem = items[targetPosIndex];
                    if (targetItem->getNextItemValue() == 0)
                        continue;
                    while(prePosIndex < startPosIndex) {
                        prePosIndex ++;
                        preItem = items[prePosIndex];
                        if (preItem->getNextItemValue() == 0) { //没有数字
                            finalNexPosIndex = prePosIndex;
                        } else { //有数字
                            int targetItemValue = targetItem->getItemValue();
                            if (!preItem->getValueChaged() && preItem->getNextItemValue() == targetItemValue) { //相同的数字叠加
                                finalNexPosIndex = prePosIndex;
                                valueChange = true;
                            } else {
                                break;
                            }
                        }
                    }
                    if (finalNexPosIndex != targetPosIndex) {
                        itemMoved = true;
                        if (valueChange) {
                            items[finalNexPosIndex]->valueAdd(targetItem->getItemValue());
                        } else {
                            items[finalNexPosIndex]->setNextItemValue(targetItem->getItemValue());
                        }
                        targetItem->setNextItemValue(0);
                        targetItem->setNextPosIndex(finalNexPosIndex);
                        
                    }
                }
            }
            if (itemMoved) updateItemStatus();
        } else if (curPoint.x - startPoint.x < -5) { //向左滑动
            touchMoved = true;
            for (int i = 0; i < 4; i ++) {
                int startPosIndex = POS_1 + i * 4;
                for (int j = 1; j <= 3; j++ ) {
                    int targetPosIndex = startPosIndex + j;
                    int prePosIndex = targetPosIndex;
                    int finalNexPosIndex = targetPosIndex;
                    bool valueChange = false;
                    Game2048Item *preItem = items[prePosIndex];
                    Game2048Item *targetItem = items[targetPosIndex];
                    if (targetItem->getNextItemValue() == 0)
                        continue;
                    while(prePosIndex > startPosIndex) {
                        prePosIndex --;
                        preItem = items[prePosIndex];
                        if (preItem->getNextItemValue() == 0) { //没有数字
                            finalNexPosIndex = prePosIndex;
                        } else { //有数字
                            int targetItemValue = targetItem->getItemValue();
                            if (!preItem->getValueChaged() && preItem->getNextItemValue() == targetItemValue) { //相同的数字叠加
                                finalNexPosIndex = prePosIndex;
                                valueChange = true;
                            } else {
                                break;
                            }
                        }
                    }
                    if (finalNexPosIndex != targetPosIndex) {
                        itemMoved = true;
                        if (valueChange) {
                            items[finalNexPosIndex]->valueAdd(targetItem->getItemValue());
                        } else {
                            items[finalNexPosIndex]->setNextItemValue(targetItem->getItemValue());
                        }
                        targetItem->setNextItemValue(0);
                        targetItem->setNextPosIndex(finalNexPosIndex);
                        
                    }
                }
            }
            if (itemMoved) updateItemStatus();
        }
    }
}

void Game2048Layer::updateItemStatus() {
    for (std::vector<Game2048Item*>::iterator iter = items.begin(); iter != items.end(); iter++) {
        if ((*iter)->getNextPosIndex() != (*iter)->getPosIndex()) {
            //要移动
            CCLOG("to move");
            int nextPosIndex = (*iter)->getNextPosIndex();
            CCMoveTo *action1 = CCMoveTo::create(0.1f, POS[nextPosIndex]);
            (*iter)->runAction(action1);
        } else {
            CCLOG("no need move");
        }
    }
    this->scheduleOnce(schedule_selector(Game2048Layer::moveOver), 0.1f);
}

bool Game2048Layer::elementExis(const std::vector<int> &vector, int element) {
    for (std::vector<int>::const_iterator it = vector.begin(); it != vector.end(); it++) {
        if ((*it) == element)
            return true;
    }
    return false;
}

void Game2048Layer::moveOver() {
    CCLOG("adjust items");
    std::vector<int> nexPOSSet;//被移到的位置的集合
    std::vector<int> originPOSSet;//没被移到的位置的集合，两种状态，一是该位置移到别处，二是该位置没有动
    std::vector<int> emptyPosSet; //没有物品的位置集合
    for (std::vector<Game2048Item *>::iterator iter = items.begin(); iter != items.end(); iter++) {
        int posIndex = (*iter)->getPosIndex();
        int nexPosIndex = (*iter)->getNextPosIndex();
        if (nexPosIndex != posIndex){
            //证明当前的item移到了nexPosIndex的位置上了，nexPosIndex位置上的值用nextItemValue更新
            if (!elementExis(nexPOSSet,nexPosIndex)) {
                nexPOSSet.push_back(nexPosIndex);
            }
        }
    }
    
    for (int i = POS_1; i <= POS_16; i++) {
        if (!elementExis(nexPOSSet, i))
            originPOSSet.push_back(i);
    }
    
    for (std::vector<int>::iterator it = nexPOSSet.begin(); it != nexPOSSet.end(); it++) {
        //nexPosIndex位置上的值用nextItemValue更新
        int index = (*it);
        Game2048Item *oldItem = items[index];
        int nexValue = oldItem->getNextItemValue();
        Game2048Item *newItem = new Game2048Item(index,itemSize,POS[index]);
        newItem->init();
        newItem->makeContent(nexValue);
        items[index] = newItem;
        oldItem->removeFromParentAndCleanup(true);
        this->addChild(newItem);
        newItem->release();
    }
    
    for (std::vector<int>::iterator it = originPOSSet.begin(); it != originPOSSet.end(); it++) {
        //没被移到的位置的集合，两种状态，一是该位置移到别处，而是该位置没有动
        int index = (*it);
        Game2048Item *oldItem = items[index];
        int oldItemPosIndex = oldItem->getPosIndex();
        int oldItemNexPosIndex = oldItem->getNextPosIndex();
        Game2048Item *newItem = new Game2048Item(index,itemSize,POS[index]);
        newItem->init();
        
        if(oldItemNexPosIndex == oldItemPosIndex) {
            //这种情况是当前位置没有别的item移过来，而且当前位置原来的item也没有移走。用原来item的itemValue初始化
            int oldItemValue = oldItem->getItemValue();
            if (oldItemValue != 0) {
             newItem->makeContent(oldItemValue);
            } else {
                //位置上元素值为0（空）
                emptyPosSet.push_back(index);
            }
        } else {
            //这种情况是当前位置没有别的item移过来，但是当前位置原来的item移走了。该位置元素值也为0（空）
            emptyPosSet.push_back(index);
        }
        items[index] = newItem;
        oldItem->removeFromParentAndCleanup(true);
        this->addChild(newItem);
        newItem->release();
    }
    
    int randomIndex = emptyPosSet[rand() % emptyPosSet.size()];
    CCLOG("random index is %d",randomIndex);
    items[randomIndex]->makeContent(rand() % 10 > 6 ? 4 : 2);    
    
//    for (std::vector<Game2048Item *>::iterator iter = items.begin(); iter != items.end(); iter++) {
//        CCLOG("index : %d, value :%d",(*iter)->getPosIndex(),(*iter)->getItemValue());
//    }
}

void Game2048Layer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    touchMoved = false;
}

