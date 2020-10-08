#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

class Stepper
{
	public:
		Stepper();
      virtual ~Stepper();
		void setup(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint16_t);
		void reset();
		void step();
		void run();
		void stop();
		void forward();
		void backward();
		void enable(bool);
		void set_endstop_positiv(bool);
		bool get_endstop_positiv();
		void set_endstop_negativ(bool);
		bool get_endstop_negativ();
		uint16_t get_position();
		void set_position(uint16_t);
		bool get_enable();
		bool get_direction();
		bool get_run();

    protected:

    private:
		 uint16_t	_position;
		 uint16_t	_position_ovf;
		 uint16_t	_position_min;
		 uint16_t	_position_max;
		 uint8_t		_step_pin;
		 uint8_t		_dir_pin;
		 uint8_t		_enable_pin;
		 int8_t		_sub_step;				// Mit Vorzeichen, da Test auf < 0
		 uint8_t		_sub_step_max;
		 bool 		_step_state;
		 bool			_enable;
		 bool 		_direction;
		 bool 		_run;
		 bool 		_endstop_pos;
		 bool			_endstop_neg;
};

#endif
