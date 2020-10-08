#include <Arduino.h>
#include "StateMachine.h"
//#include "Pin_Setup.h"

StateMachine::StateMachine() {
	_max_state		= 0;
	_act_state		= 0;
	_last_state		= 99;
}

StateMachine::~StateMachine() {
    //dtor
}
// StateMachine Setup
void StateMachine::setup(uint8_t max_state) {
	_max_state		= max_state - 1 ;
}
// StateMachine Reset
void StateMachine::reset() {
	_act_state 	= 0;
}
// StateMachine State -> Change
boolean StateMachine::onchange() {
	if (_last_state == _act_state) {
		return false;
	}
	else {
		_last_state = _act_state;
		return true;
	}
}
// StateMachine State -> Increment
void StateMachine::state_inc() {
	if (_act_state < _max_state) {
		_act_state++;
	}
	else {
		_act_state = 0;
	}
}
// StateMachine get State
uint8_t StateMachine::get_state() {
	return _act_state;
}
