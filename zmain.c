/*
============================================================
  Fichero: zmain.c
  Creado: 04-06-2025
  Ultima Modificacion: dimarts, 17 de juny de 2025, 13:06:27
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpersonaje.h"

#include <time.h>

Grafico gdp[3];

void pausa(double time) {
	clock_t fin=clock()+CLOCKS_PER_SEC*time;
	while(clock()<fin);
}

void grafico_init() {
	for(int k=0;k<3;k++) {
		u1 a[]={'A'+k};
		gdp[k]=grafico_new(1,1,a);
	}
}

void grafico_end() {
	for(int k=0;k<3;k++) {
		grafico_del(gdp+k);
	}
}

void objeto_init() {
	Objeto o={1,1,1,1,100,{gdp,gdp+1,gdp+2,gdp+1},0,NORTH};
	objeto_new(o);
}

int main() {
	srand(time(NULL));
	ini(CINK,CPAPER,500,500);
	mundo_new(5);
	personaje_init();
	grafico_init();
	objeto_init();
	u1 changes=1;
	while(kread()!=ESCAPE) {
		if(changes) {
			total_draw(personaje.x,personaje.y,personaje.face);
			mundo_prt(personaje.x,personaje.y);
			printf("%i,%i\n",personaje.x,personaje.y);//dbg
		}
		fls();
		changes=personaje_act();
		pausa(0.1);
		if(changes) clr();
	}
	grafico_end();
	mundo_del();
	end();
	return 0;
}
