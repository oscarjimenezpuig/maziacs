/*
============================================================
  Fichero: zpersonaje.h
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 05:52:37
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

u1 personaje_men_new(char* mensaje);
//se introduce un nuevo mensaje

u1 personaje_men_show();
//se saca por pantalla un mensaje

