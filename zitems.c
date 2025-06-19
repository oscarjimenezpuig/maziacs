/*
============================================================
  Fichero: zitems.c
  Creado: 18-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 04:53:05
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zitems.h"

static Grafico gtesoro[3];
static Grafico gespada;

void tesoro_define(u1 n) {
	static u1 gtedef=0;
	if(!gtedef) {
		//grafico
		snew(128,255,192,192,192,192,192,255,255);
		snew(129,255,0,0,0,0,0,255,255);
		snew(130,255,3,3,3,3,3,255,255);
		snew(131,192,192,192,192,192,192,255,255);
		snew(132,66,126,0,0,0,0,255,255);
		snew(133,3,3,3,3,3,3,255,255);
		u1 spf[]={128,129,130,131,132,133};
		gtesoro[0]=grafico_new(3,2,spf);
		snew(134,255,129,129,129,129,129,255,255);
		snew(135,129,129,129,129,129,129,255,255);
		u1 spl[]={134,135};
		gtesoro[1]=grafico_new(1,2,spl);
		snew(136,0,0,0,0,0,0,255,255);
		u1 spt[]={128,129,130,131,136,133};
		gtesoro[2]=grafico_new(3,2,spt);
		//objeto
		Objeto dt={TESORO,COGIBLE,"TREASURE",0,0,0,{gtesoro,gtesoro+1,gtesoro+2,gtesoro+1},1,NORTH};
		objeto_new(dt);
		gtedef=1;
	}
	Objeto* ot=objeto_get(TESORO);
	ot->x=ot->y=1;
	while(ot->x==1 && ot->y==1) {
		mundo_rand(&(ot->x),&(ot->y));
	}
	ot->face=NORTH<<(rand()%4);
}

void items_free() {
	for(u1 k=0;k<3;k++) {
		grafico_del(gtesoro+k);
	}
}
