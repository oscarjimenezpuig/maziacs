/*
============================================================
  Fichero: zitems.c
  Creado: 18-06-2025
  Ultima Modificacion: divendres, 20 de juny de 2025, 13:26:17
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
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"1111111111",
				"0000000000",
		};
		gpuerta=grafico_new(10,36,'0',dpuet);
		gpudef=1;
	}
	Objeto opdef={PUERTA,SALIDA,"DOOR",1,1,0,{&gpuerta,&gpuerta,&gpuerta,&gpuerta},1,NORTH};
	objeto_new(opdef);
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
		gtesoro[0]=grafico_new(24,16,'0',dtsrf);
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
		gtesoro[1]=grafico_new(8,16,'0',dtsrl);
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
		gtesoro[2]=grafico_new(24,16,'0',dtsrt);
		//objeto
		Objeto dt={TESORO,COGIBLE,"TREASURE",0,0,0,{gtesoro,gtesoro+1,gtesoro+2,gtesoro+1},1,NORTH};
		gtedef=objeto_new(dt);
		tesoro_define(n);
	} else {
		Objeto* ot=objeto_get(TESORO);
		ot->x=ot->y=1;
		while(ot->x==1 && ot->y==1) {
			mundo_rand(&(ot->x),&(ot->y));
		}
		ot->face=NORTH<<(rand()%4);
	}
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
		gespada=grafico_new(11,32,'0',detot);
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
