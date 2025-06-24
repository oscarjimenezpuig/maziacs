/*
============================================================
  Fichero: zitems.c
  Creado: 18-06-2025
  Ultima Modificacion: diumenge, 22 de juny de 2025, 06:32:57
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zitems.h"

static Grafico gpuerta;
static Grafico gtesoro[3];
static Grafico gespada;

void puerta_define() {
	static u1 gpudef=0;
	if(!gpudef) {
		char* dpuet[]={
			"0000110000",
			"0000110000",
			"0011111100",
			"0011111100",
			"1111111111",
			"1111111111"
						};
		gpuerta=grafico_new(10,6,1,'0',dpuet);
		gpudef=1;
	}
	Objeto opdef={PUERTA,SALIDA,"DOOR",1,1,0,{&gpuerta,&gpuerta,&gpuerta,&gpuerta},1,NORTH};
	objeto_new(opdef);
}

struct Nodo {
	u2 x,y;
	u2 paso;
	u1 salidas;
	struct Nodo* dir[4];
};

static void nododel(struct Nodo* nodo) {
	if(nodo) {
		for(u1 k=0;k<4;k++) {
			nododel(nodo->dir[k]);
		}
		free(nodo);
	}
}

static struct Nodo* nuevonodo(u2 px,u2 py,u2 pp,u2 direccion) {
	struct Nodo* n=malloc(sizeof(struct Nodo));
	if(n) {
		if(direccion==0) {
			n->x=personaje.x;
			n->y=personaje.y;
			n->paso=0;
			n->salidas=mundo_sal(n->x,n->y);
		} else {
			s1 dx,dy;
			dx=dy=0;
			switch(direccion) {
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
			}
			n->x=px+dx;
			n->y=py+dy;
			n->paso=pp+1;
			u1 contra=8/direccion;
			n->salidas=mundo_sal(n->x,n->y) & (~contra);
		}
		for(u1 k=0;k<4;k++) n->dir[k]=NULL;
	}
	return n;
}
			
static struct Nodo* nodo_max=NULL;

static void recursivo_tesoro(struct Nodo* actual) {
	if(nodo_max==NULL || nodo_max->paso<actual->paso) nodo_max=actual;
	u1 dir=NORTH;
	u1 nsal=0;
	for(;dir<=SOUTH;dir=dir<<1) {
		if(dir & actual->salidas) {
			actual->dir[nsal++]=nuevonodo(actual->x,actual->y,actual->paso,dir);
		}
	}
	for(u1 k=0;k<nsal;k++) {
		recursivo_tesoro(actual->dir[k]);
	}
}

static u1 tesoro_coloca(u2* x,u2* y) {
	u1 ret=0;
	nodo_max=NULL;
	struct Nodo* primero=nuevonodo(0,0,0,0);
	recursivo_tesoro(primero);
	struct Nodo* final=nodo_max;
	if(final) {
		*x=final->x;
		*y=final->y;
		ret=1;
	}
	nododel(primero);
	return ret;
}

void tesoro_define(u1 n) {
	static u1 gtedef=0;
	if(!gtedef) {
		//grafico
		char* dtsrf[]={
				"111111111111111111111111",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"111111111111111111111111",
				"111111111111111111111111",
				"110000000100001000000011",
				"110000000111111000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"111111111111111111111111",
				"111111111111111111111111"
		};
		gtesoro[0]=grafico_new(24,16,0,'0',dtsrf);
		char* dtsrl[]={
				"11111111",
				"10000001",
				"10000001",
				"10000001",
				"10000001",
				"10000001",
				"11111111",
				"11111111",
				"10000001",
				"10000001",
				"10000001",
				"10000001",
				"10000001",
				"10000001",
				"11111111",
				"11111111"
		};
		gtesoro[1]=grafico_new(8,16,0,'0',dtsrl);
		char* dtsrt[]={
				"111111111111111111111111",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"111111111111111111111111",
				"111111111111111111111111",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"110000000000000000000011",
				"111111111111111111111111",
				"111111111111111111111111"
		};
		gtesoro[2]=grafico_new(24,16,0,'0',dtsrt);
		gtedef=1;
	}
	//objeto
	Objeto dt={TESORO,COGIBLE,"TREASURE",0,0,0,{gtesoro,gtesoro+1,gtesoro+2,gtesoro+1},1,NORTH};
	objeto_new(dt);
	Objeto* ot=objeto_get(TESORO);
	if(!tesoro_coloca(&(ot->x),&(ot->y))) ot->activo=0;
	ot->face=NORTH<<(rand()%4);
}

static void espada_coloca(u1 id,u2* x,u2* y) {
	u1 ok=0;
	while(!ok) {
		mundo_rand(x,y);
		ok=1;
		for(u1 k=ESPADA_MIN;k<id;k++) {
			Objeto* oe=objeto_get(k);
			if(*x==oe->x && *y==oe->y) {
				ok=0;
				break;
			}
		}
	}
}

void espadas_define(u1 nivel) {
	static u1 gedef=0;
	if(!gedef) {
		//grafico
		char* detot[] = {
				"00000100000",
				"00001110000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010111000",
				"00010011000",
				"00010011000",
				"00010001000",
				"00001110000",
				"01111111110",
				"01111111110",
				"00001110000",
				"00000000000",
				"00001110000",
				"00000000000",
				"00001110000",
				"00000100000"
		};
		gespada=grafico_new(11,32,1,'0',detot);
		gedef=1;
	}
	u1 espadas=nivel-1;
	if(espadas) {
		for(u1 k=ESPADA_MIN;k<ESPADA_MIN+espadas;k++) {
			objeto_del(k);
			Objeto de={k,COGIBLE|ARMA,"SWORD",0,0,0,{&gespada,&gespada,&gespada,&gespada},1,NORTH};
			objeto_new(de);
			Objeto* oe=objeto_get(k);
			if(oe) espada_coloca(k,&(oe->x),&(oe->y));
		}
	}
}

void items_free() {
	grafico_del(&gpuerta);
	for(u1 k=0;k<3;k++) {
		grafico_del(gtesoro+k);
	}
	grafico_del(&gespada);
}
