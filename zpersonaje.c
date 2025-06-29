/*
============================================================
  Fichero: zpersonaje.c
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 07:09:38
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpersonaje.h"

Personaje personaje;

static u1 findfacefree() {
	u1 const DIRS[]={NORTH,EAST,SOUTH,WEST};
	u1 sal=mundo_sal(personaje.x,personaje.y);
	for(u1 k=0;k<4;k++) {
		if(sal & DIRS[k]) return DIRS[k];
	}
	return 0;
}

void personaje_init() {
	personaje.x=personaje.y=1;
	personaje.objeto=0;
	personaje.face=findfacefree();
	personaje.activo=1;
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
			String str;
			if(poseido) {
				poseido->x=personaje.x;
				poseido->y=personaje.y;
				sprintf(str,"YOU DROP %s...",poseido->nombre);
				personaje_men_new(str);
			}
			sprintf(str,"YOU PICK %s...",o[0]->nombre);
			personaje_men_new(str);
			if((o[0]->tipo & 4)==0) {
				personaje_men_new("RUN TO HOME!");
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
	y=SCRH-8*MRCRAT;
	x=1;
	char str[20];
	sprintf(str,"LEVEL %i",nivel);
	ston(&x,&y,1,0,MRCRAT,NAT,str);
	//encarado
	char* const DIRF[]={"NORTH","SOUTH","EAST","WEST"};
	sprintf(str,"%s",DIRF[cara(personaje.face)]);
	u2 l=len(str);
	x=(SCRW-8*MRCRAT*l)/2;
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

static Mensajes mensajes={0,0};
static u1 showing=0;
static int men_pos=0;
static int men_end=0;
static Mensaje actual;
static u1 is_quited=0;

static void men_copy(Mensaje d,Mensaje o) {
	char* ptrd=d;
	char* ptro=o;
	while(*ptro!='\0'&& ptro-o<MENSIZ) {
		*ptrd++=*ptro++;
	}
	*ptrd='\0';
}

static u1 mens_ins(Mensaje n) {
	if(mensajes.size<MENSAJES) {
		men_copy(mensajes.mensaje[mensajes.size++],n);
		return 1;
	}
	return 0;
}

static void men_scr_clean() {
	for(u2 i=0;i<SCRW;i++) {
		for(u2 j=0;j<8*MRCRAT;j++) {
			off(i,j);
		}
	}
}

static u1 men_show() {
	u1 ret=0;
	const u2 ADV=8*MRCRAT;
	if(showing) {
		u2 x=men_pos;
		u2 y=1;
		men_scr_clean();
		ston(&x,&y,1,0,MRCRAT,NAT,actual);
		if(men_pos<=men_end) showing=0;
		else men_pos-=ADV;
		if(quit) {
			is_quited=quit;
			quit=0;
		}
		fls();
		ret=1;
	} else if(mensajes.read<mensajes.size) {
		men_copy(actual,mensajes.mensaje[mensajes.read++]);
		showing=1;
		men_pos=SCRW;
		men_end=-len(actual)*8*MRCRAT;
		if(quit) {
			is_quited=quit;
			quit=0;
		}
	} else {
		mensajes.size=mensajes.read=0;
		if(is_quited) quit=is_quited;
	}
	return ret;
}

u1 personaje_men_new(char* m) {
	return mens_ins(m);
}

u1 personaje_men_show() {
	return men_show();
}


	
