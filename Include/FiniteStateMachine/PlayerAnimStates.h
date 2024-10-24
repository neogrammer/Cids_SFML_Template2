#pragma once
#include <FiniteStateMachine/IgnoreUnknownEvent.h>
#include <variant>
#include <FiniteStateMachine/Events.h>

struct IdleState { };
struct RunningState {};
struct InAirState {};
struct InAirPeakState {};
struct InAirFallState {};
struct ShootingState {};
struct InAirShootingState {};
struct InAirPeakShootingState {};
struct InAirFallShootingState{};
struct RunningAndShootingState {};

using PlayerAnimVar = std::variant<IdleState, RunningState,InAirState,InAirPeakState,InAirFallState,ShootingState,InAirShootingState, InAirPeakShootingState, InAirFallShootingState,RunningAndShootingState>;


