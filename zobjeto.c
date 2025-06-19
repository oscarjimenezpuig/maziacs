/*
============================================================
  Fichero: zobjeto.c
  Creado: 08-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 05:04:48
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zobjeto.h"

Objeto objetos[OBJETOS];

static u1 visto[OBJETOS];
static u1 vistos=0;

u1 objeto_new(Objeto o) {
	static u1 def=0;
	if(!def) {
		Objeto* ptr=objetos;
		while(ptr!=objetos+OBJETOS) {
			ptr->tipo=0;
			ptr++;
		}
		def=1;
	}
	Objeto* ptr=objetos+o.id;
	if(ptr->tipo==0 && ptr->id!=0) {
		*ptr=o;
		ptr->activo=1;
		return 1;
	}
	return 0;
}

void objeto_del(u1 id) {
	objetos[id].tipo=0;
	objetos[id].activo=0;
}

Objeto* objeto_get(u1 id) {
	if(objetos[id].tipo!=0) {
		return objetos+id;
	}
	return NULL;
}

static u1 examinar_desplazar(u1 dir,u2* vx,u2* vy) {
	//rellena la matriz de vistos con los objetos vistos
	if(mundo_get(*vx,*vy)) {
		Objeto* ptr=objetos;
		while(ptr!=objetos+OBJETOS) {
			if(ptr->activo && ptr->x==*vx && ptr->y==*vy) {
				visto[vistos++]=ptr->id;
			}
			ptr++;
		}
		s1 dx,dy;
		dx=dy=0;
		switch(dir) {
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
		*vx+=dx;
		*vy+=dy;
		return 1;
	}
	return 0;
}

static u1 dirn(u1 dir) {
	u1 val=0;
	while((dir=dir>>1)) val++;
	return val;
}

static void visualizar(u1 x,u1 y,u1 dir) {
	const u1 MIR[4][4]={{3,4,2,1},{2,3,1,4},{4,1,3,2},{1,2,4,3}};
	while(vistos) {
		u1 no=visto[--vistos];
		Objeto* o=objetos+no;
		u4 dm=DSM(x,y,o->x,o->y);
		u1 gr=MIR[dirn(dir)][dirn(o->face)];
		grafico_on(*(o->grafico[gr-1]),o->altura,dm);	
	}
}

u1 visualizar_objetos(u1 x,u1 y,u1 dir) {
	vistos=0;
	u2 vx=x;
	u2 vy=y;
	while(examinar_desplazar(dir,&vx,&vy));
	if(vistos) {
		visualizar(x,y,dir);
		return 1;
	}
	return 0;
}

			

	
