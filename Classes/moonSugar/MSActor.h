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
#include "CCEventDispatcher.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCArmatureAnimation.h"

//state
#define STATE_IDLE				"loading"

#define STATE_NORMAL_ATTACK		"attack"

#define STATE_BE_ATTACK			"smitten"

#define STATE_RUN				"run"

#define STATE_DEAD				"death"

//behavior
#define DIRECT_EVENT			"directEvent"
#define CANCEL_DIRECT_EVENT		"cancelDirectEvent"
#define NORMAL_ATTACK_EVENT		"normalAttackEvent"
#define CANCEL_ATTACK_EVENT		"cancelAttackEvent"
#define BE_ATTACK_EVENT			"beAttackEvent"
#define CANCEL_BE_ATTACK_EVENT	"cancelBeAttackEvent"
#define DEAD_EVENT				"deadEvent"


//event
#define ACTOR_EVENT_STATE_CHANGED			"actorEventStateChanged"

NS_MS_BEGIN
//行为事件
class BehaviorEvent
{
public:
	std::string eventType;

	BehaviorEvent(std::string behaviorEventType);

	~BehaviorEvent();
};

//direct type
#define DIRECT_TYPE_LEFT "left"
#define DIRECT_TYPE_RIGHT "right"

class BehaviorDirectEvent : public BehaviorEvent
{
public:
    BehaviorDirectEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorDirectEvent();
    
    std::string directType;
};

class BehaviorCancelDirectEvent : public BehaviorEvent
{
public:
    BehaviorCancelDirectEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorCancelDirectEvent();
};

class BehaviorNormalAttackEvent : public BehaviorEvent
{
public:
    BehaviorNormalAttackEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorNormalAttackEvent();
};

class BehaviorCancelNormalAttackEvent : public BehaviorEvent
{
public:
    BehaviorCancelNormalAttackEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorCancelNormalAttackEvent();
};

class StateContext
{
public:
	std::string currentState;
};

class Actor : public cocos2d::Object
{
public:
    StateContext * stateContext;
	//listenerDispatcher
	cocos2d::EventDispatcher * dispatcher;
	Actor();
	~Actor();
    //实体
    cocostudio::Armature *entry;

    void executeEvent(moonsugar::BehaviorEvent * behaviorEvent);
protected:
	void executeDirectEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelDirectEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeNormalAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);

	void dispatcherStateChangeEvent();
    
    void onNormalAttackComplete(cocostudio::Armature *armature, cocostudio::MovementEventType eventType, const std::string& str);
};

NS_MS_END


#endif
