/*
============================================================
  Fichero: zenemigos.h
  Creado: 21-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 06:24:27
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zitems.h"

#include <time.h>

void maziac_define(u1 nivel);
//define los maziac que hay en un nivel

u1 maziac_act();
//actuacion de todos los maziac

u1 maziac_visto();
//dice si el personaje ve algun maziac

void enemigos_free();
//libera todo el espacio de los enemigos
