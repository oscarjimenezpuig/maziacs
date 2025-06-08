/*
============================================================
  Fichero: zgrafico.c
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 8 de juny de 2025, 06:51:36
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

void grafico_onoff(Grafico g,u2 a,u1 b,u1 on) {
	u1 ratio=VIS-b;
	if(ratio) {
		double mx=(PARDIM-(g.w*8))/2;
		double mz=PARDIM/2;
		double my=a;
		Punto p={mx,my,mz};
		Punto pp;
		proyecta(p,pp);
		for(u1 sy=0;sy<g.h;sy++) {
			for(u1 sx=0;sx<g.w;sx++) {
				u1 s=*(g.sprite+sx+sy*g.w);
				u2 x=(sx*8)*ratio+pp[0];
				u2 y=(sy*8)*ratio+pp[1];
				if(on) son(s,x,y,ratio,NAT);
				else soff(s,x,y,ratio,NAT);
			}
		}
	}
}

void grafico_on(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,1);
}

void grafico_off(Grafico g,u2 a,u1 b) {
	grafico_onoff(g,a,b,0);
}
				
		

		
