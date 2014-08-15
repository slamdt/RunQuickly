//
//  CBCommon.h
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#ifndef __RunQuickly__CBCommon__
#define __RunQuickly__CBCommon__
#include "cocos2d.h"
using namespace cocos2d;

#define SINGLETON(className)\
private:\
className() {};\
virtual bool init();\
static className *_shared;\
public:\
static className* shared(){\
if (!_shared) {_shared = new className();_shared->init();}\
return _shared;\
};

#define SINGLETON_IMPL(className)\
className* className::_shared = NULL;


#endif /* defined(__RunQuickly__CBCommon__) */
