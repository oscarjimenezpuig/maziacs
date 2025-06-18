/*
============================================================
  Fichero: zdraw.h
  Creado: 04-06-2025
  Ultima Modificacion: dilluns, 16 de juny de 2025, 09:09:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zobjeto.h"

void pared_draw(Punto esi,Vector normal);
//dibuja una pared desde su extremo superior izquierdo

void pared_erase(Punto esi,Vector normal);
//borra el rectangulo maximo que contiene la pared

void posicion_draw(u1 bloc,u1 direccion,u1 salidas);
//dibuja una posicion, bloc indica la profundidad siendo 0 la que esta en primer plano
//la vista nos dira que salidas vemos

void nubes(u1 bloc);
//dibuja una serie de puntos aleatoriamente en cada habitacion dibujada

u1 total_draw(u2 x,u2 y,u1 direccion);
//dada una posicion del mundo, se dibuja todo lo que se vea
