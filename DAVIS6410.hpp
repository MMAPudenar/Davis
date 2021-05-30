/**
 * \file DAVIS6410.hpp
 * \brief Archivo de cabecera para el anemómetro DAVIS 6410
 * \author Joseph Santiago Portilla Martínez - Karen Stefania Mirama Eraso
 */ 
#ifndef DAVIS6410_HPP
#define DAVIS6410_HPP

//---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
//---------------------------------------------------------
/**
 * \brief Medición de velocidad del viento en m/s
 * \param freq: Frecuencia de revolución las copas
 * \param sampleTime: Tiempo de muestreo de la interrupción
 * \return Velocidad del viento en m/s
*/
double getSpeed(volatile int freq, uint8_t sampleTime);

/**
 * \brief Medición de dirección del viento en grados
 * \param dvPin: Pin de conexión del piranómetro
 * \param dvOffset: Offset en el montaje del anemómetro
 * \return Dirección del viento en grados
*/
uint16_t getDirection (uint8_t dvPin, uint16_t dvOffset);

/**
 * \brief Convertir de grados a dirección del viento 
 * \param dvGrados: Pin de conexión del piranómetro
*/
void calcularDireccion(float dvGrados);

#endif