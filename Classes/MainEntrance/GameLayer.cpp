//
//  GameLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-6-25.
//
//

#include "GameLayer.h"
static GameLayer* _layer;


const char* arry[6] = {"拉","屎","都","能","赚","钱"};
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
    monthPay = 0.0f;
    rate = 0.0f;
    name = "";
    gameBegin = false;
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *title = CCLabelTTF::create("带薪拉屎大赛", FONT_NAME, 40);
    title->setPosition(ccp(winSize.width/2,winSize.height * 0.95));
    this->addChild(title);
    
    CCLabelTTF *tips = CCLabelTTF::create("请填入参赛者个人信息:", FONT_NAME, 30);
    tips->setPosition(ccp(winSize.width * 0.3,winSize.height * 0.8));
    this->addChild(tips);
    
    CCLabelTTF *nameTip = CCLabelTTF::create("姓名", FONT_NAME, 20);
    nameTip->setPosition(ccp(winSize.width * 0.1,winSize.height * 0.7));
    this->addChild(nameTip);
    
    CCScale9Sprite *nameEditbixBg = CCScale9Sprite::create("InputBg.png");
    nameEditbix = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), nameEditbixBg);
    nameEditbix->setTouchPriority(getTouchPriority());
    nameEditbix->setFontName(FONT_NAME);
    nameEditbix->setFontColor(ccc3(0,0,0));
    nameEditbix->setFontSize(20);
    nameEditbix->setInputMode(kEditBoxInputModeAny);
    nameEditbix->setDelegate(this);
    nameEditbix->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.7));
    nameEditbix->setPlaceholderFontName(FONT_NAME);
    nameEditbix->setPlaceHolder("input your name ，man");
    nameEditbix->setPlaceholderFontColor(ccc3(0, 0, 0));
    nameEditbix->setTag(TYPE_NAME);
    this->addChild(nameEditbix);
    
    CCLabelTTF *monthTip = CCLabelTTF::create("月薪", FONT_NAME, 20);
    monthTip->setPosition(ccp(winSize.width * 0.1,winSize.height * 0.6));
    this->addChild(monthTip);
    
    CCScale9Sprite *monthEditbixBg = CCScale9Sprite::create("InputBg.png");
    monthEditBox = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), monthEditbixBg);
    monthEditBox->setTouchPriority(getTouchPriority());
    monthEditBox->setFontName(FONT_NAME);
    monthEditBox->setFontColor(ccc3(0,0,0));
    monthEditBox->setFontSize(20);
    monthEditBox->setInputMode(kEditBoxInputModeAny);
    monthEditBox->setDelegate(this);
    monthEditBox->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    monthEditBox->setPlaceholderFontName(FONT_NAME);
    monthEditBox->setPlaceHolder("input your month pay ，man");
    monthEditBox->setPlaceholderFontColor(ccc3(0, 0, 0));
    monthEditBox->setTag(TYPE_MONTH);
    this->addChild(monthEditBox);
    
    CCMenuItemLabel *beginShitBtn = CCMenuItemLabel::create(CCLabelTTF::create("开始拉屎", FONT_NAME, 30), this, menu_selector(GameLayer::beginShit));
    beginShitBtn->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.4));
    
    CCMenuItemLabel *endShitBtn = CCMenuItemLabel::create(CCLabelTTF::create("拉完了", FONT_NAME, 30), this, menu_selector(GameLayer::endShit));
    endShitBtn->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.4));
    
    CCMenu *menu = CCMenu::create(beginShitBtn,endShitBtn,NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    CCLabelTTF *earnTip = CCLabelTTF::create("你已经赚了RMB(元):", FONT_NAME, 40);
    earnTip->setPosition(ccp(winSize.width * 0.4, winSize.height * 0.3));
    this->addChild(earnTip);
    
    monyEarn = CCLabelTTF::create("0", FONT_NAME, 40);
    monyEarn->cocos2d::CCNode::setAnchorPoint(ccp(0, 0));
    monyEarn->setPosition(ccp(earnTip->getContentSize().width, 0));
    earnTip->addChild(monyEarn);
    
    return true;
}

void GameLayer::beginShit() {
    if (monthPay == 0 || strcmp(name, "") == 0) {
        CCMessageBox("逗比，先填写自己的月薪And姓名", "逗比");
    } else {
        if (gameBegin)
            return;
        rate = monthPay / 22 / 24 / 60 / 60;
        CCLOG("rate is %f ",rate);
        gameBegin = true;
        this->schedule(schedule_selector(GameLayer::IncreateInner), 1);
    }
}

void GameLayer::endShit() {
    if (!gameBegin) {
        CCMessageBox("还未开始怎能结束", "请先拉屎");
        return;
    }
    this->unscheduleAllSelectors();
    CCMessageBox(CCString::createWithFormat("你这次拉屎赚了%s元，真牛逼！",monyEarn->getString())->getCString(), "result");
    gameBegin = false;
}

void GameLayer::IncreateInner() {
    for(int i =0 ;i < 6; i++) {
        makeAnim(arry[i],i);
    }    
    double origin = atof(monyEarn->getString());
    origin += rate;
    monyEarn->setString(CCString::createWithFormat("%.4f",origin)->getCString());
}

void GameLayer::makeAnim(const char *str,int index) {
    CCLabelTTF* word = CCLabelTTF::create(str, FONT_NAME, 30);
    int randomDir = rand() % 2 == 0 ? 1 : -1;
    float disRata = (rand() % 3 + 1.0f) / 10.0f;
    CCPoint pos1 = ccp(winSize.width * 0.5, winSize.height * 0.5);
    CCPoint pos2 = ccp(winSize.width * (0.5 + randomDir*disRata /2 ), winSize.height * 0.9);
    CCPoint pos3 = ccp(winSize.width * (0.5 + randomDir*disRata), winSize.height * 0.5);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = pos1;
    bezier.controlPoint_2 = pos2;
    bezier.endPosition = pos3;
    CCBezierTo *beziaTo = CCBezierTo::create(1, bezier);
    word->setPosition(pos1);
    this->addChild(word);
    word->runAction(CCRotateBy::create(100, 3600));
    word->runAction(CCSequence::create(CCDelayTime::create(index * 0.1f),beziaTo,CCCallFuncN::create(this, callfuncN_selector(GameLayer::aniEnd)),NULL));
}

void GameLayer::aniEnd(cocos2d::CCObject *pSender) {
    CCNode *node = dynamic_cast<CCNode*>(pSender);
    node->stopAllActions();
    node->removeFromParentAndCleanup(true);
}

void GameLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}


void GameLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void GameLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}

void GameLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    int tag = dynamic_cast<CCNode*>(editBox)->getTag();
    if (tag == TYPE_MONTH) {
        const char *text = editBox->getText();
        int lengh = strlen(text);
        for (int i = 0; i < lengh; i++) {
            if (text[i] < '0' || text[i] > '9') {
                CCMessageBox("逗比，你的月薪是字符串啊，要输入数字", "erroMg");
                editBox->setText("");
                return;
            }
        }
        monthPay = atof(text);
    } else {
        name = editBox->getText();
        CCLOG("name is %s", name);
    }
}