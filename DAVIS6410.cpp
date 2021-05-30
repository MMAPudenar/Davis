/**
 * \file DAVIS6410.cpp
 * \brief Archivo de implementación para el anemómetro DAVIS 6410
 * \author Joseph Santiago Portilla Martínez - Karen Stefania Mirama Eraso
 */ 
#include <Arduino.h>
#include "DAVIS6410.hpp"

//---------------------------------------------------------
// IMPLEMENTACIÓN DE FUNCIONES
//---------------------------------------------------------|
/**
 * \brief Medición de velocidad del viento en m/s
 * \param freq: Frecuencia de revolución las copas
 * \param sampleTime: Tiempo de muestreo de la interrupción
 * \return Velocidad del viento en m/s
*/
double getSpeed(volatile int freq, uint8_t sampleTime) {
  float vv;

  vv = freq * (2.25 / sampleTime); // número de pulsos * (2.25 / Periodo de muestreo) [mph]
  vv = vv * 0.44704; // [m/s]

  return vv;
}

/**
 * \brief Medición de dirección del viento en grados
 * \param dvPin: Pin de conexión del piranómetro
 * \param dvOffset: Offset en el montaje del anemómetro
 * \return Dirección del viento en grados
*/
uint16_t getDirection (uint8_t dvPin, uint16_t dvOffset) {
  uint16_t veletaValor, dv;

  veletaValor = analogRead(dvPin);

  dv = map(veletaValor, 0, 4095, 0, 360);
  dv = dv + dvOffset;

  if(dv > 360)
      dv = dv - 360;  
  if(dv < 0)
      dv = dv + 360; 
  
  return dv;
}

/**
 * \brief Convertir de grados a dirección del viento 
 * \param dvGrados: Dirección del viento en grados.
*/
void calcularDireccion(float dvGrados) {
    if(dvGrados < 22)  
      Serial.println("N");  
    else if (dvGrados < 67)  
      Serial.println("NE");  
    else if (dvGrados < 112)  
      Serial.println("E");  
    else if (dvGrados < 157)  
      Serial.println("SE");  
    else if (dvGrados < 212)  
      Serial.println("S");  
    else if (dvGrados < 247)  
      Serial.println("SO");  
    else if (dvGrados < 292)  
      Serial.println("O");  
    else if (dvGrados < 337)  
      Serial.println("NO");  
    else  
      Serial.println("N");  
}