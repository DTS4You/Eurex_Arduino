#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

class StateMachine
{
	public:
		StateMachine();
      virtual ~StateMachine();
		void setup(uint8_t);
		void reset();
		boolean onchange();
		void state_inc();
		uint8_t get_state();

    protected:

    private:
		 uint8_t	_max_state;
		 uint8_t	_act_state;
		 uint8_t	_last_state;
};

#endif
