/*
============================================================
  Fichero: geometry.h
  Creado: 29-05-2025
  Ultima Modificacion: dimecres, 4 de juny de 2025, 10:15:38
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "screen.h"

void ron(u2 xi,u2 yi,u2 xf,u2 yf);
//conexion de una recta con origen xi,yi y final xf,yf

void roff(u2 xi,u2 yi,u2 xf,u2 yf);
//desconexion de una recta con origen xi,yi y final xf,yf

void pon(u1 edges,u2* edge);
//conexion de un poligono a partir del numero de vertices y las coordenadas.
//el poligon es cerrado

void poff(u1 edges,u2* edge);
//desconexion de un poligono


