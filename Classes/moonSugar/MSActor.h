//
//  MSActor.h
//  NowGo
//
//  Created by RockLee on 14-2-10.
//
//

#ifndef NowGo_MSActor_h
#define NowGo_MSActor_h

#include "moonSugar.h"
#include "cocos2d.h"
#include <string>

NS_MS_BEGIN

class StateEnum
{
public:
    static const std::string STATE_IDLE;
    static const std::string STATE_NORMAL_ATTACK;
    static const std::string STATE_BE_ATTACK;
    static const std::string STATE_RUN;
    static const std::string STATE_DEAD;
};

class BehavierEventEnum
{
public:
    static const std::string DIRECT_EVENT;
    static const std::string CANCEL_DIRECT_EVENT;
    static const std::string NORMAL_ATTACK_EVENT;
    static const std::string CANCEL_ATTACK_EVENT;
    static const std::string BE_ATTACK_EVENT;
    static const std::string CANCEL_BE_ATTACK_EVENT;
    static const std::string DEAD_EVENT;
};

class Actor : public cocos2d::Object
{
public:
    std::string currentState;
    
    
};

NS_MS_END


#endif
