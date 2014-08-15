//
//  CBShareManager.h
//  RunQuickly
//
//  Created by yuyu on 14-8-14.
//
//

#ifndef __RunQuickly__CBShareManager__
#define __RunQuickly__CBShareManager__

#include "GameLayer.h"

class shotScreenLayer : public CBPopUpLayer {
public:
    CREATE_FUNC(shotScreenLayer);
    virtual bool init();
    void shareBtnDown();
    void back();
    void getFileName();
private:
    std::string file_name;
};

class CBShareManager {
    SINGLETON(CBShareManager)
public:
    void shotScreen();
};

#endif /* defined(__RunQuickly__CBShareManager__) */
