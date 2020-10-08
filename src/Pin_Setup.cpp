#include <Arduino.h>
#include "Pin_Setup.h"

void Pin_Setup()
{
   pinMode(X_n_STOP, INPUT_PULLUP);
   pinMode(X_m_STOP, INPUT_PULLUP);
   pinMode(X_p_STOP, INPUT_PULLUP);
   pinMode(Y_n_STOP, INPUT_PULLUP);
   pinMode(Y_p_STOP, INPUT_PULLUP);
   pinMode(Z1_n_STOP, INPUT_PULLUP);
   pinMode(Z2_n_STOP, INPUT_PULLUP);
   pinMode(R_n_STOP, INPUT_PULLUP);

	/*		Werden über Stepper.cpp definiert
   pinMode(X_Enable, OUTPUT);
   pinMode(X_STEP, OUTPUT);
   pinMode(X_DIR, OUTPUT);

   pinMode(Y_Enable, OUTPUT);
   pinMode(Y_STEP, OUTPUT);
   pinMode(Y_DIR, OUTPUT);

   pinMode(Z1_Enable, OUTPUT);
   pinMode(Z1_STEP, OUTPUT);
   pinMode(Z1_DIR, OUTPUT);

   pinMode(Z2_Enable, OUTPUT);
   pinMode(Z2_STEP, OUTPUT);
   pinMode(Z2_DIR, OUTPUT);

   pinMode(R_Enable, OUTPUT);
   pinMode(R_STEP, OUTPUT);
   pinMode(R_DIR, OUTPUT);
	*/

   pinMode(Output_1, OUTPUT);
   pinMode(Output_2, OUTPUT);
   pinMode(Output_3, OUTPUT);
   pinMode(Output_4, OUTPUT);

	pinMode(ledPin, OUTPUT);


   digitalWrite(Y_Enable, 0);
   digitalWrite(Y_STEP, 0);
   digitalWrite(Y_DIR, 0);

   digitalWrite(Z1_Enable, 0);
   digitalWrite(Z1_STEP, 0);
   digitalWrite(Z1_DIR, 0);

   digitalWrite(Z2_Enable, 0);
   digitalWrite(Z2_STEP, 0);
   digitalWrite(Z2_DIR, 0);

   digitalWrite(R_Enable, 0);
   digitalWrite(R_STEP, 0);
   digitalWrite(R_DIR, 0);

	digitalWrite(Output_1, 0);
	digitalWrite(Output_2, 0);
	digitalWrite(Output_3, 0);
	digitalWrite(Output_4, 0);

   pinMode(EXT_TASTER_1, INPUT);
   pinMode(EXT_TASTER_2, INPUT);
   pinMode(EXT_LED_1, OUTPUT);
   pinMode(EXT_LED_2, OUTPUT);

}
