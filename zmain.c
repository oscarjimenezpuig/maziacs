/*
============================================================
  Fichero: zmain.c
  Creado: 04-06-2025
  Ultima Modificacion: dijous, 19 de juny de 2025, 08:57:34
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zitems.h"

#include <time.h>

u1 nivel=1;

void pausa(double time) {
	clock_t fin=clock()+CLOCKS_PER_SEC*time;
	while(clock()<fin);
}

void mundo_inicia() {
	personaje_init();
	puts("Personaje");
	mundo_new(nivel);
	puts("Mundo");
	tesoro_define(nivel);
	puts("Tesoro");
}

void mundo_finaliza() {
	items_free();
	mundo_del();
}

int main() {
	srand(time(NULL));
	ini(CINK,CPAPER,500,500);
	mundo_inicia();
	u1 changes=1;
	while(kread()!=ESCAPE) {
		if(changes) {
			total_draw(personaje.x,personaje.y,personaje.face);
			personaje_marc();
			mundo_prt(personaje.x,personaje.y);
			printf("posicion=%i,%i\n",personaje.x,personaje.y);//dbg
		}
		fls();
		changes=personaje_act();
		pausa(0.1);
		if(changes) clr();
	}
	mundo_finaliza();
	end();
	return 0;
}
