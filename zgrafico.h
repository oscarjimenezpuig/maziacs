/*
============================================================
  Fichero: zgrafico.h
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 8 de juny de 2025, 06:49:55
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zdraw.h"

Grafico grafico_new(u1 w,u1 h,u1* sprites);
//creacion de un nuevo grafico

void grafico_del(Grafico* grafico);
//se libera el espacio del grafico

void grafico_on(Grafico g,u2 altura,u1 bloc);
//conecta el grafico en un bloque a una altura determinada (la altura corresponde al
//extremo superior izquierdo del grafico)

void grafico_off(Grafico g,u2 altura,u1 bloc);
//desconecta el grafico (mismas condiciones que la conexion)


