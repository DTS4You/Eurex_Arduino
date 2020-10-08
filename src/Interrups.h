#include "ascii_codes.h"
#include "Pin_Setup.h"
#include <RBD_SerialManager.h> // https://github.com/alextaujenis/RBD_SerialManager
#include "Stepper.h"

extern class Stepper::Stepper x_Stepper, y_Stepper, z1_Stepper, z2_Stepper, r_Stepper;

//##############################################################################
//### Interrupts                                                             ###
//##############################################################################
// Timer 3 Interrupt Service Routine
// X-Achse
ISR(TIMER3_COMPA_vect)          // timer compare interrupt service routine
{
	//x_Stepper.set_endstop_positiv(digitalRead(X_p_STOP));		// Endschalter abfragen
	//x_Stepper.set_endstop_negativ(digitalRead(X_n_STOP));		// Endschalter abfragen
	x_Stepper.set_endstop_positiv(0);		// Debug
	x_Stepper.set_endstop_negativ(0);		// Debug
	x_Stepper.step();
}
// Timer 4 Interrupt Service Routine
// Y-Achse
ISR(TIMER4_COMPA_vect)          // timer compare interrupt service routine
{
	//y_Stepper.set_endstop_positiv(digitalRead(Y_p_STOP));		// Endschalter abfragen
	//y_Stepper.set_endstop_negativ(digitalRead(Y_n_STOP));		// Endschalter abfragen
	y_Stepper.set_endstop_positiv(0);		// Debug
	y_Stepper.set_endstop_negativ(0);		// Debug
	y_Stepper.step();
}
// Timer 1 Interrupt Service Routine
// Z1-Achse
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	//z1_Stepper.set_endstop_positiv(0);	// Kein Endschalter vorhanden
	//z1_Stepper.set_endstop_negativ(0);	// Kein Endschalter vorhanden
	z1_Stepper.set_endstop_positiv(0);		// Kein Endschalter vorhanden
	z1_Stepper.set_endstop_negativ(0);		// Kein Endschalter vorhanden
	z1_Stepper.step();
}
// Timer 5 Interrupt Service Routine
// Z2-Achse
ISR(TIMER5_COMPA_vect)				// timer compare interrupt service routine
{
	//z1_Stepper.set_endstop_positiv(0);	// Kein Endschalter vorhanden
	//z1_Stepper.set_endstop_negativ(0);	// Kein Endschalter vorhanden
	z2_Stepper.set_endstop_positiv(0);		// Kein Endschalter vorhanden
	z2_Stepper.set_endstop_negativ(0);		// Kein Endschalter vorhanden
	z2_Stepper.step();
}
// Timer 2 Interrupt Service Routine
// R-Achse
ISR(TIMER2_COMPA_vect)
{
	//r_Stepper.set_endstop_positiv(0);		// Kein Endschalter vorhanden
	//r_Stepper.set_endstop_negativ(0);		// Kein Endschalter vorhanden
	r_Stepper.set_endstop_positiv(0);		// Kein Endschalter vorhanden
	r_Stepper.set_endstop_negativ(0);		// Kein Endschalter vorhanden
	r_Stepper.step();
}
//##############################################################################
