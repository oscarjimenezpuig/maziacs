/*
============================================================
  Fichero: zmain.c
  Creado: 04-06-2025
  Ultima Modificacion: dimarts, 24 de juny de 2025, 07:38:47
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zenemigos.h"


u1 nivel=1;
u1 quit=0;

void mundo_inicia() {
	for(u1 k=0;k<128;k++) koff(k);
	mundo_new(nivel);
	puts("Mundo");
	personaje_init();
	puts("Personaje");
	objeto_clear();
	puts("Limpiados");
	puerta_define();
	puts("Puerta");
	tesoro_define(nivel);
	puts("Tesoro");
	espadas_define(nivel);
	puts("Espadas");
	maziac_define(nivel);
	puts("Maziacs");
}

void mundo_finaliza() {
	items_free();
	enemigos_free();
	mundo_del();
}

u1 nuevo_nivel() {
	if(personaje.x==1 && personaje.y==1 && personaje.objeto==TESORO) {
		nivel++;
		if(nivel<=MAXLEVEL) {
			personaje_men_new("YOU BEAT THIS LEVEL");
			mundo_inicia();
		} else {
			personaje_men_new("CONGRATS, YOU BEAT THE GAME");
			quit=1;
		}
		return 1;
	}
	return 0;
}					

int main() {
	srand(time(NULL));
	ini(CINK,CPAPER,500,500);
	mundo_inicia();
	u1 changes=1;
	while(kread()!=ESCAPE && !quit) {
		if(changes) {
			total_draw(personaje.x,personaje.y,personaje.face);
			personaje_marc();
			mundo_prt(personaje.x,personaje.y);		
			fls();
		}
		changes=personaje_act() | nuevo_nivel();
		maziac_act();
		changes |= maziac_visto();
		personaje_men_show();
		pausa(0.1);
		if(changes) clr();
	}
	mundo_finaliza();
	end();
	return 0;
}
