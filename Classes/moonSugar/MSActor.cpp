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
    else if (behaviorEvent->eventType == JUMP_EVENT)
    {
        executeJumpEvent(behaviorEvent);
    }
    else if (behaviorEvent->eventType == CANCEL_JUMP_EVENT)
    {
        executeCancelJumpEvent(behaviorEvent);
    }
    delete behaviorEvent;
}

void Actor::jump()
{
    cocos2d::Action * action = cocos2d::MoveTo::create(0.2f, cocos2d::Point(position->x, position->y + 100));
    cocos2d::Action * back = cocos2d::MoveTo::create(0.2f, cocos2d::Point(position->x, position->y));
    cocos2d::CallFunc * callback = cocos2d::CallFunc::create(CC_CALLBACK_0(Actor::onJumpComplete, this));
    cocos2d::FiniteTimeAction *sq = cocos2d::Sequence::create(static_cast<cocos2d::FiniteTimeAction*>(action), static_cast<cocos2d::FiniteTimeAction*>(back), callback, NULL);
    entry->runAction(sq);
}

void Actor::onJumpComplete()
{
    moonsugar::BehaviorCancelJumpEvent * cancelJump = new moonsugar::BehaviorCancelJumpEvent(CANCEL_JUMP_EVENT);
    executeEvent(cancelJump);
    cancelJump = nullptr;
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
        
        std::function<void(cocostudio::Armature * armature, cocostudio::MovementEventType eventType, const std::string &str)> fun = CC_CALLBACK_3(Actor::onNormalAttackComplete, this);
        entry->getAnimation()->setMovementEventCallFunc(fun);
        entry->getAnimation()->play(STATE_NORMAL_ATTACK);
    }
}

void Actor::onNormalAttackComplete(cocostudio::Armature *armature, cocostudio::MovementEventType eventType, const std::string &str)
{
    if (eventType == 1)
    {
        entry->getAnimation()->setMovementEventCallFunc(NULL);
        moonsugar::BehaviorCancelNormalAttackEvent * cancelNormalAttackEvent = new moonsugar::BehaviorCancelNormalAttackEvent(CANCEL_ATTACK_EVENT);
        executeEvent(cancelNormalAttackEvent);
        cancelNormalAttackEvent = nullptr;
    }
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

void Actor::executeJumpEvent(moonsugar::BehaviorEvent *behaviorEvent)
{
    if (stateContext->currentState == STATE_IDLE || stateContext->currentState == STATE_RUN)
    {
        stateContext->currentState = STATE_JUMP;
        
        jump();
    }
}

void Actor::executeCancelJumpEvent(moonsugar::BehaviorEvent *behaviorEvent)
{
    if (stateContext->currentState == STATE_JUMP)
    {
        stateContext->currentState = STATE_IDLE;
        
        entry->getAnimation()->play(STATE_IDLE);
    }
}
NS_MS_END
