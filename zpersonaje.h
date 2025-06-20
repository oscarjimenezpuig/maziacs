/*
============================================================
  Fichero: zpersonaje.h
  Creado: 06-06-2025
  Ultima Modificacion: divendres, 20 de juny de 2025, 05:15:54
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zdraw.h"

void personaje_init();
//cada vez que iniciamos el personaje, subimos el nivel en 1

u1 personaje_act();
//actuacion del personaje

void personaje_marc();
//visualiza todos los marcadores

u1 personaje_mens(char* mensaje,Attribute attribute,u1 ratio);
//se visualiza un mensaje en la parte central de la pantalla

