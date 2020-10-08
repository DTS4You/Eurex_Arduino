#include <Arduino.h>
#include "Stepper.h"
#include "Pin_Setup.h"

Stepper::Stepper()
{
	_position		= 0;
	_position_ovf  = 65535;
	_position_min	= 0;
	_position_max	= 65535;
	_sub_step		= 0;
	_sub_step_max	= 19;
	_step_state		= false;
	_enable			= false;
	_direction		= false;
	_run				= false;
	_endstop_pos	= false;
	_endstop_neg	= false;
}

Stepper::~Stepper()
{
    //dtor
}
// Stepper Setup
void Stepper::setup(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin, uint8_t sub_step_max, uint16_t position_min, uint16_t position_max, uint16_t position_ovf)
{
	_step_pin		= step_pin;
	_dir_pin			= dir_pin;
	_enable_pin		= enable_pin;
	_sub_step_max	= sub_step_max;
	_position_min	= position_min;
	_position_max	= position_max;
	_position_ovf	= position_ovf;
	pinMode(_step_pin, OUTPUT);
	pinMode(_dir_pin, OUTPUT);
	pinMode(_enable_pin, OUTPUT);
	digitalWrite(_step_pin, _step_state);
	digitalWrite(_dir_pin, _direction);
	digitalWrite(_enable_pin, _enable);
}
// Stepper Reset
void Stepper::reset()
{
	_position 	= 0;
	_sub_step	= 0;
	_direction	= false;
	stop();
	enable(false);
}
// Stepper Enable
void Stepper::enable(bool enable)
{
	_enable = enable;
	digitalWrite(_enable_pin, _enable);
	//digitalWrite(ledPin, _enable);		// Debug
}
// Stepper Step
void Stepper::step()
{
	if(_run) {
		if(!_direction and !_endstop_pos) {
			//if(_position < _position_max) {
			if(1) {
				_step_state = !_step_state;
				digitalWrite(_step_pin, _step_state);		// Step Pin
				//digitalWrite(ledPin, _step_state);  		// Debug
				if(_sub_step >= _sub_step_max) {
					_sub_step = 0;
					if(_position < _position_ovf) {
						_position++;
					} else {
						_position = 0;
					}
				} else {
					_sub_step++;
				}
			}
		}
		if( _direction and !_endstop_neg) {
			//if(_position > _position_min) {
			if(1) {
				_step_state = !_step_state;
				digitalWrite(_step_pin, _step_state);		// Step Pin
				//digitalWrite(ledPin, _step_state);  		// Debug
				if(_sub_step <= 0) {
					_sub_step = _sub_step_max;
					if(_position > 0) {
						_position--;
					} else {
						_position = _position_ovf;
					}

				} else {
					_sub_step--;
				}
			}
		}
	}
}
// Stepper Run
void Stepper::run()
{
	_run = true;
}
void Stepper::stop()
{
	_run = false;
	_step_state = false;		// Optional -> Step_Pin to low
}
void Stepper::forward()
{
	_direction = false;
	digitalWrite(_dir_pin, _direction);
	//digitalWrite(ledPin, _direction);			// Debug
}
void Stepper::backward()
{
	_direction = true;
	digitalWrite(_dir_pin, _direction);
	//digitalWrite(ledPin, _direction);			// Debug
}
void Stepper::set_endstop_positiv(bool endstop_positiv)
{
	_endstop_pos = endstop_positiv;
}
bool Stepper::get_endstop_positiv()
{
	return _endstop_pos;
}
void Stepper::set_endstop_negativ(bool endstop_negativ)
{
	_endstop_neg = endstop_negativ;
}
bool Stepper::get_endstop_negativ()
{
	return _endstop_neg;
}
bool Stepper::get_enable()
{
	return _enable;
}
bool Stepper::get_direction()
{
	return _direction;
}
bool Stepper::get_run()
{
	return _run;
}
uint16_t Stepper::get_position()
{
	return _position;
}
void Stepper::set_position(uint16_t position)
{
	_position = position;
}
