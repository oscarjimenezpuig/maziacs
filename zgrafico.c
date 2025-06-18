/*
============================================================
  Fichero: zgrafico.c
  Creado: 06-06-2025
  Ultima Modificacion: dimarts, 17 de juny de 2025, 14:31:13
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zgrafico.h"

Grafico grafico_new(u1 w,u1 h,u1* s) {
	Grafico g={0,0,NULL};
	u2 d=w*h;
	g.sprite=malloc(sizeof(u1)*d);
	if(g.sprite) {
		g.w=w;
		g.h=h;
		u1* ptr=s;
		u1* ptrc=g.sprite;
		while(ptr!=s+d) {
			*ptrc++=*ptr++;
		}
	}
	return g;
}

void grafico_del(Grafico* g) {
	if(g) {
		free(g->sprite);
		g->w=g->h=0;
	}
}

static double ratio_previa(u1 sprdim,u1 b) {
	Punto po={0,sprdim,b*PARDIM};
	Punto pp;
	proyecta(po,pp);
	return (pp[1]/po[1]);
}

static void sprite_onoff(u1 sprite,u2 base_x,u2 base_y,u1 fila,u1 columna,double ratio,u1 on) {
	u2 px=base_x+ratio*8*columna;
	u2 py=base_y+ratio*8*fila;
	if(on) son(sprite,px,py,ratio,NAT);	
	else soff(sprite,px,py,ratio,NAT);
}

static void grafico_onoff(Grafico g,u1 a,u1 b,u1 on) {
	const u1 SPRDIM=128; //dimension de un sprite en una habitacion normal
	const double FACTOR=SPRDIM/8; //factor de ratio de primer plano
	Punto pgo={(PARDIM-SPRDIM*g.w)/2,SPRDIM*g.h+a,b*PARDIM};
	Punto pgp;
	proyecta(pgo,pgp);
	double ratio=FACTOR*ratio_previa(SPRDIM,b);
	for(u1 f=0;f<g.h;f++) {
		for(u1 c=0;c<g.w;c++) {
		sprite_onoff(*(g.sprite+c+f*g.w),pgp[0],pgp[1],f,c,ratio,on);
		}
	}
}

void grafico_on(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,1);
}

void grafico_off(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,0);
}
				
		

		
