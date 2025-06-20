/*
============================================================
  Fichero: zgrafico.h
  Creado: 06-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 19:59:51
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zmundo.h"

Grafico grafico_new(u1 w,u1 h,char white,char* line[]);
//creacion de un nuevo grafico, white es el caracter de apagado

void grafico_del(Grafico* grafico);
//se libera el espacio del grafico

void grafico_on(Grafico g,u2 y,u2 z);
//conecta el grafico en un bloque a una altura determinada (la altura corresponde al
//extremo superior izquierdo del grafico)
