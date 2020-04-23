//==========================================================================================
//----------------------------------- MOTO -------------------------------------------------
//==========================================================================================
#include <Arduino.h>
#include <AceButton.h>
using namespace ace_button;

//-------------------------------- Pulsadores-----------------------------------------------
const byte PULSADOR_START_PIN = A0;			//A0 Pin Arranque
const byte PULSADOR_TURN_R_PIN = A1;		//A1 Pin Pulsador Derecho
const byte PULSADOR_TURN_L_PIN = A2;		//A2 Pin Pulsador Izquierdo
const byte PULSADOR_LIGHT_PIN = A3;			//A3 Pin Luz
const byte PULSADOR_BRAKE_PIN = A4;			// Pulsadores freno
//const byte PULSADOR_AUX_PIN = A5;			// Pulasor Auxiliar

//--------------------------------- Luces --------------------------------------------------
const byte BRAKE_OUT_PIN = 11;				// luz de freno
const byte TURN_L_OUT_PIN = 10;				// señalero izquierdo
const byte TURN_R_OUT_PIN = 9;				// señalero derecho 
const byte LIGHT_OUT_PIN = 6;				// relé de luz corta
const byte BREAM_OUT_PIN = 5;				// relé de luz alta

//--------------------------------------- Otros --------------------------------------------
const byte IGNITION_OUT_PIN = 3;			// Arranque
//const byte bocina = 16;					// Bocina

//------------------------------------- AceButton ----------------------------------------

ButtonConfig turnConfig;

AceButton pulsadorStart(PULSADOR_START_PIN, HIGH);
AceButton pulsadorLight(PULSADOR_LIGHT_PIN, HIGH);
AceButton pulsadorBrake(PULSADOR_BRAKE_PIN, HIGH);
AceButton pulsadorTurnR(&turnConfig, PULSADOR_TURN_R_PIN, HIGH);
AceButton pulsadorTurnL(&turnConfig, PULSADOR_TURN_L_PIN, HIGH);



//------------------------------------- Variables ------------------------------------------


//==========================================================================================
//---------------------------------------- Funciones ---------------------------------------
//==========================================================================================
void handleTurnEvent(AceButton* button, uint8_t eventType, uint8_t /* buttonState */){
	switch (eventType){
	case AceButton::kEventClicked:
		digitalWrite(BRAKE_OUT_PIN, HIGH);
		break;
	
	case AceButton::kEventDoubleClicked:
		digitalWrite(LIGHT_OUT_PIN, HIGH);
		break;
	case AceButton::kEventLongPressed:
		digitalWrite(TURN_R_OUT_PIN, HIGH);
		break;
	}
}

//==========================================================================================
//------------------------------------- Setup ----------------------------------------------
//==========================================================================================

void setup(){

	turnConfig.setEventHandler(handleTurnEvent);
	turnConfig.setFeature(ButtonConfig::kFeatureDoubleClick);
	turnConfig.setFeature(ButtonConfig::kFeatureLongPress);
	turnConfig.setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);
	turnConfig.setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);


//------------------------------------- Salidas -----------------------
	pinMode(BRAKE_OUT_PIN, OUTPUT);			// Out Brake
	pinMode(TURN_L_OUT_PIN, OUTPUT);		// Out Turn Left
	pinMode(TURN_R_OUT_PIN, OUTPUT);		// Out Turn Right
	pinMode(LIGHT_OUT_PIN, OUTPUT);			// Out Light
	pinMode(BREAM_OUT_PIN, OUTPUT);			// Out Light Bream
	pinMode(IGNITION_OUT_PIN, OUTPUT);		// Out Ignition 

//------------------------------------- Entradas ---------------------
	pinMode(PULSADOR_START_PIN, INPUT);		// Pulsador Start
	pinMode(PULSADOR_TURN_R_PIN, INPUT);	// Pulsador Turn Right
	pinMode(PULSADOR_TURN_L_PIN, INPUT);	// Pulsador Turn Left
	pinMode(PULSADOR_LIGHT_PIN, INPUT);		// Pulsador Light
	pinMode(PULSADOR_BRAKE_PIN, INPUT);		// Pulsador Brake
}

//==========================================================================================
//-------------------------------------- Loop ----------------------------------------------
//==========================================================================================

void loop(){
	pulsadorLight.check();
	pulsadorTurnR.check();
	pulsadorTurnL.check();
	pulsadorBrake.check();
}

