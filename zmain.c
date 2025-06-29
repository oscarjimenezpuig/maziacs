/*
============================================================
  Fichero: zmain.c
  Creado: 04-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 06:45:31
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zenemigos.h"


u1 nivel=1;
u1 quit=0;

void mundo_dbg_prt(u2 x,u2 y) {
	char chr;
	u2 mundo_dimension=mundo_dim();
	for(u2 j=0;j<mundo_dimension;j++) {
		for(u2 i=0;i<mundo_dimension;i++) {
			if(mundo_get(i,j)) {
				chr=' ';
				if(i==x && j==y) chr='@';
				else {
					for(u2 id=0;id<OBJETOS;id++) {
						Objeto* o=objeto_get(id);
						if(o && o->activo && o->x==i && o->y==j) {
							if(o->tipo==8) chr='M';
							else if(o->tipo & 4) chr='/';
							else if(o->tipo & 2) chr='$';
													}
					}
				}
				printf("%c",chr);
			} else printf("\033[7m \033[0m");
		}
		puts("");
	}
}


void mundo_inicia() {
	for(u1 k=0;k<128;k++) koff(k);
	mundo_new(nivel);
	personaje_init();
	objeto_clear();
	puerta_define();
	tesoro_define(nivel);
	espadas_define(nivel);
	maziac_define(nivel);
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
			rev();
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
	double paus=0;
	u1 changes=1;
	while(kread()!=ESCAPE && !quit) {
		if(changes) {
			total_draw(personaje.x,personaje.y,personaje.face);
			personaje_marc();
			mundo_dbg_prt(personaje.x,personaje.y);		
			fls();
		}
		if(!personaje_men_show()) {
			paus=0.1;
			changes=personaje_act() | nuevo_nivel();
			maziac_act();
			changes |= maziac_visto();
		} else paus=0.05;
		pausa(paus);
		if(changes) clr();
	}
	mundo_finaliza();
	end();
	return 0;
}
