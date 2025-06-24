/*
============================================================
  Fichero: zmundo.h
  Creado: 04-06-2025
  Ultima Modificacion: diumenge, 22 de juny de 2025, 14:35:04
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpausa.h"

void mundo_new(u1 nivel);
//crea mundo

void mundo_del();
//libera mundo

u1 mundo_get(u2 x,u2 y);
//consigue una posicion del mundo y da si hay pared o no

u1 mundo_sal(u2 x,u2 y);
//da las salidas de un mundo

u2 mundo_dim();
//da la dimension del mundo

void mundo_rand(u2* x,u2* y);
//da una posicion random del mundo (vacia)

void mundo_prt(u2 x,u2 y);
//imprime el mundo actual


