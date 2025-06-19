/*
============================================================
  Fichero: zitems.h
  Creado: 18-06-2025
  Ultima Modificacion: dimecres, 18 de juny de 2025, 20:34:46
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpersonaje.h"

void tesoro_define(u1 nivel);
//crea el tesoro y lo coloca en algun lugar del laberinto

void espadas_define(u1 nivel);
//crea las espadas en funcion del nivel y las coloca en el laberinto

void items_free();
//libera todo los graficos de los objetos cuando acaba la partida
