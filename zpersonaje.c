/*
============================================================
  Fichero: zpersonaje.c
  Creado: 06-06-2025
  Ultima Modificacion: divendres, 20 de juny de 2025, 05:15:54
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
	personaje.face=DIRS[k];
	return 1;
}

static u1 personaje_mueve(s1 direccion) {
	s1 dx,dy;
	dx=dy=0;
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

static u1 concog(Objeto* o) {
	return (o->activo && (o->tipo & COGIBLE) && o->x==personaje.x && o->y==personaje.y);
}

static u1 personaje_coge() {
	Objeto* o[OBJETOS];
	u1 os=objeto_find(o,concog);
	if(os) {
		Objeto* poseido=objeto_get(personaje.objeto);
		if(!poseido || poseido->tipo!=o[0]->tipo) {
			o[0]->x=o[0]->y=-1;
			personaje.objeto=o[0]->id;
			if(poseido) {
				poseido->x=personaje.x;
				poseido->y=personaje.y;
			}
		return 1;
		}
	}
	return 0;
}	

u1 personaje_act() {
	u1 r=0;
	if(kison(LEFT)) r|=personaje_gira(-1);
	if(kison(RIGHT)) r|=personaje_gira(1);
	if(kison(UP)) r|=personaje_mueve(1);
	if(kison(DOWN)) r|=personaje_mueve(-1);
	if(kison(SPACE)) r|=personaje_coge();
	return r;
}

static u1 cara(u1 dir) {
	switch(dir) {
		case NORTH:
			return 0;
		case SOUTH:
			return 1;
		case EAST:
			return 2;
		default:
			return 3;
	}
}

static u2 len(char* str) {
	char* ptr=str;
	while(*ptr!='\0') ptr++;
	return ptr-str;
}

void personaje_marc() {
	//nivel
	u2 x,y;
	x=y=1;
	char str[20];
	sprintf(str,"LEVEL %i",nivel);
	ston(&x,&y,1,0,MRCRAT,NAT,str);
	//encarado
	char* const DIRF[]={"NORTH","SOUTH","EAST","WEST"};
	sprintf(str,"%s",DIRF[cara(personaje.face)]);
	x=1;
	y=SCRH-8*MRCRAT;
	ston(&x,&y,1,0,MRCRAT,NAT,str);
	//poseido
	if(personaje.objeto) {
		Objeto* op=objeto_get(personaje.objeto);
		sprintf(str,"%s",op->nombre);
		u2 l=len(str);
		x=SCRW-(l*8*MRCRAT+1);
		ston(&x,&y,1,0,MRCRAT,NAT,str);
	}
}

u1 personaje_mens(char* men,Attribute a,u1 r) {
}


		


	
