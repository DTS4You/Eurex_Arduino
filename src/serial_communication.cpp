#include <Arduino.h>
#include "ascii_codes.h"
#include "Pin_Setup.h"
#include <RBD_SerialManager.h> // https://github.com/alextaujenis/RBD_SerialManager
#include "Stepper.h"
#include "StateMachine.h"

extern class RBD::SerialManager serial_manager;
extern class Stepper::Stepper x_Stepper, y_Stepper, z1_Stepper, z2_Stepper, r_Stepper;

extern String send_string;

extern class StateMachine::StateMachine state_shutter;

void com_x_stop();
void com_y_stop();
void com_z_stop();
void com_z1_stop();
void com_z2_stop();
void com_r_stop();
void com_x_drive_pos();
void com_x_drive_neg();
void com_x_frequenz(uint16_t);
void com_y_frequenz(uint16_t);


uint8_t readInputs() {
	uint8_t end_stops = 0;
	end_stops = ( digitalRead( X_n_STOP) << 7
					| digitalRead( X_m_STOP) << 6
					| digitalRead( X_p_STOP) << 5
					| digitalRead( Y_n_STOP) << 4
					| digitalRead( Y_p_STOP) << 3
					| digitalRead( R_n_STOP) << 2
					| digitalRead(Z1_n_STOP) << 1
					| digitalRead(Z2_n_STOP) << 0 );
	//end_stops = ~end_stops;		// Aktiv Low -> zum Simulieren negieren
	return end_stops;
}

/*
#ifdef TEST_COM
//------------------------------------------------------------------------------
// Test Kommandos
void com_xstep_pin(uint8_t value) {
	digitalWrite(X_STEP, value);
}

void com_xdir_pin(uint8_t value) {
	digitalWrite(X_DIR, value);
}

void com_ystep_pin(uint8_t value) {
	digitalWrite(Y_STEP, value);
}

void com_ydir_pin(uint8_t value) {
	digitalWrite(Y_DIR, value);
}

void com_z1step_pin(uint8_t value) {
	digitalWrite(Z1_STEP, value);
}

void com_z1dir_pin(uint8_t value) {
	digitalWrite(Z1_DIR, value);
}

void com_z2step_pin(uint8_t value) {
	digitalWrite(Z2_STEP, value);
}

void com_z2dir_pin(uint8_t value) {
	digitalWrite(Z2_DIR, value);
}

void com_rstep_pin(uint8_t value) {
	digitalWrite(R_STEP, value);
}

void com_rdir_pin(uint8_t value) {
	digitalWrite(R_DIR, value);
}
//------------------------------------------------------------------------------
#endif
*/

// Reset
void com_reset()
{
	x_Stepper.reset();
	y_Stepper.reset();
	z1_Stepper.reset();
	z2_Stepper.reset();
	r_Stepper.reset();

	serial_manager.println(ACK);
	//serial_manager.write(ACK);
}
// Sende Position
void com_send_position() {
	send_string = "";
	send_string.concat(x_Stepper.get_position());
	send_string.concat(";");
	send_string.concat(y_Stepper.get_position());
	send_string.concat(";");
	send_string.concat(z1_Stepper.get_position());
	send_string.concat(";");
	send_string.concat(z2_Stepper.get_position());
	send_string.concat(";");
	send_string.concat(r_Stepper.get_position());
	send_string.concat(";");
	send_string.concat(readInputs());
	serial_manager.println(send_string);
}
// Sende Status
void com_send_state() {
	send_string = "";
	send_string.concat("X:");
	send_string.concat(x_Stepper.get_enable());
	send_string.concat(";");
	send_string.concat(x_Stepper.get_direction());
	send_string.concat(";");
	send_string.concat(x_Stepper.get_run());
	send_string.concat(";");
	send_string.concat(OCR3A);
	send_string.concat(" / Y:");
	send_string.concat(y_Stepper.get_enable());
	send_string.concat(";");
	send_string.concat(y_Stepper.get_direction());
	send_string.concat(";");
	send_string.concat(y_Stepper.get_run());
	send_string.concat(";");
	send_string.concat(OCR4A);
	send_string.concat(" / Z1:");
	send_string.concat(z1_Stepper.get_enable());
	send_string.concat(";");
	send_string.concat(z1_Stepper.get_direction());
	send_string.concat(";");
	send_string.concat(z1_Stepper.get_run());
	send_string.concat(";");
	send_string.concat(OCR1A);
	send_string.concat(" / Z2:");
	send_string.concat(z2_Stepper.get_enable());
	send_string.concat(";");
	send_string.concat(z2_Stepper.get_direction());
	send_string.concat(";");
	send_string.concat(z2_Stepper.get_run());
	send_string.concat(";");
	send_string.concat(OCR5A);
	send_string.concat(" / R:");
	send_string.concat(r_Stepper.get_enable());
	send_string.concat(";");
	send_string.concat(r_Stepper.get_direction());
	send_string.concat(";");
	send_string.concat(z2_Stepper.get_run());
	send_string.concat(";");
	send_string.concat(OCR5A);
	serial_manager.println(send_string);
}
// STOP
void com_stop_all() {
	com_x_stop();
	com_y_stop();
	com_z_stop();
	com_r_stop();
}
// Sende Endschalter
void com_send_endstop() {
	send_string = "";
	send_string.concat(readInputs());
	serial_manager.println(send_string);
}
// Referenz Fahrt enable
void com_ref_enable(uint8_t value) {
	//ref_flag = value;
}
// Ausgang 1 schalten
void com_out1(uint8_t value) {
	//digitalWrite(ledPin, value);	// Debug
	digitalWrite(Output_1, value);
}
// Ausgang 2 schalten
void com_out2(uint8_t value) {
	digitalWrite(Output_2, value);
}
// Ausgang 3 schalten
void com_out3(uint8_t value) {
	digitalWrite(Output_3, value);
}
// Debug LED schalten
void com_debug(uint8_t value) {
	digitalWrite(ledPin, value);
}
//########################################################################
//### X-Achse -> Timer 3
//########################################################################
// X-Stepper Enable
void com_x_enable(uint8_t value) {
	x_Stepper.enable(value);
}
// Kommando X-Achse positiv mit Frequenz
void com_x_freq_pos(uint16_t value) {
   x_Stepper.forward();
   x_Stepper.run();
   if(TCNT3 > value) {
      TCNT3 = 0;						// Timer 3 -> X-Achse
   }
   OCR3A = value;						// Timer 3 -> X-Achse
   TIMSK3 |= ( 1 << OCIE3A );		// enable timer compare interrupt
}
// Kommando X-Achse negativ mit Frequenz
void com_x_freq_neg(uint16_t value) {
	x_Stepper.backward();
   x_Stepper.run();
   if(TCNT3 > value) {
      TCNT3 = 0;						// Timer 3 -> X-Achse
   }
   OCR3A = value;						// Timer 3 -> X-Achse
   TIMSK3 |= ( 1 << OCIE3A );		// enable timer compare interrupt
}
// Kommando X-Achse Frequenz übertragen
void com_x_frequenz(uint16_t value) {
	if(TCNT3 > value) {
		TCNT3 = 0;						// Timer 3 -> X-Achse
	}
	OCR3A = value;						// Timer 3 -> X-Achse
	TIMSK3 |= ( 1 << OCIE3A );		// enable timer compare interrupt
}
// Kommando X-Achse positiv bewegen
void com_x_drive_pos() {
	x_Stepper.forward();
	x_Stepper.run();
	TIMSK3 |= ( 1 << OCIE3A );		// enable timer compare interrupt
}
// Kommando X-Achse negativ bewegen
void com_x_drive_neg() {
	x_Stepper.backward();
	x_Stepper.run();
	TIMSK3 |= ( 1 << OCIE3A );		// enable timer compare interrupt
}
// Kommando X-Achse STOP
void com_x_stop() {
   x_Stepper.stop();
   TIMSK3 &= ~( 1 << OCIE3A );	// disable timer compare interrupt
}
//########################################################################
//### Y-Achse -> Timer 4
//########################################################################
// Kommando Y-Achse Enable
void com_y_enable(uint8_t value) {
	y_Stepper.enable(value);
}
// Kommando Y-Achse positiv mit Frequenz
void com_y_freq_pos(uint16_t value) {
	y_Stepper.forward();
	y_Stepper.run();
	if(TCNT4 > value) {
		TCNT4 = 0;						// Timer 4 -> Y-Achse
	}
	OCR4A = value;						// Timer 4 -> Y-Achse
	TIMSK4 |= ( 1 << OCIE4A );		// enable timer compare interrupt
}
// Kommando Y-Achse negativ mit Frequenz
void com_y_freq_neg(uint16_t value) {
	y_Stepper.backward();
	y_Stepper.run();
	if(TCNT4 > value) {
		TCNT4 = 0;						// Timer 4 -> Y-Achse
	}
	OCR4A = value;						// Timer 4 -> Y-Achse
	TIMSK4 |= ( 1 << OCIE4A );		// enable timer compare interrupt
}
// Kommando Y-Achse Frequenz übertragen
void com_y_frequenz(uint16_t value) {
	if(TCNT4 > value) {
		TCNT4 = 0;						// Timer 3 -> X-Achse
	}
	OCR4A = value;						// Timer 3 -> X-Achse
	TIMSK4 |= ( 1 << OCIE4A );		// enable timer compare interrupt
}
// Kommando Y-Achse positiv bewegen
void com_y_drive_pos() {
	y_Stepper.forward();
	y_Stepper.run();
	TIMSK4 |= ( 1 << OCIE4A );		// enable timer compare interrupt
}
// Kommando Y-Achse negativ bewegen
void com_y_drive_neg() {
	y_Stepper.backward();
	y_Stepper.run();
	TIMSK4 |= ( 1 << OCIE4A );		// enable timer compare interrupt
}
// Kommando Y-Achse STOP
void com_y_stop() {
   y_Stepper.stop();
   TIMSK4 &= ~( 1 << OCIE4A );	// disable timer compare interrupt
}
//########################################################################
//### R-Achse -> Timer 5
//########################################################################
// Kommando R-Achse Enable
void com_r_enable(uint8_t value) {
	r_Stepper.enable(value);
}
// Kommando R-Achse positiv mit Frequenz
void com_r_freq_pos(uint16_t value) {
	r_Stepper.forward();
	r_Stepper.run();
	if(TCNT2 > value) {
		TCNT2 = 0;						// Timer 5 -> Y-Achse
	}
	OCR2A = value;						// Timer 5 -> Y-Achse
	TIMSK2 |= ( 1 << OCIE2A );		// enable timer compare interrupt
}
// Kommando R-Achse negativ mit Frequenz
void com_r_freq_neg(uint16_t value) {
	r_Stepper.backward();
	r_Stepper.run();
	if(TCNT2 > value) {
		TCNT2 = 0;						// Timer 5 -> Y-Achse
	}
	OCR2A = value;						// Timer 5 -> Y-Achse
	TIMSK2 |= ( 1 << OCIE2A );		// enable timer compare interrupt
}
// Kommando R-Achse Frequenz übertragen
void com_r_frequenz(uint16_t value) {
	if(TCNT2 > value) {
		TCNT2 = 0;						// Timer 3 -> X-Achse
	}
	OCR2A = value;						// Timer 3 -> X-Achse
	TIMSK2 |= ( 1 << OCIE2A );		// enable timer compare interrupt
}
// Kommando R-Achse positiv bewegen
void com_r_drive_pos() {
	r_Stepper.forward();
	r_Stepper.run();
	TIMSK2 |= ( 1 << OCIE2A );		// enable timer compare interrupt
}
// Kommando R-Achse negativ bewegen
void com_r_drive_neg() {
	r_Stepper.backward();
	r_Stepper.run();
	TIMSK2 |= ( 1 << OCIE2A );		// enable timer compare interrupt
}
// Kommando R-Achse STOP
void com_r_stop() {
	r_Stepper.stop();
	TIMSK2 &= ~( 1 << OCIE2A );	// disable timer compare interrupt
}
//########################################################################
//### Z-Achse -> Timer 1
//########################################################################
// Kommando Z-Achse Enable
void com_z_enable(uint8_t value) {
	z1_Stepper.enable(value);
	z2_Stepper.enable(value);
}
// Kommando Z-Achse positiv mit Frequenz
void com_z_freq_pos(uint16_t value) {
	z1_Stepper.forward();
	z1_Stepper.run();
	z2_Stepper.forward();
	z2_Stepper.run();
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
	TIMSK5 |= ( 1 << OCIE5A );		// enable timer compare interrupt
}
// Kommando Z-Achse negativ mit Frequenz
void com_z_freq_neg(uint16_t value) {
	z1_Stepper.backward();
	z1_Stepper.run();
	z2_Stepper.backward();
	z2_Stepper.run();
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
	TIMSK5 |= ( 1 << OCIE5A );		// enable timer compare interrupt
}
// Kommando Z-Achse Frequenz übertragen
void com_z_frequenz(uint16_t value) {
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
	TIMSK5 |= ( 1 << OCIE5A );		// enable timer compare interrupt
}
// Kommando Z-Achse positiv bewegen
void com_z_drive_pos() {
	z1_Stepper.forward();
	z1_Stepper.run();
	z2_Stepper.forward();
	z2_Stepper.run();
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
	TIMSK5 |= ( 1 << OCIE5A );		// enable timer compare interrupt
}
// Kommando Z-Achse negativ bewegen
void com_z_drive_neg() {
	z1_Stepper.backward();
	z1_Stepper.run();
	z2_Stepper.backward();
	z2_Stepper.run();
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
	TIMSK5 |= ( 1 << OCIE5A );		// enable timer compare interrupt
}
// Kommando Z-Achse STOP
void com_z_stop() {
	z1_Stepper.stop();
	z2_Stepper.stop();
	TIMSK1 &= ~( 1 << OCIE1A );	// disable timer compare interrupt
	TIMSK5 &= ~( 1 << OCIE5A );	// disable timer compare interrupt
}
// Kommando Z1-Achse positiv mit Frequenz
void com_z1_freq_pos(uint16_t value) {
	z1_Stepper.forward();
	z1_Stepper.run();
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	TIMSK1 |= ( 1 << OCIE1A );
}
// Kommando Z1-Achse negativ mit Frequenz
void com_z1_freq_neg(uint16_t value) {
	z1_Stepper.backward();
	z1_Stepper.run();
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	TIMSK1 |= ( 1 << OCIE1A );
}
// Kommando Z1-Achse Frequenz übertragen
void com_z1_frequenz(uint16_t value) {
	if(TCNT1 > value) {
		TCNT1 = 0;
	}
	OCR1A = value;
	TIMSK1 |= ( 1 << OCIE1A );
}
// Kommando Z1-Achse positiv bewegen
void com_z1_drive_pos() {
	z1_Stepper.forward();
	z1_Stepper.run();
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
}
// Kommando Z1-Achse negativ bewegen
void com_z1_drive_neg() {
	z1_Stepper.backward();
	z1_Stepper.run();
	TIMSK1 |= ( 1 << OCIE1A );		// enable timer compare interrupt
}
// Kommando Z1-Achse STOP
void com_z1_stop() {
	z1_Stepper.stop();
	TIMSK1 &= ~( 1 << OCIE1A );	// disable timer compare interrupt
}
// Kommando Z2-Achse positiv mit Frequenz
void com_z2_freq_pos(uint16_t value) {
	z2_Stepper.forward();
	z2_Stepper.run();
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK5 |= ( 1 << OCIE5A );
}
// Kommando Z2-Achse negativ mit Frequenz
void com_z2_freq_neg(uint16_t value) {
	z2_Stepper.backward();
	z2_Stepper.run();
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK5 |= ( 1 << OCIE5A );
}
// Kommando Z2-Achse Frequenz übertragen
void com_z2_frequenz(uint16_t value) {
	if(TCNT5 > value) {
		TCNT5 = 0;
	}
	OCR5A = value;
	TIMSK5 |= ( 1 << OCIE5A );
}
// Kommando Z2-Achse positiv bewegen
void com_z2_drive_pos() {
	z2_Stepper.forward();
	z2_Stepper.run();
	TIMSK5 |= ( 1 << OCIE5A );
}
// Kommando Z2-Achse negativ bewegen
void com_z2_drive_neg() {
	z2_Stepper.backward();
	z2_Stepper.run();
	TIMSK5 |= ( 1 << OCIE5A );
}
// Kommando Z2-Achse STOP
void com_z2_stop() {
	z2_Stepper.stop();
	digitalWrite(Z2_STEP, 0);		// STEP Pin to low
	TIMSK5 &= ~( 1 << OCIE5A );	// disable timer compare interrupt
}
