//
//  GameLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//
//

#include "GameLayer.h"
static GameLayer* _layer;

GameLayer* GameLayer::instance() {
    if (_layer == NULL) {
        _layer = new GameLayer();
        CCAssert(_layer->init(), "gamelayer init failed");
    }
    return _layer;
}

CCScene* GameLayer::scene() {
    CCScene* scene = CCScene::create();
    GameLayer *layer = GameLayer::instance();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init() {
    CCLabelTTF *tips = CCLabelTTF::create("跑得快项目开始", "FZYHJW--GB1-0", 30);
    tips->setPosition(ccp(500,300));
    this->addChild(tips);
    return true;
}