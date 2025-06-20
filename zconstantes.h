/*
============================================================
  Fichero: zconstantes.h
  Creado: 04-06-2025
  Ultima Modificacion: divendres, 20 de juny de 2025, 05:33:30
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
#define FACNIV 3 //este factor multiplicado por el nivel da la dimension lateral del laberinto
#define PIXDIM 8 //dimension del pixel en un primer plano
#define MRCRAT 2 //ratio de aumento de los marcadores

//tipos
#define COGIBLE 1
#define ARMA 2

//identificadores
#define TESORO 1
#define ESPADA_MIN 2
#define ESPADA_MAX 12

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
	u1 w,h;
	u1* bit;
} Grafico;

typedef struct {
	u1 id;
	u1 tipo;
	char* nombre;
	u2 x,y; //posicion del mundo
	u2 altura; //altura a la que se vera el objeto
	Grafico* grafico[4];
	u1 activo;
	u1 face; //hacia donde esta enfocada la cara frontal
} Objeto;

typedef struct {
	u2 x,y;
	u1 nivel;
	u1 face;
	u1 vivo;
	u1 objeto;
} Personaje;

typedef u1 (*Condicion)(Objeto*);

extern Personaje personaje;
extern Objeto objetos[OBJETOS];

extern u1 nivel;


#endif //ZCONSTANTES_H


