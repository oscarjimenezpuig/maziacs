/*
============================================================
  Fichero: zpersonaje.c
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 8 de juny de 2025, 06:19:26
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpersonaje.h"

Personaje personaje;

void personaje_init() {
	static u1 nivel=0;
	personaje.x=personaje.y=1;
	personaje.nivel=++nivel;
	personaje.face=SOUTH;
}

static u1 personaje_gira(s1 direccion) {
	u1 const DIRS[]={NORTH,EAST,SOUTH,WEST};
	u1 dir=(direccion>0)?1:3;
	u1 k=0;
	for(;k<4;k++) if(DIRS[k]==personaje.face) break;
	k=(k+dir)%4;
	printf("direccion=%i\n",k);//dbg
	personaje.face=DIRS[k];
	printf("face=%i\n",DIRS[k]);//dbg
	return 1;
}

static u1 personaje_mueve(s1 direccion) {
	s1 dx,dy;
	switch(personaje.face) {
		case NORTH:
			dy=-1;
			break;
		case SOUTH:
			dy=1;
			break;
		case EAST:
			dx=1;
			break;
		case WEST:
			dx=-1;
			break;
	}
	u2 fx=personaje.x+(dx)*direccion;
	u2 fy=personaje.y+(dy)*direccion;
	if(mundo_get(fx,fy)) {
		personaje.x=fx;
		personaje.y=fy;
		return 1;
	}
	return 0;
}

u1 personaje_act() {
	u1 r=0;
	if(kison(LEFT)) r|=personaje_gira(-1);
	if(kison(RIGHT)) r|=personaje_gira(1);
	if(kison(UP)) r|=personaje_mueve(1);
	if(kison(DOWN)) r|=personaje_mueve(-1);
	return r;
}


	
