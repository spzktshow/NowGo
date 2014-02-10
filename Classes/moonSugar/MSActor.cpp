//
//  MSActor.cpp
//  NowGo
//
//  Created by RockLee on 14-2-10.
//
//

#include "MSActor.h"

//state enum
const std::string moonsugar::StateEnum::STATE_IDLE = "stateIdle";
const std::string moonsugar::StateEnum::STATE_NORMAL_ATTACK = "stateNormalAttack";
const std::string moonsugar::StateEnum::STATE_BE_ATTACK = "stateBeAttack";
const std::string moonsugar::StateEnum::STATE_RUN = "stateRun";
const std::string moonsugar::StateEnum::STATE_DEAD = "stateDead";

//behavier event enum
const std::string moonsugar::BehavierEventEnum::DIRECT_EVENT = "directEvent";
const std::string moonsugar::BehavierEventEnum::CANCEL_DIRECT_EVENT = "cancelDirectEvent";
const std::string moonsugar::BehavierEventEnum::NORMAL_ATTACK_EVENT = "normalAttackEvent";
const std::string moonsugar::BehavierEventEnum::CANCEL_ATTACK_EVENT = "cancelAttackEvent";
const std::string moonsugar::BehavierEventEnum::BE_ATTACK_EVENT = "beAttackEvent";
const std::string moonsugar::BehavierEventEnum::CANCEL_BE_ATTACK_EVENT = "cancelBeAttackEvent";
const std::string moonsugar::BehavierEventEnum::DEAD_EVENT = "deadEvent";