/*
============================================================
  Fichero: zconstantes.h
  Creado: 04-06-2025
  Ultima Modificacion: divendres, 6 de juny de 2025, 11:20:15
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef ZCONSTANTES_H
#define ZCONSTANTES_H

#include "inout.h"
#include "geometry.h"
#include "maze.h"

#define SCRW 500 //dimension pantalla w
#define SCRH 500 //dimension pantalla h
#define CINK (Color){0,0,0} //color ink
#define CPAPER (Color){255,255,255} //color paper
#define PARDIM SCRW //definicion de la longitud de pared
#define PFUGA {SCRW/2,(PARDIM/2),-PARDIM}
#define VIS 20 //numero maximo de posiciones que se veran

#define PAIR(A) ((A)%2==0)

typedef double Punto[3];
typedef double Vector[3];

typedef struct {
	u2 x,y;
	u1 nivel;
	u1 face;
	u1 vivo;
} Personaje;

typedef struct {
	u1 w,h;
	u1* sprite;
} Grafico;

extern Personaje personaje;


#endif //ZCONSTANTES_H


