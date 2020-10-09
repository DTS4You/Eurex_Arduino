//#############################################################################
//### UBoot-Stepper                                                         ###
//#############################################################################
//### Version 1.06                                                          ###
//###																		###
//### Ardiono 2560 auf MKS Gen V1.4 Board                                   ###
//### Datum			: 04.06.2019                                            ###
//### Änderungen	:                                                       ###
//###             		Ausgangsrelais hinzu                                ###
//###             		R-Achse auf Timer 2                                 ###
//###             		Z-Ache auf Timer 1 und 5 verteilt                   ###
//###					Achsen Overflow hinzu				    			###
//###					Externe Taster hinzu 	-> D23 / D25 / D27 / D29    ###
//###				    Externe Taster geändert	-> D14 / D15 / D18 / D19    ###
//###					com_out1 -> Aus - Auto - Ein -> Serial Modul	    ###
//###					out1,1 -> Scheibe undurchsichtig                    ###
//###					out1,0 -> Scheibe durchsichtig                      ###
//###					Umstieg auf Windows								    ###
//#############################################################################

//#define DEBUG_defs
//#define TEST_COM
//#defibe TEST

#include <RBD_Timer.h>         // https://github.com/alextaujenis/RBD_Timer
#include <RBD_SerialManager.h> // https://github.com/alextaujenis/RBD_SerialManager

#include "ascii_codes.h"
#include "Pin_Setup.h"
#include "Timer_Setup.h"

#include "serial_communication.h"
#include "Stepper.h"

#include <RBD_Button.h>
#include <RBD_Light.h>

#include <StateMachine.h>

#define X_STEP_DIV	19
#define Y_STEP_DIV	19
#define Z1_STEP_DIV	19
#define Z2_STEP_DIV	19
#define R_STEP_DIV	0

#define X_STEP_MIN	0
#define X_STEP_MAX	1000
#define X_STEP_OVF	65535
#define Y_STEP_MIN	0
#define Y_STEP_MAX	65535
#define Y_STEP_OVF	65535
#define Z_STEP_MIN	0
#define Z_STEP_MAX	65535
#define Z_STEP_OVF	65535
#define R_STEP_MIN	0
#define R_STEP_MAX	65535
#define R_STEP_OVF	12799

#define BLINK_TIME	300		// ms

volatile uint16_t value_16		= 0;
volatile uint8_t	value_8		= 0;

volatile uint16_t x_pos  		= 0;
volatile uint16_t x_pos_max	= 65000;
volatile uint16_t y_pos  		= 0;
volatile uint16_t y_pos_max	= 65000;
volatile uint16_t z1_pos 		= 0;
volatile uint16_t z1_pos_max	= 2000;
volatile uint16_t z2_pos 		= 0;
volatile uint16_t z2_pos_max	= 2000;
volatile int16_t  r_pos			= 0;		// Rotation der Z-Achse, drehen auf der Hochachse, mit Vorzeichen, um negativen Überlauf zu testen
volatile uint16_t	status_f		= 0;

//volatile uint16_t	test_value 	= 0xAA55;

volatile String send_string = "";

#include "Interrups.h"

void Pin_Setup();

RBD::SerialManager serial_manager;

Stepper x_Stepper;
Stepper y_Stepper;
Stepper z1_Stepper;
Stepper z2_Stepper;
Stepper r_Stepper;

//------------------------------------------------------------------------------
// Externe Taster einbinden
RBD::Timer blink_task;
RBD::Button taster_uboot(EXT_TASTER_1, false);		// disable input pullup
RBD::Button taster_shutter(EXT_TASTER_2, false);		// disable input pullup
RBD::Light led_1(EXT_LED_1);
RBD::Light led_2(EXT_LED_2);
StateMachine state_shutter;
StateMachine state_uboot;
//------------------------------------------------------------------------------
//##############################################################################
//### Setup                                                                  ###
//##############################################################################
void setup() {

	serial_manager.start();

	Pin_Setup();
	// Init Timer
	noInterrupts();           // disable all interrupts
	// Timer Setup
	Timer_Setup();

	interrupts();             // enable all interrupts

	x_Stepper.setup(X_STEP, X_DIR, X_Enable, X_STEP_DIV, X_STEP_MIN, X_STEP_MAX, X_STEP_OVF);
	y_Stepper.setup(Y_STEP, Y_DIR, Y_Enable, Y_STEP_DIV, Y_STEP_MIN, Y_STEP_MAX, Y_STEP_OVF);
	z1_Stepper.setup(Z1_STEP, Z1_DIR, Z1_Enable, Z1_STEP_DIV, Z_STEP_MIN, Z_STEP_MAX, Z_STEP_OVF);
	z2_Stepper.setup(Z2_STEP, Z2_DIR, Z2_Enable, Z2_STEP_DIV, Z_STEP_MIN, Z_STEP_MAX, Z_STEP_OVF);
	r_Stepper.setup(R_STEP, R_DIR, R_Enable, R_STEP_DIV, R_STEP_MIN, R_STEP_MAX, R_STEP_OVF);

	// Externe Taster
	blink_task.setTimeout(BLINK_TIME);
	blink_task.restart();

	taster_shutter.invertReading();
	taster_uboot.invertReading();

	state_shutter.setup(3);		// Max State -> off / auto / on
	state_uboot.setup(2);		// Max State -> off / auto

	led_1.on();
	led_2.on();

	#ifdef DEBUG_defs
	x_pos 	= 16384;
	y_pos 	=  8192;
	z1_pos 	=  4096;
	z2_pos	=	2048;
	r_pos		=	1024;
	#endif
}
//##############################################################################





//##############################################################################
//### Main-Loop                                                              ###
//##############################################################################
void loop() {
	// Serielle Kommunikation
	serial_communication();

	//---------------------------------------------------------------------------
	// Externe Taster
	//---------------------------------------------------------------------------
	// Taster 1 abfragen
	if (taster_uboot.onPressed()) {
		state_uboot.state_inc();
	}
	//---------------------------------------------------------------------------
	// UBoot StateMachine
	//---------------------------------------------------------------------------
	if (state_uboot.onchange()){
		if (state_uboot.get_state() == 0) {
			led_1.on();
		}
		if (state_uboot.get_state() == 1) {
			led_1.blink(400, 400);
		}
	}
	//---------------------------------------------------------------------------

	// Taster 2 abfragen
	if (taster_shutter.onPressed()) {
		state_shutter.state_inc();
	}
	//---------------------------------------------------------------------------
	// Shutter State
	//---------------------------------------------------------------------------
	if (state_shutter.onchange()) {
		if (state_shutter.get_state() == 0)	{		// State off
			led_2.off();
			com_out1(0);
		}
		if (state_shutter.get_state() == 1)	{		// State auto
			led_2.blink(400, 400);
		}
		if (state_shutter.get_state() == 2)	{		// State on
			led_2.blink(800, 800);
			com_out1(1);
		}
	}
	//---------------------------------------------------------------------------

	led_1.update();
	led_2.update();
	//---------------------------------------------------------------------------

}
//##############################################################################
