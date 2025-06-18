/*
============================================================
  Fichero: zobjeto.h
  Creado: 06-06-2025
  Ultima Modificacion: dimarts, 17 de juny de 2025, 12:58:26
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zgrafico.h"

u1 objeto_new(Objeto objeto);
//define un nuevo objeto (si un objeto ocupa una identidad ya ocupada no lo incluye)

void objeto_del(u1 id);
//quita el objeto con identidad dada

u1 visualizar_objetos(u1 x,u1 y,u1 direccion);
//se visualizan los objetos por parte del personaje, devuelve 1 si hay alguno

