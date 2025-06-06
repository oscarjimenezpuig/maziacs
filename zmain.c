/*
============================================================
  Fichero: zmain.c
  Creado: 04-06-2025
  Ultima Modificacion: divendres, 6 de juny de 2025, 11:38:10
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zpersonaje.h"

#include <time.h>

void pausa(double time) {
	clock_t fin=clock()+CLOCKS_PER_SEC*time;
	while(clock()<fin);
}

int main() {
	srand(time(NULL));
	ini(CINK,CPAPER,500,500);
	mundo_new(5);
	personaje_init();
	u1 changes=1;
	while(kread()!=ESCAPE) {
		if(changes) {
			total_draw(personaje.x,personaje.y,personaje.face);
			mundo_prt(personaje.x,personaje.y);
		}
		fls();
		changes=personaje_act();
		pausa(0.1);
		if(changes) clr();
	}
	mundo_del();
	end();
	return 0;
}
