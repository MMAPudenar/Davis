#include <Arduino.h>
#include "DAVIS6410.hpp"

// ------------ DEFINICION DE CONSTANTES ------------
// Definicion de pines
const uint8_t vvPin = 23; // Negro
const uint8_t dvPin = 34; // Verde
// Definicion de tiempos
const uint16_t TMedicion = 1000;

// ------------ DEFINICION DE VARIABLES ------------
unsigned long tActual = 0; 		// Tiempo actual de millis()
unsigned long tPrevio = 0;

uint8_t sampleTime = 1;
uint16_t dvOffset = 0;

// ------------ DEFINICION DE INTERRUPCIONES ------------
volatile int count = 0;
volatile int freq;
hw_timer_t * timer = NULL;
portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Función de interrupción
void IRAM_ATTR isr() {
  portENTER_CRITICAL(&synch);
  count++; // Cada vez que se llama a la función el contador se incrementa
  portEXIT_CRITICAL(&synch);
}

// Función de interrupción de timer
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  freq = count; // Se almacena el valor de la frecuencia
  count = 0; // Se reinicia el contador.
  portEXIT_CRITICAL_ISR(&timerMux);
}

// ------------ SETUP ------------
void setup() {
	// DEBUGGING
	Serial.begin(115200);
  
  // PINES  
	pinMode(vvPin, INPUT);
	pinMode(dvPin, INPUT);

  // SETUP DE INTERRUPCIONES
  attachInterrupt(vvPin, isr, FALLING);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

// ------------ LOOP ------------
void loop() {
  double vel;
  uint16_t dir;

  tActual = millis(); 

  if (tActual > tPrevio + TMedicion) { 
    vel = getSpeed(freq, sampleTime);    
    dir = getDirection(dvPin, dvOffset);

    Serial.print("Vel. [m/s]\tDir.[°]\n");
		Serial.print(vel);
		Serial.print("\t");
		Serial.print(dir);
		Serial.print("\n");
    calcularDireccion(dir);

    tPrevio = tActual;
  }

}

