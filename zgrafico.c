/*
============================================================
  Fichero: zgrafico.c
  Creado: 06-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 05:00:49
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

static double ratio_previa(u1 b) {
	Punto poi={0,0,b*PARDIM};
	Punto ppoi;
	proyecta(poi,ppoi);
	Punto pod={SPRDIM,0,b*PARDIM};
	Punto ppod;
	proyecta(pod,ppod);
	return ((ppod[0]-ppoi[0])/SPRDIM);
}

static void sprite_onoff(u1 sprite,u1 gh,u2 base_x,u2 base_y,u1 fila,u1 columna,double ratio,u1 on) {
	u2 px=base_x+ratio*8*columna;
	u2 py=base_y-(ratio*8*(gh-1-fila));
	if(on) son(sprite,px,py,ratio,NAT);	
	else soff(sprite,px,py,ratio,NAT);
}

static void grafico_onoff(Grafico g,u1 a,u1 b,u1 on) {
	const double FACTOR=SPRDIM/8; //factor de ratio de primer plano
	Punto pgo={(PARDIM-SPRDIM*g.w)/2,SPRDIM*(g.h)+a,b*PARDIM};
	Punto pgp;
	proyecta(pgo,pgp);
	double ratio=FACTOR*ratio_previa(b);
	for(u1 f=0;f<g.h;f++) {
		for(u1 c=0;c<g.w;c++) {
			sprite_onoff(*(g.sprite+c+f*g.w),g.h,pgp[0],pgp[1],f,c,ratio,on);
		}
	}
}

void grafico_on(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,1);
}

void grafico_off(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,0);
}

static u1 give_line(char white,char* line) {
	u1 total=0;
	u1 value=128;
	char* ptr=line;
	while(*ptr!='\0') {
		if(*ptr!=white) total+=value;
		value=value>>1;
		ptr++;
	}
	return total;
}

u1 sprite_data_new(u1 s,char w,char* d[]) {
	u1 spdef[8];
	for(u1 k=0;k<8;k++) {
		spdef[k]=give_line(w,d[k]);
	}
	return snew(s,spdef[0],spdef[1],spdef[2],spdef[3],spdef[4],spdef[5],spdef[6],spdef[7]);
}
	


