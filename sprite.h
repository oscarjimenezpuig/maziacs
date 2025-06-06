/*
============================================================
  Fichero: sprite.h
  Creado: 16-05-2025
  Ultima Modificacion: dilluns, 2 de juny de 2025, 09:37:15
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "screen.h"

//un sprite es un conjunto de 8x8 puntos
//Tenemos espacio para 256 sprites, se contiene tambien mayusculas, signos de puntuacion y numeros
//segun su codigo ASCII

typedef enum {NAT=0,FLH=1,FLV=2,INV=4} Attribute;

u1 snew(u1 id,u1 a,u1 b,u1 c,u1 d,u1 e,u1 f,u1 g,u1 h);
//definicion de un sprite

void son(u1 id,u2 x,u2 y,u1 ratio,Attribute a);
//colocacion en modo on en pantalla de un sprite

void soff(u1 id,u2 x,u2 y,u1 ratio,Attribute a);
//colocacion en modo off en pantalla de un sprite


