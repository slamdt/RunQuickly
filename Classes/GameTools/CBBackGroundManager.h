//
//  CBBackGroundManager.h
//  RunQuickly
//
//  Created by yuyu on 14-8-22.
//
//

#ifndef __RunQuickly__CBBackGroundManager__
#define __RunQuickly__CBBackGroundManager__

#include "CBCommon.h"
class CBBackGroundManager {
    SINGLETON(CBBackGroundManager);
public:
    void enterBackGround();
    void enterForeGround();
};

#endif /* defined(__RunQuickly__CBBackGroundManager__) */
