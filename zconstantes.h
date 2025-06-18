/*
============================================================
  Fichero: zconstantes.h
  Creado: 04-06-2025
  Ultima Modificacion: dimarts, 17 de juny de 2025, 08:43:06
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
#define OBJETOS 256 //maximo de objetos a definir

//vision de grafico
#define FRONTAL 1
#define DERECHA 2
#define TRASERA 3
#define IZQUIERDA 4

#define PAIR(A) ((A)%2==0)
#define ABS(A) (((A)>0)?(A):-(A))
#define DSM(X,Y,Z,T) (ABS((X)-(Z))+ABS((Y)-(T)))

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

typedef struct {
	u1 id;
	u1 tipo;
	u2 x,y; //posicion del mundo
	u2 altura; //altura a la que se vera el objeto
	Grafico* grafico[4];
	u1 activo;
	u1 face; //hacia donde esta enfocada la cara frontal
} Objeto;

extern Personaje personaje;
extern Objeto objetos[OBJETOS];


#endif //ZCONSTANTES_H


