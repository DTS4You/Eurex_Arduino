#ifndef PIN_SETUP_H
#define PIN_SETUP_H

#include <Arduino.h>
//##############################################################################
//### PinMapping                                                             ###
//##############################################################################

#define X_Enable        38
#define X_STEP          54			// A0
#define X_DIR           55			// A1

#define Y_Enable        56			// A2
#define Y_STEP          60			// A6
#define Y_DIR           61			// A7

#define Z1_Enable       62       // A8
#define Z1_STEP         46
#define Z1_DIR          48

#define Z2_Enable       24
#define Z2_STEP         26
#define Z2_DIR          28

#define R_Enable        30
#define R_STEP          36
#define R_DIR           34


#define X_n_STOP        63			// MKS Gen -> AUX-2
#define X_m_STOP        59			// MKS Gen -> AUX-2
#define X_p_STOP        40			// MKS Gen -> AUX-2

#define Y_n_STOP        64			// MKS Gen -> AUX-2
#define Y_p_STOP        42			// MKS Gen -> AUX-2

#define R_n_STOP        44			// MKS Gen -> AUX-2
#define Z1_n_STOP       65			// MKS Gen -> AUX-2
#define Z2_n_STOP       66			// MKS Gen -> AUX-2

#define Output_1        9
#define Output_2        10
#define Output_3        7
#define Output_4        8

#define ledPin          13

#define EXT_TASTER_1    14		// Y-STOP -
#define EXT_LED_1       15		// Y-STOP +
#define EXT_TASTER_2		18		// Z-STOP -
#define EXT_LED_2			19		// Z-STOP +

#endif
