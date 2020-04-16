//==========================================================================================
//----------------------------------- MOTO -------------------------------------------------
//==========================================================================================
#include <Arduino.h>
#include <ButtonKing.h>

//-------------------------------- Pulsadores-----------------------------------------------
ButtonKing pulsadorArranque(A0, true);	//A0
ButtonKing pulsadorDerecho(A1,true);	//A1
ButtonKing pulsadorIzquierdo(A2,true);	//A2
ButtonKing pulsadorLUZ(A3,true);		//A3

const byte pulsFreno = A4;				// Pulsadores frenos
const byte pulsAux = A5;				// Pulasor Auxiliar

//--------------------------------- Luces --------------------------------------------------
const byte led_freno = 11;				// luz de freno
const byte led_senI = 10;				// señalero izquierdo
const byte led_senD = 9;				// señalero derecho 
const byte Luz = 6;						// relé de luz corta
const byte LuzALTA = 5;					// relé de luz alta

//--------------------------------------- Otros --------------------------------------------
const byte arranque = 3;				// Arranque
//const byte bocina = 16;				// Bocina

//------------------------------------- Variables ------------------------------------------


//funcion Destellador
boolean senalDestellador = LOW;
long tP1 = 0;
long tP2 = 0;
byte sena = 0;

//Funcion Señaleros
byte tiempoParpadeo = 200;

//Funcion Luces
boolean estadosLuces = LOW;
byte intencidadLedFreno = 70;
boolean estadoLuzAlta = LOW;

//funcion Freno
boolean freno_act = false;

//==========================================================================================
//---------------------------------------- Funciones ---------------------------------------
//==========================================================================================
boolean Destellador(byte TP){								// Funcion Destellados
	tP2 = millis();
	if(tP2 - tP1 > TP){
		tP1 = tP2;
		(senalDestellador == LOW) ? senalDestellador = HIGH : senalDestellador = LOW;
	}  
	return senalDestellador;
}

void Senaleros(){											// Funcion Señaleros
	if(sena == 1){											// Señalero derecho
	    digitalWrite(led_senD, Destellador(tiempoParpadeo));
	    digitalWrite(led_senI, LOW); 
	}
	if(sena == 2){											// Señalero Izquierdo
	    digitalWrite(led_senI, Destellador(tiempoParpadeo));
	    digitalWrite(led_senD, LOW); 
	}
	if(sena == 3){ 											// Baliza 
	    digitalWrite(led_senD, Destellador(tiempoParpadeo));
	    digitalWrite(led_senI, Destellador(tiempoParpadeo));
	}
	else
	{
		digitalWrite(led_senD, LOW);
		digitalWrite(led_senI, LOW);
	}
}

void Luces(){												// Funcion Luces
	if(estadosLuces == HIGH){
		digitalWrite(Luz, HIGH);
		analogWrite(led_freno, intencidadLedFreno);
	}
	else{
		digitalWrite(Luz, LOW);
		analogWrite(led_freno, LOW);
		digitalWrite(LuzALTA, LOW);
	}
	(estadoLuzAlta) ? digitalWrite(LuzALTA, HIGH) : digitalWrite(LuzALTA, LOW);
}

void Freno(){												// Funcion Freno
	if(freno_act){
		for(int i=0; i<255; i++){
			analogWrite(led_freno, i);
		}
	}
}

// ----------------------------- Boton Arranque -------------------------------------
void ArranqueStart(){
	digitalWrite(arranque, HIGH);
}
void ArranqueStop(){
	digitalWrite(arranque, LOW);
}					
//-------------------------------- Boton Luces --------------------------------------
void EnciendeLuces(){
	estadosLuces == LOW ? estadosLuces = HIGH : estadosLuces = LOW;
}
void EncenderLuzAlta(){
	estadoLuzAlta == LOW ? estadoLuzAlta = HIGH : estadoLuzAlta = LOW;
}
void DestellarLuzAlta(){
	estadoLuzAlta = LOW;
	digitalWrite(LuzALTA, Destellador(50));
}

//------------------------------ Boton Señalero -------------------------------------
void SenaleroDerechoEncendido(){
	sena==1 ? sena=0 : sena=1;	
}
void SenaleroIzquieroEncendido(){
	sena==2 ? sena=0 : sena=2;
}
void SenaleroApagado(){
	sena = 0;
}
void Baliza(){
	sena = 3;
}

//==========================================================================================
//------------------------------------- Setup ----------------------------------------------
//==========================================================================================

void setup(){

//------------------------------------- Salidas -----------------------
	pinMode(LuzALTA, OUTPUT);
	pinMode(led_freno, OUTPUT);
	pinMode(led_senI, OUTPUT);
	pinMode(led_senD, OUTPUT);
	pinMode(Luz, OUTPUT);
	pinMode(arranque, OUTPUT);

//------------------------------------- Entradas ---------------------
	pinMode(pulsFreno, INPUT);
	
	//------------------- Boton Arranque
	pulsadorArranque.setShortDoubleStart(ArranqueStart);
	pulsadorArranque.setLongDoubleStop(ArranqueStop);

	//------------------- Boton Luces
	pulsadorLUZ.setDoubleClick(EnciendeLuces);
	pulsadorLUZ.setClick(EncenderLuzAlta);
	pulsadorLUZ.setLongClickStart(DestellarLuzAlta);

	//------------------- Boton Derecho
	pulsadorDerecho.setClick(SenaleroDerechoEncendido);
	pulsadorDerecho.setDoubleClick(SenaleroApagado);
	pulsadorDerecho.setLongClickStart(Baliza);

	//------------------- Boton Izquierdo
	pulsadorIzquierdo.setClick(SenaleroIzquieroEncendido);
	pulsadorIzquierdo.setDoubleClick(SenaleroApagado);	
	pulsadorIzquierdo.setLongClickStart(Baliza);

	//------------------- Boton Freno


}

//==========================================================================================
//-------------------------------------- Loop ----------------------------------------------
//==========================================================================================

void loop(){
	(!digitalRead(pulsFreno)) ? freno_act = true : freno_act = false;
	pulsadorIzquierdo.isClick();
	pulsadorDerecho.isClick();
	pulsadorLUZ.isClick();
	pulsadorArranque.isClick();
	Luces();
	Freno();
	Senaleros();

}

