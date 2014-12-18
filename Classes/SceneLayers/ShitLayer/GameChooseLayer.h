//
//  GameChooseLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-12-16.
//
//

#ifndef __RunQuickly__GameChooseLayer__
#define __RunQuickly__GameChooseLayer__

#include "GameLayer.h"

class GameChooseLayer : public CBPopUpLayer {
public:
    virtual bool init();
    CREATE_FUNC(GameChooseLayer);
    
    void playe2048();
    void playeShitBuilding();
    void onClose();
private:
};

#endif /* defined(__RunQuickly__GameChooseLayer__) */
