/*
============================================================
  Fichero: zobjeto.h
  Creado: 06-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 05:05:11
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zgrafico.h"

u1 objeto_new(Objeto objeto);
//define un nuevo objeto (si un objeto ocupa una identidad ya ocupada no lo incluye)
//no se pueden definir objetos con identidad 0

void objeto_del(u1 id);
//quita el objeto con identidad dada

Objeto* objeto_get(u1 id);
//obtiene el objeto con identidad dada

u1 visualizar_objetos(u1 x,u1 y,u1 direccion);
//se visualizan los objetos por parte del personaje, devuelve 1 si hay alguno

