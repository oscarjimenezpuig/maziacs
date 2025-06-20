/*
============================================================
  Fichero: zitems.c
  Creado: 18-06-2025
  Ultima Modificacion: divendres, 20 de juny de 2025, 05:40:29
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

void espadas_define(u1 nivel) {
	static u1 gedef=0;
	if(!gedef) {
		//grafico
		char* detot[] = {
				"00000100000",
				"00001010000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"00010001000",
				"01001110010",
				"11111111111",
				"01001110010",
				"00001110000",
				"00001010000",
				"00001110000",
				"00001010000",
				"00000100000"
		};
		gespada=grafico_new(11,22,'0',detot);
		gedef=1;
	}
	u1 espadas=nivel-1;
	if(espadas) {
		for(u1 k=ESPADA_MIN;k<ESPADA_MIN+espadas;k++) {
			objeto_del(k);
			Objeto de={k,COGIBLE|ARMA,"SWORD",0,0,0,{&gespada,&gespada,&gespada,&gespada},1,NORTH};
			objeto_new(de);
			Objeto* oe=objeto_get(k);
			if(oe) mundo_rand(&oe->x,&oe->y);
			//TODO Modificar la posicion para que solo haya un objeto por localizacion
			//TODO Modificar grafico de la espada (dimensiones mal)
		}
	}
}

void items_free() {
	for(u1 k=0;k<3;k++) {
		grafico_del(gtesoro+k);
	}
}
