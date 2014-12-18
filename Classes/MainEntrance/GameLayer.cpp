//
//  GameLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//
//

#include "GameLayer.h"
#include "ShitLayer.h"

GameLayer* GameLayer::_layer = NULL;

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
    if (!CBLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    //注册返回键监听
    cocos2d::CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
    CreateLayer(SHIT_LAYER);
    return true;
}

void GameLayer::CreateLayer(LAYER_TYPE type) {
    switch (type) {
        case SHIT_LAYER:
            this->addChild(ShitLayer::create());
            break;
        default:
            break;
    }
}


void GameLayer::keyBackClicked() {
    CBPlatform::shared()->quitGame();
}