//
//  ShitBuildingLayer.cpp
//  RunQuickly
//
//  Created by yuyu on 14-12-15.
//
//

#include "ShitBuildingLayer.h"

bool ShitBuildingLayer::init() {
    if (!CBScreenLayer::init()) {
        return false;
    }
    disJoint = NULL;
    
    CCLayerColor *layerBottom = CCLayerColor::create(ccc4(0, 0, 0, 255), WINSIZE.width, WINSIZE.height);
    this->addChild(layerBottom);
    
    b2Vec2 gravity = b2Vec2(0,-GRAVITY);
    world = new b2World(gravity);
    world->SetAllowSleeping(false);
    world->SetContinuousPhysics(true);
    
    //静态的边界
    makeScreenEgdge();
    
    makeShit();
    this->scheduleUpdate();
    
    return true;
}

void ShitBuildingLayer::makeShit() {
    //静态固定的点，用来
    b2BodyDef staticPointDef;
    staticPointDef.position.Set(WINSIZE.width / 2 / ptm_ratio, WINSIZE.height / ptm_ratio);
    staticPointDef.type = b2_staticBody;
    b2Body *staticPointBody = world->CreateBody(&staticPointDef);
    b2PolygonShape staticBox;
    staticBox.SetAsBox(20 / ptm_ratio, 20 / ptm_ratio);
    staticPointBody->CreateFixture(&staticBox, 0);
    
    
    //动态的屎
    b2BodyDef shitBodydef;
    shitBodydef.type = b2_dynamicBody;
    shitBodydef.position.Set(WINSIZE.width / 2 / ptm_ratio, WINSIZE.height * 0.8 / ptm_ratio);
    
    CCSprite *shitPic = CCSprite::create("shit.png");
    this->addChild(shitPic);
    
    b2Body *shitBody = world->CreateBody(&shitBodydef);
    shitBody->SetUserData(shitPic);
    shitBody->SetActive(true);
    shitBody->ApplyForceToCenter(b2Vec2(50 * GRAVITY,0));
    
    b2PolygonShape dynamicBox ;
    dynamicBox.SetAsBox(shitPic->getContentSize().width / 2 / ptm_ratio , shitPic->getContentSize().height / 2 / ptm_ratio);
    
    //为该钢体定义夹具
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;        //绑定物体的形状
    fixtureDef.density = 2.0f;            //密度
    fixtureDef.restitution = 0.0f;;        //弹性系数
    fixtureDef.friction = 0.1f;             //摩擦系数
    
    shitBody->CreateFixture(&fixtureDef);
    
    //生成距离关节
    b2DistanceJointDef disJointdef;
    disJointdef.Initialize(staticPointBody, shitBody, staticPointBody->GetWorldCenter(), shitBody->GetWorldCenter());
    
    disJoint = world->CreateJoint(&disJointdef);
}

void ShitBuildingLayer::makeScreenEgdge() {
    b2BodyDef screenBodyDef;
    screenBodyDef.position.Set(0,0);
    screenBodyDef.type = b2_staticBody;
    b2Body *screenBody = world->CreateBody(&screenBodyDef);
    
    b2EdgeShape screenBox;
    //上边
    screenBox.Set(b2Vec2(0,WINSIZE.height / ptm_ratio), b2Vec2(WINSIZE.width / ptm_ratio, WINSIZE.height / ptm_ratio));
    screenBody->CreateFixture(&screenBox,0);
    //底边
    screenBox.Set(b2Vec2(0,0), b2Vec2(WINSIZE.width / ptm_ratio, 0));
    screenBody->CreateFixture(&screenBox, 0);
    //左边
    screenBox.Set(b2Vec2(0,WINSIZE.height / ptm_ratio),b2Vec2(0,0));
    screenBody->CreateFixture(&screenBox, 0);
    //右边
    screenBox.Set(b2Vec2(WINSIZE.width / ptm_ratio,WINSIZE.height / ptm_ratio), b2Vec2(WINSIZE.width / ptm_ratio,0));
    screenBody->CreateFixture(&screenBox, 0);
}

void ShitBuildingLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (disJoint != NULL) {
        world->DestroyJoint(disJoint);
        disJoint = NULL;
//        makeShit();
    }
}

void ShitBuildingLayer::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL && b->GetType() != b2_staticBody) {
            cocos2d::CCSprite *ballData = (cocos2d::CCSprite *)(b->GetUserData());
            if(ballData){
                ballData->setPosition(ccp(b->GetPosition().x * ptm_ratio, b->GetPosition().y * ptm_ratio));
                ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            }
        }
    }
}