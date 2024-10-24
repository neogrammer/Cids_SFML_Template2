#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FiniteStateMachine/DuckFold.h>
#include <optional>
#include <iostream>
#include <type_traits>
#include <variant>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e)	{	return InAirState{}; 	}
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e)	{	return RunningState{}; 	}
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e)	{	return ShootingState{};	}
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedFalling& e) { return InAirFallState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStartedShooting& e) {	return RunningAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStartedFalling& e) { return InAirFallState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStoppedMoving& e) { return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventJumped& e)	{	return InAirState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventReachedJumpPeak& e) { return InAirPeakState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventStartedFalling& e) { return InAirFallState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventStartedShooting& e)	{	return InAirShootingState{}; 	}
	std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}
	std::optional<PlayerAnimVar> On_Event(InAirPeakState& s, const EventStartedFalling& e) { return InAirFallState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirPeakState& s, const EventStartedShooting& e) { return InAirPeakShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirPeakState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}
	std::optional<PlayerAnimVar> On_Event(InAirFallState& s, const EventStartedShooting& e) { return InAirFallShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirFallState& s, const EventStartedMoving& e) {
		return InAirFallState{};
	}

	std::optional<PlayerAnimVar> On_Event(InAirFallState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventJumped& e)	{	return InAirShootingState{}; 	}
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedMoving& e)	{	return RunningAndShootingState{}; 	}
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { 	return IdleState{};	}
	std::optional<PlayerAnimVar> On_Event(InAirShootingState& s, const EventReachedJumpPeak& e) { return InAirPeakShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirShootingState& s, const EventStoppedShooting& e) {	return InAirState{}; 	}
	std::optional<PlayerAnimVar> On_Event(InAirShootingState& s, const EventStartedFalling& e) { return InAirFallShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirShootingState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}
	std::optional<PlayerAnimVar> On_Event(InAirPeakShootingState& s, const EventStoppedShooting& e) { return InAirPeakState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirPeakShootingState& s, const EventStartedFalling& e) { return InAirFallShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirPeakShootingState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningAndShootingState{};
		else
			return ShootingState{};
	}
	std::optional<PlayerAnimVar> On_Event(InAirFallShootingState& s, const EventStoppedShooting& e) { return InAirFallState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirFallShootingState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningAndShootingState{};
		else
			return ShootingState{};
	}
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventJumped& e)	{	return InAirShootingState{}; 	}
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventStoppedShooting& e)	{	return RunningState{};  }
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventStoppedMoving& e) { return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningAndShootingState& s, const EventStartedFalling& e) { return InAirFallShootingState{}; }

	

	template <typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&) { 	return std::nullopt; 	}
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "IdleState"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "ShootingState"; }
		else if (std::holds_alternative<InAirState>(state_)) { return "InAirState"; }
		else if (std::holds_alternative<RunningState>(state_)) { return "RunningState"; }
		else if (std::holds_alternative<RunningAndShootingState>(state_)) { return "RunningAndShootingState"; }
		else if (std::holds_alternative<InAirShootingState>(state_)) { return "InAirShootingState"; }
		else if (std::holds_alternative<InAirFallState>(state_)) { return "InAirFallState"; }
		else if (std::holds_alternative<InAirFallShootingState>(state_)) { return "InAirFallShootingState"; }
		else if (std::holds_alternative<InAirPeakShootingState>(state_)) { return "InAirPeakShootingState"; }
		else if (std::holds_alternative<InAirPeakState>(state_)) { return "InAirPeakState"; }
		else { return "NoStateCurrentlyHeld"; }
	}
};

#endif