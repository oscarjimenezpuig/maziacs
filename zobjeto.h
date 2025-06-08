/*
============================================================
  Fichero: zobjeto.h
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 8 de juny de 2025, 07:45:23
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zgrafico.h"

struct Visto {
	Objeto* objeto;
	u1 vista;
	u1 bloc;
	struct Visto* next;
};

u1 objeto_new(Objeto objeto);
//define un nuevo objeto (si un objeto ocupa una identidad ya ocupada no lo incluye)

void objeto_del(u1 id);
//quita el objeto con identidad dada

u1 objeto_visto(Objeto o,u1* bloc);
//dice si un objeto es visto por el personaje en que bloque, el valor obtenido es la
//vision (frontal, lateral o trasera) del objeto, sino 0

u1 visualizar_objetos();
//se visualizan los objetos por parte del personaje, devuelve 1 si hay alguno

