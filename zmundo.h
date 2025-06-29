/*
============================================================
  Fichero: zmundo.h
  Creado: 04-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 06:30:49
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
