/*
============================================================
  Fichero: zpausa.c
  Creado: 22-06-2025
  Ultima Modificacion: diumenge, 22 de juny de 2025, 14:34:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpausa.h"

void pausa(double time) {
	clock_t fin=clock()+CLOCKS_PER_SEC*time;
	while(clock()<fin);
}


