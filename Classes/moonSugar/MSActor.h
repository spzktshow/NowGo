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

//state
#define STATE_IDLE				"stateIdle"

#define STATE_NORMAL_ATTACK		"stateNormalAttack"

#define STATE_BE_ATTACK			"stateBeAttack"

#define STATE_RUN				"stateRun"

#define STATE_DEAD				"stateDead"

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

class BehaviorEvent
{
public:
	std::string eventType;

	BehaviorEvent(std::string behaviorEventType);

	~BehaviorEvent();
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

    void executeEvent(moonsugar::BehaviorEvent * behaviorEvent);
protected:
	void executeDirectEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelDirectEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeNormalAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);
	void executeCancelNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent);

	void dispatcherStateChangeEvent();
};

NS_MS_END


#endif
