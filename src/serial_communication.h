// Serielle Kommunikation
#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H

#include "ascii_codes.h"
#include <RBD_SerialManager.h> // https://github.com/alextaujenis/RBD_SerialManager
#include <Arduino.h>
#include "Pin_Setup.h"
#include "Stepper.h"
#include "StateMachine.h"

extern class RBD::SerialManager serial_manager;
extern class Stepper::Stepper x_Stepper, y_Stepper, z1_Stepper, z2_Stepper, r_Stepper;

extern class StateMachine::StateMachine state_shutter;

//void its_on();
void com_reset();
void com_send_state();
void com_send_position();
void com_stop_all();
void com_send_endstop();
void com_ref_enable(uint8_t);
void com_out1(uint8_t);
void com_out2(uint8_t);
void com_out3(uint8_t);
void com_debug(uint8_t);
void com_x_enable(uint8_t);
void com_x_freq_pos(uint16_t);
void com_x_freq_neg(uint16_t);
void com_x_frequenz(uint16_t);
void com_x_drive_pos();
void com_x_drive_neg();
void com_x_stop();
void com_y_enable(uint8_t);
void com_y_freq_pos(uint16_t);
void com_y_freq_neg(uint16_t);
void com_y_frequenz(uint16_t);
void com_y_drive_pos();
void com_y_drive_neg();
void com_y_stop();
void com_z_enable(uint8_t);
void com_z_freq_pos(uint16_t);
void com_z_freq_neg(uint16_t);
void com_z_frequenz(uint16_t);
void com_z_drive_pos();
void com_z_drive_neg();
void com_z_stop();
void com_z1_enable(uint8_t);
void com_z1_freq_pos(uint16_t);
void com_z1_freq_neg(uint16_t);
void com_z1_frequenz(uint16_t);
void com_z1_drive_pos();
void com_z1_drive_neg();
void com_z1_stop();
void com_z2_enable(uint8_t);
void com_z2_freq_pos(uint16_t);
void com_z2_freq_neg(uint16_t);
void com_z2_frequenz(uint16_t);
void com_z2_drive_pos();
void com_z2_drive_neg();
void com_z2_stop();
void com_r_enable(uint8_t);
void com_r_freq_pos(uint16_t);
void com_r_freq_neg(uint16_t);
void com_r_frequenz(uint16_t);
void com_r_drive_pos();
void com_r_drive_neg();
void com_r_stop();


void serial_communication()
{
	extern uint8_t 	value_8;
	extern uint16_t 	value_16;
	// you must set the serial monitor to include a newline with each command
	if(serial_manager.onReceive()) {
		// Kommando Reset
		if(serial_manager.isCmd("res")) {
			com_reset();
		}
		// Kommando Status
		if(serial_manager.isCmd("sta")) {
			com_send_state();
		}
		// Kommando Position
		if(serial_manager.isCmd("pos")) {
			com_send_position();
		}
		// Kommando alle Achsen STOP
		if(serial_manager.isCmd("stop")) {
			com_stop_all();
			serial_manager.println(ACK);
		}
		// Kommando Endschalter abfragen
		if(serial_manager.isCmd("est")) {
			com_send_endstop();
		}
		// Kommando Relais 1 schalten
		if(serial_manager.isCmd("out1")) {
			value_8 = serial_manager.getParam().toInt();
			if (state_shutter.get_state() == 1) {		// Auto Mode
				com_out1(value_8);
			}
			serial_manager.println(ACK);
		}
		if(serial_manager.isCmd("out2")) {
			value_8 = serial_manager.getParam().toInt();
			com_out2(value_8);
			serial_manager.println(ACK);
		}
		if(serial_manager.isCmd("out3")) {
			value_8 = serial_manager.getParam().toInt();
			com_out3(value_8);
			serial_manager.println(ACK);
		}
		if(serial_manager.isCmd("debug")) {
			value_8 = serial_manager.getParam().toInt();
			com_debug(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Referenz Fahrt enable
		if(serial_manager.isCmd("ref")) {
			value_8 = serial_manager.getParam().toInt();
			com_ref_enable(value_8);
			serial_manager.println(ACK);
		}
		// Kommando X-Achse auf Pos. 0
		if(serial_manager.isCmd("xpn")) {
			x_Stepper.set_position(0);
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse auf Pos. 0
		if(serial_manager.isCmd("ypn")) {
			y_Stepper.set_position(0);
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse auf Pos. 0
		if(serial_manager.isCmd("zpn")) {
			z1_Stepper.set_position(0);
			z2_Stepper.set_position(0);
			serial_manager.println(ACK);
		}
		// Kommando R-Achse auf Pos.0
		if(serial_manager.isCmd("rpn")) {
			r_Stepper.set_position(0);
			serial_manager.println(ACK);
		}
		// Kommando X-Position setzen
		if(serial_manager.isCmd("xpp")) {
			value_16 = serial_manager.getParam().toInt();
			x_Stepper.set_position(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Y-Position setzen
		if(serial_manager.isCmd("ypp")) {
			value_16 = serial_manager.getParam().toInt();
			y_Stepper.set_position(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z-position setzen
		if(serial_manager.isCmd("zpp")) {
			value_16 = serial_manager.getParam().toInt();
			z1_Stepper.set_position(value_16);
			z2_Stepper.set_position(value_16);
			serial_manager.println(ACK);
		}
		// Kommando R-Position setzen
		if(serial_manager.isCmd("rpp")) {
			value_16 = serial_manager.getParam().toInt();
			r_Stepper.set_position(value_16);
			serial_manager.println(ACK);
		}
		// Kommando X-Max setzen
		if(serial_manager.isCmd("xpm")) {
			value_16 = serial_manager.getParam().toInt();
			//x_pos_max = value_16;
			serial_manager.println(ACK);
		}
		// Kommando Y-Max setzen
		if(serial_manager.isCmd("ypm")) {
			value_16 = serial_manager.getParam().toInt();
			//y_pos_max = value_16;
			serial_manager.println(ACK);
		}
		// Kommando Z-Max setzen
		if(serial_manager.isCmd("zpm")) {
			value_16 = serial_manager.getParam().toInt();
			//z1_pos_max	= value_16;
			//z2_pos_max	= value_16;
			serial_manager.println(ACK);
		}
		//########################################################################
		//### X-Achse
		//########################################################################
		// Kommando X-Achse Enable
		if(serial_manager.isCmd("xen")) {
			value_8 = serial_manager.getParam().toInt();
			com_x_enable(value_8);
			serial_manager.println(ACK);
		}
		// Kommando X-Achse positiv mit Frequenz
		if(serial_manager.isCmd("xfp")) {
			value_16 = serial_manager.getParam().toInt();
			com_x_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando X-Achse negativ mit Frequenz
		if(serial_manager.isCmd("xfn")) {
			value_16 = serial_manager.getParam().toInt();
			com_x_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando X-Achse Frequenz übertragen
		if(serial_manager.isCmd("xfs")) {
			value_16 = serial_manager.getParam().toInt();
			com_x_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando X-Achse fahre in positive Richtung
		if(serial_manager.isCmd("xdp")) {
			com_x_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando X-Achse fahre in negative Richtung
		if(serial_manager.isCmd("xdn")) {
			//com_x_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando X-Achse Stop
		if(serial_manager.isCmd("xst")) {
			com_x_stop();
			serial_manager.println(ACK);
		}
		//########################################################################
		//### Y-Achse
		//########################################################################
		// Kommando Y-Achse Enable
		if(serial_manager.isCmd("yen")) {
			value_8 = serial_manager.getParam().toInt();
			com_y_enable(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse positiv mit Frequenz
		if(serial_manager.isCmd("yfp")) {
			value_16 = serial_manager.getParam().toInt();
			com_y_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse negativ mit Frequenz
		if(serial_manager.isCmd("yfn")) {
			value_16 = serial_manager.getParam().toInt();
			com_y_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse Frequenz übertragen
		if(serial_manager.isCmd("yfs")) {
			value_16 = serial_manager.getParam().toInt();
			com_y_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse fahre in positive Richtung
		if(serial_manager.isCmd("ydp")) {
			com_y_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse fahre in negative Richtung
		if(serial_manager.isCmd("ydn")) {
			com_y_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando Y-Achse Stop
		if(serial_manager.isCmd("yst")) {
			com_y_stop();
			serial_manager.println(ACK);
		}
		//########################################################################
		//### R-Achse
		//########################################################################
		// Kommando R-Achse Enable
		if(serial_manager.isCmd("ren")) {
			value_8 = serial_manager.getParam().toInt();
			com_r_enable(value_8);
			serial_manager.println(ACK);
		}
		// Kommando R-Achse positiv mit Frequenz
		if(serial_manager.isCmd("rfp")) {
			value_16 = serial_manager.getParam().toInt();
			com_r_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando R-Achse negativ mit Frequenz
		if(serial_manager.isCmd("rfn")) {
			value_16 = serial_manager.getParam().toInt();
			com_r_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando R-Achse Frequenz übertragen
		if(serial_manager.isCmd("rfs")) {
			value_16 = serial_manager.getParam().toInt();
			com_r_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando R-Achse fahre in positive Richtung
		if(serial_manager.isCmd("rdp")) {
			com_r_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando R-Achse fahre in negative Richtung
		if(serial_manager.isCmd("rdn")) {
			com_r_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando R-Achse Stop
		if(serial_manager.isCmd("rst")) {
			com_r_stop();
			serial_manager.println(ACK);
		}
		//########################################################################
		//### Z-Achse
		//########################################################################
		// Kommando Z-Achse Enable
		if(serial_manager.isCmd("zen")) {
			value_8 = serial_manager.getParam().toInt();
			com_z_enable(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse positiv mit Frequenz
		if(serial_manager.isCmd("zfp")) {
			value_16 = serial_manager.getParam().toInt();
			com_z_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse negativ mit Frequenz
		if(serial_manager.isCmd("zfn")) {
			value_16 = serial_manager.getParam().toInt();
			com_z_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse Frequenz übertragen
		if(serial_manager.isCmd("zfs")) {
			value_16 = serial_manager.getParam().toInt();
			com_z_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse fahre in positive Richtung
		if(serial_manager.isCmd("zdp")) {
			com_z_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse fahre in negative Richtung
		if(serial_manager.isCmd("zdn")) {
			com_z_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando Z-Achse Stop
		if(serial_manager.isCmd("zst")) {
			com_z_stop();
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse positiv mit Frequenz
		if(serial_manager.isCmd("z1fp")) {
			value_16 = serial_manager.getParam().toInt();
			com_z1_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse negativ mit Frequenz
		if(serial_manager.isCmd("z1fn")) {
			value_16 = serial_manager.getParam().toInt();
			com_z1_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse Frequenz übertragen
		if(serial_manager.isCmd("z1fs")) {
			value_16 = serial_manager.getParam().toInt();
			com_z1_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse fahre in positive Richtung
		if(serial_manager.isCmd("z1dp")) {
			com_z1_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse fahre in negative Richtung
		if(serial_manager.isCmd("z1dn")) {
			com_z1_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando Z1-Achse Stop
		if(serial_manager.isCmd("z1st")) {
			com_z1_stop();
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse positiv mit Frequenz
		if(serial_manager.isCmd("z2fp")) {
			value_16 = serial_manager.getParam().toInt();
			com_z2_freq_pos(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse negativ mit Frequenz
		if(serial_manager.isCmd("z2fn")) {
			value_16 = serial_manager.getParam().toInt();
			com_z2_freq_neg(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse Frequenz übertragen
		if(serial_manager.isCmd("z2fs")) {
			value_16 = serial_manager.getParam().toInt();
			com_z2_frequenz(value_16);
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse fahre in positive Richtung
		if(serial_manager.isCmd("z2dp")) {
			com_z2_drive_pos();
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse fahre in negative Richtung
		if(serial_manager.isCmd("z2dn")) {
			com_z2_drive_neg();
			serial_manager.println(ACK);
		}
		// Kommando Z2-Achse Stop
		if(serial_manager.isCmd("z2st")) {
			com_z2_stop();
			serial_manager.println(ACK);
		}
		/*
		//########################################################################
		//### Kommunikations-Test Pins ansteuern
		//########################################################################
		#ifdef TEST_COM
		// Kommando X-STEP-Pin
		if(serial_manager.isCmd("xstep")) {
			value_8 = serial_manager.getParam().toInt();
			com_xstep_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando X-Dir-Pin
		if(serial_manager.isCmd("xdir")) {
			value_8 = serial_manager.getParam().toInt();
			com_xdir_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Y-STEP-Pin
		if(serial_manager.isCmd("ystep")) {
			value_8 = serial_manager.getParam().toInt();
			com_ystep_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Y-Dir-Pin
		if(serial_manager.isCmd("ydir")) {
			value_8 = serial_manager.getParam().toInt();
			com_ydir_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Z1-STEP-Pin
		if(serial_manager.isCmd("z1step")) {
			value_8 = serial_manager.getParam().toInt();
			com_z1step_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Z1-Dir-Pin
		if(serial_manager.isCmd("z1dir")) {
			value_8 = serial_manager.getParam().toInt();
			com_z1dir_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Z2-STEP-Pin
		if(serial_manager.isCmd("z2step")) {
			value_8 = serial_manager.getParam().toInt();
			com_z2step_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando Z2-Dir-Pin
		if(serial_manager.isCmd("z2dir")) {
			value_8 = serial_manager.getParam().toInt();
			com_z2dir_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando R-STEP-Pin
		if(serial_manager.isCmd("rstep")) {
			value_8 = serial_manager.getParam().toInt();
			com_rstep_pin(value_8);
			serial_manager.println(ACK);
		}
		// Kommando R-Dir-Pin
		if(serial_manager.isCmd("rdir")) {
			value_8 = serial_manager.getParam().toInt();
			com_rdir_pin(value_8);
			serial_manager.println(ACK);
		}
		#endif
		//########################################################################
		*/
	}
}


#endif
