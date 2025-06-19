/*
============================================================
  Fichero: zgrafico.h
  Creado: 06-06-2025
  Ultima Modificacion: dimecres, 18 de juny de 2025, 20:27:21
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zmundo.h"

Grafico grafico_new(u1 w,u1 h,u1* sprites);
//creacion de un nuevo grafico

void grafico_del(Grafico* grafico);
//se libera el espacio del grafico

void grafico_on(Grafico g,u2 altura,u1 bloc);
//conecta el grafico en un bloque a una altura determinada (la altura corresponde al
//extremo superior izquierdo del grafico)

void grafico_off(Grafico g,u2 altura,u1 bloc);
//desconecta el grafico (mismas condiciones que la conexion)

u1 sprite_data_new(u1 sprite,char white,char* data[]);
//creacion de un sprite a partir de cadenas de caracteres (el blanco sera no conectado)

