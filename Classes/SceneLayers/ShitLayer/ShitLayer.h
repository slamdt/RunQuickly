//
//  ShitLayer.h
//  RunQuickly
//
//  Created by yuyu on 14-8-13.
//
//

#ifndef __RunQuickly__ShitLayer__
#define __RunQuickly__ShitLayer__

#include "GameLayer.h"

class ShitLayer : public CCLayer ,public CCEditBoxDelegate{
public:
    CREATE_FUNC(ShitLayer);
    virtual bool init();
    
    void beginShit();
    void endShit();
    void IncreateInner();
    void makeAnim(const char* str,int index);
    void aniEnd(CCObject *pSender);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
private:
    
    CCEditBox *nameEditbix, *monthEditBox;
    CCLabelTTF *monyEarn;
    double monthPay;
    const char* name;
    double rate;
    bool gameBegin;
    enum EDITBOX_TYPE{
        TYPE_NAME = 1,
        TYPE_MONTH
    };
};

#endif /* defined(__RunQuickly__ShitLayer__) */
