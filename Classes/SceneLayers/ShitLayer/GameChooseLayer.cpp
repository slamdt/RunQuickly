//
//  GameChooseLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-12-16.
//
//

#include "GameChooseLayer.h"
#include "Game2048Layer.h"
#include "ShitBuildingLayer.h"

bool GameChooseLayer::init() {
    if (!CBPopUpLayer::init()) {
        return false;
    }
    
    float bottmWidth = WINSIZE.width * 0.6;
    float bottmHight = WINSIZE.height*0.6;
    CCLayerColor *chooseBottom = CCLayerColor::create(ccc4(170, 170, 170, 255),bottmWidth,bottmHight);
    chooseBottom->setPosition(ccp((WINSIZE.width - bottmWidth)/2, (WINSIZE.height - bottmHight) /2));
    this->addChild(chooseBottom);
    
    CCMenuItemLabel *game2048 = CCMenuItemLabel::create(CCLabelTTF::create("2048", FONT_NAME, 20), this, menu_selector(GameChooseLayer::playe2048));
    game2048->setColor(ccRED);
    game2048->setPosition(ccp(chooseBottom->getContentSize().width/2, chooseBottom->getContentSize().height *0.6));
    
    CCMenuItemLabel *gameShitBuilding = CCMenuItemLabel::create(CCLabelTTF::create("我是包工头", FONT_NAME, 20), this, menu_selector(GameChooseLayer::playeShitBuilding));
    gameShitBuilding->setColor(ccRED);
    gameShitBuilding->setPosition(ccp(chooseBottom->getContentSize().width/2, chooseBottom->getContentSize().height * 0.4));
    
    CCMenu *menu = CCMenu::create(game2048,gameShitBuilding,NULL);
    menu->setTouchPriority(getTouchPriority());
    menu->setPosition(ccp(0, 0));
    chooseBottom->addChild(menu);
    
    
    return true;
}

void GameChooseLayer::playe2048() {
    GameLayer_->addChild(Game2048Layer::create());
    onClose();
}

void GameChooseLayer::playeShitBuilding(){
    GameLayer_->addChild(ShitBuildingLayer::create());
    onClose();
}

void GameChooseLayer::onClose() {
    this->removeFromParentAndCleanup(true);
}