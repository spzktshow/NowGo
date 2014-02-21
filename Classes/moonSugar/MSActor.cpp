//
//  MSActor.cpp
//  NowGo
//
//  Created by RockLee on 14-2-10.
//
//

#include "MSActor.h"
#include "CCEventCustom.h"
#include "CCDirector.h"

NS_MS_BEGIN
//BehaviorEvent
BehaviorEvent::BehaviorEvent(std::string behaviorEventType)
{
	eventType = behaviorEventType;
}

BehaviorEvent::~BehaviorEvent(){}

//Actor
Actor::Actor()
{
	dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();

	stateContext = new StateContext();
	stateContext->currentState = STATE_IDLE;
}

Actor::~Actor()
{
	dispatcher->removeAllEventListeners();
	delete stateContext;
	delete dispatcher;
}

void Actor::executeEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
	if (behaviorEvent->eventType == DIRECT_EVENT)
	{
		executeDirectEvent(behaviorEvent);
	}
	else if (behaviorEvent->eventType == CANCEL_DIRECT_EVENT)
	{
		executeCancelDirectEvent(behaviorEvent);
	}
	else if (behaviorEvent->eventType == NORMAL_ATTACK_EVENT)
	{
		executeNormalAttackEvent(behaviorEvent);
	}
	else if (behaviorEvent->eventType == CANCEL_ATTACK_EVENT)
	{
		executeCancelAttackEvent(behaviorEvent);
	}
	else if (behaviorEvent->eventType == BE_ATTACK_EVENT)
	{
		executeNormalBeAttackEvent(behaviorEvent);
	}
	else if (behaviorEvent->eventType == CANCEL_BE_ATTACK_EVENT)
	{
		executeCancelNormalBeAttackEvent(behaviorEvent);
	}
    
    delete behaviorEvent;
}

void Actor::dispatcherStateChangeEvent()
{
	cocos2d::EventCustom event(ACTOR_EVENT_STATE_CHANGED);
	dispatcher->dispatchEvent(&event);
}

void Actor::executeDirectEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
	if (stateContext->currentState == STATE_IDLE)
	{
		stateContext->currentState = STATE_RUN;
        
        entry->getAnimation()->play(STATE_RUN);
        
        moonsugar::BehaviorDirectEvent *behaviorDirectEvent = static_cast<moonsugar::BehaviorDirectEvent*>(behaviorEvent);

        if (behaviorDirectEvent->directType == DIRECT_TYPE_LEFT)
        {
            entry->setScaleX(-1);
        }
        else
        {
            entry->setScaleX(1);
        }
		//dispatcherStateChangeEvent();
	}
}

void Actor::executeCancelDirectEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
	if (stateContext->currentState == STATE_RUN)
	{
		stateContext->currentState = STATE_IDLE;
        
        entry->getAnimation()->play(STATE_IDLE);

		//dispatcherStateChangeEvent();
	}
}

void Actor::executeNormalAttackEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
    if (stateContext ->currentState == STATE_RUN || stateContext->currentState == STATE_IDLE)
    {
        stateContext->currentState = STATE_NORMAL_ATTACK;
        
//        entry->getAnimation()->setMovementEventCallFunc(std::function<void (cocostudio::Armature *, cocostudio::MovementEventType, const std::string &)> (Actor::onNormalAttackComplete));
        entry->getAnimation()->play(STATE_NORMAL_ATTACK);
    }
}

void Actor::onNormalAttackComplete(cocostudio::Armature *armature, cocostudio::MovementEventType eventType, const std::string &str)
{
    moonsugar::BehaviorCancelNormalAttackEvent * cancelNormalAttackEvent = new moonsugar::BehaviorCancelNormalAttackEvent(CANCEL_ATTACK_EVENT);
    executeCancelAttackEvent(cancelNormalAttackEvent);
    cancelNormalAttackEvent = nullptr;
}

void Actor::executeCancelAttackEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
    if (stateContext->currentState == STATE_NORMAL_ATTACK)
    {
        stateContext->currentState = STATE_IDLE;
        
        entry->getAnimation()->play(STATE_IDLE);
    }
}

void Actor::executeNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent)
{

}

void Actor::executeCancelNormalBeAttackEvent(moonsugar::BehaviorEvent * behaviorEvent)
{

}
NS_MS_END
