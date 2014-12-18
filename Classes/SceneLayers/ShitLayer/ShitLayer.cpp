//
//  ShitLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#include "ShitLayer.h"
#include "CBShareManager.h"
#include "GameChooseLayer.h"


const char* arry[6] = {"拉","屎","都","能","赚","钱"};
bool ShitLayer::gameBegin = false;

void ShitLayer::hehe(int *arg) {
    int b = 110;
    arg = &b;
    *arg = 120;
}

bool ShitLayer::init() {
    if (!CBScreenLayer::init()) {
        return false;
    }
    CCLayerColor *yellowBtom = CCLayerColor::create(ccc4(200, 160, 0, 255), WINSIZE.width, WINSIZE.height);
    this->addChild(yellowBtom);
    
    monthPay = 0.0f;
    rate = 0.0f;
    name = "";
    wordsNode = NULL;
    CBPlatform::shared()->setPlatformDelegate(this);
    
    /*弄清楚c++的传址，和java的其实是一样的
    int a = 100;
    hehe(&a);
    CCLOG("a is %d",a);
    */
    
    CCLabelTTF *title = CCLabelTTF::create("带薪嗯嗯大赛", FONT_NAME, 30);
    title->setPosition(ccp(WINSIZE.width/2,WINSIZE.height * 0.95));
    this->addChild(title);
    
    CCLabelTTF *tips = CCLabelTTF::create("请填入参赛者个人信息:", FONT_NAME, 20);
    tips->setPosition(ccp(WINSIZE.width * 0.4,WINSIZE.height * 0.8));
    this->addChild(tips);
    
    CCLabelTTF *nameTip = CCLabelTTF::create("姓名", FONT_NAME, 20);
    nameTip->setPosition(ccp(WINSIZE.width * 0.2,WINSIZE.height * 0.65));
    this->addChild(nameTip);
    
    CCScale9Sprite *nameEditbixBg = CCScale9Sprite::create("InputBg.png");
    nameEditbix = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), nameEditbixBg);
    nameEditbix->setTouchPriority(getTouchPriority());
    nameEditbix->setFontName(FONT_NAME);
    nameEditbix->setFontColor(ccc3(0,0,0));
    nameEditbix->setFontSize(15);
    nameEditbix->setInputMode(kEditBoxInputModeAny);
    nameEditbix->setDelegate(this);
    nameEditbix->setPosition(ccp(WINSIZE.width * 0.55, nameTip->getPositionY()));
    nameEditbix->setPlaceholderFontName(FONT_NAME);
    nameEditbix->setPlaceHolder("input your name");
    nameEditbix->setPlaceholderFontColor(ccc3(0, 0, 0));
    nameEditbix->setTag(TYPE_NAME);
    this->addChild(nameEditbix);
    
    CCLabelTTF *monthTip = CCLabelTTF::create("月薪", FONT_NAME, 20);
    monthTip->setPosition(ccp(WINSIZE.width * 0.2,WINSIZE.height * 0.55));
    this->addChild(monthTip);
    
    CCScale9Sprite *monthEditbixBg = CCScale9Sprite::create("InputBg.png");
    monthEditBox = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), monthEditbixBg);
    monthEditBox->setTouchPriority(getTouchPriority());
    monthEditBox->setFontName(FONT_NAME);
    monthEditBox->setFontColor(ccc3(0,0,0));
    monthEditBox->setFontSize(15);
    monthEditBox->setInputMode(kEditBoxInputModeAny);
    monthEditBox->setDelegate(this);
    monthEditBox->setPosition(ccp(WINSIZE.width * 0.55, monthTip->getPositionY()));
    monthEditBox->setPlaceholderFontName(FONT_NAME);
    monthEditBox->setPlaceHolder("input you month pay");
    monthEditBox->setPlaceholderFontColor(ccc3(0, 0, 0));
    monthEditBox->setTag(TYPE_MONTH);
    this->addChild(monthEditBox);
    
    CCMenuItemLabel *beginShitBtn = CCMenuItemLabel::create(CCLabelTTF::create("开始嗯嗯", FONT_NAME, 20), this, menu_selector(ShitLayer::beginShit));
    beginShitBtn->setPosition(ccp(WINSIZE.width * 0.3, WINSIZE.height * 0.4));
    
    CCMenuItemLabel *endShitBtn = CCMenuItemLabel::create(CCLabelTTF::create("拉完了", FONT_NAME, 20), this, menu_selector(ShitLayer::endShit));
    endShitBtn->setPosition(ccp(WINSIZE.width * 0.7, WINSIZE.height * 0.4));
    
    moreGameBtn = CCMenuItemLabel::create(CCLabelTTF::create("更多游戏", FONT_NAME, 25), this, menu_selector(ShitLayer::moreGameBtnDown));
    moreGameBtn->setPosition(ccp(WINSIZE.width * 0.5, WINSIZE.height * 0.15));
    
    playWhenShitBtn = CCMenuItemLabel::create(CCLabelTTF::create("边拉边玩", FONT_NAME, 25), this, menu_selector(ShitLayer::playWhenShitBtnDown));
    playWhenShitBtn->setPosition(ccp(WINSIZE.width * 0.5, WINSIZE.height * 0.05));
    
    CCMenu *menu = CCMenu::create(beginShitBtn,endShitBtn,moreGameBtn,playWhenShitBtn,NULL);
    menu->setTouchPriority(getTouchPriority());
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    CCLabelTTF *earnTip = CCLabelTTF::create("你已经赚了RMB(元):", FONT_NAME, 20);
    earnTip->setPosition(ccp(WINSIZE.width * 0.4, WINSIZE.height * 0.3));
    this->addChild(earnTip);
    
    monyEarn = CCLabelTTF::create("0", FONT_NAME, 20);
    monyEarn->cocos2d::CCNode::setAnchorPoint(ccp(0, 0));
    monyEarn->setPosition(ccp(earnTip->getContentSize().width, 0));
    earnTip->addChild(monyEarn);
    return true;
}

void ShitLayer::beginShit() {
    if (monthPay == 0 || strcmp(name, "") == 0) {
        CCMessageBox("人生赢家，先填写自己的月薪And姓名", "tips");
    } else {
        if (gameBegin)
            return;
        rate = monthPay / 22 / 24 / 60 / 60;
        CCLOG("rate is %f ",rate);
        gameBegin = true;
        if (wordsNode == NULL) {
            wordsNode = CCNode::create();
            this->addChild(wordsNode);
        }
        this->schedule(schedule_selector(ShitLayer::IncreateInner), 1);
    }
}

void ShitLayer::endShit() {
    if (!gameBegin) {
        CCMessageBox("还未开始怎能结束", "请先嗯嗯");
        return;
    }
    this->unscheduleAllSelectors();
//    CCMessageBox(CCString::createWithFormat("你这次拉屎赚了%s元，真牛逼！",monyEarn->getString())->getCString(), "result");
    
    wordsNode->removeFromParentAndCleanup(true);
    wordsNode = NULL;
    moreGameBtn->setVisible(false);
    playWhenShitBtn->setVisible(false);
    
    CBShareManager::shared()->shotScreen();
    moreGameBtn->setVisible(true);
    playWhenShitBtn->setVisible(true);
    gameBegin = false;
}

void ShitLayer::IncreateInner() {
    for(int i =0 ;i < 6; i++) {
        makeAnim(arry[i],i);
    }
    double origin = atof(monyEarn->getString());
    origin += rate;
    monyEarn->setString(CCString::createWithFormat("%.4f",origin)->getCString());
}

void ShitLayer::makeAnim(const char *str,int index) {
    CCLabelTTF* word = CCLabelTTF::create(str, FONT_NAME, 20);
    word->setColor(ccc3(0, 0, 0));
    int randomDir = rand() % 2 == 0 ? 1 : -1;
    float disRata = (rand() % 3 + 1.0f) / 10.0f;
    CCPoint pos1 = ccp(WINSIZE.width * 0.5, WINSIZE.height * 0.5);
    CCPoint pos2 = ccp(WINSIZE.width * (0.5 + randomDir*disRata /2 ), WINSIZE.height * 0.9);
    CCPoint pos3 = ccp(WINSIZE.width * (0.5 + randomDir*disRata), WINSIZE.height * 0.5);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = pos1;
    bezier.controlPoint_2 = pos2;
    bezier.endPosition = pos3;
    CCBezierTo *beziaTo = CCBezierTo::create(1, bezier);
    word->setPosition(pos1);
    wordsNode->addChild(word);
    word->setVisible(false);
    word->runAction(CCRotateBy::create(100, 3600));
    word->runAction(CCSequence::create(CCDelayTime::create(index * 0.1f),
                                       CCCallFuncN::create(this, callfuncN_selector(ShitLayer::delayAddShit)),
                                       beziaTo,
                                       CCCallFuncN::create(this, callfuncN_selector(ShitLayer::aniEnd)),NULL));
}

void ShitLayer::delayAddShit(cocos2d::CCNode *node) {
    node->setVisible(true);
}

void ShitLayer::aniEnd(cocos2d::CCNode *node) {
    node->stopAllActions();
    node->removeFromParentAndCleanup(true);
}

void ShitLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}


void ShitLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void ShitLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}

void ShitLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    int tag = dynamic_cast<CCNode*>(editBox)->getTag();
    if (tag == TYPE_MONTH) {
        const char *text = editBox->getText();
        int lengh = strlen(text);
        for (int i = 0; i < lengh; i++) {
            if (text[i] < '0' || text[i] > '9') {
                CCMessageBox("人生赢家，请输入数字格式的薪水！！", "erroMg");
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

void ShitLayer::moreGameBtnDown() {
    CBPlatform::shared()->showAdWall();
}

void ShitLayer::playWhenShitBtnDown() {
    GameLayer_->addChild(GameChooseLayer::create());
    return;
    
    
    if (!gameBegin)
    {
        CCMessageBox("城步吴彦祝说", "不嗯嗯，无游戏，请先嗯嗯");
        return;
    }
    GameLayer_->addChild(GameChooseLayer::create());
}

bool ShitLayer::getShitState() {
    return gameBegin;
}

void ShitLayer::updateEarned(int extraTime) {
    CCLog("extraTime is %d",extraTime);
    double origin = atof(monyEarn->getString());
    origin = origin +  rate * extraTime;
    monyEarn->setString(CCString::createWithFormat("%.4f",origin)->getCString());
}