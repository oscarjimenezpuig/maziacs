/*
============================================================
  Fichero: zproyecta.c
  Creado: 16-06-2025
  Ultima Modificacion: dilluns, 16 de juny de 2025, 09:08:23
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zproyecta.h"

void proyecta(Punto o,Punto p) {
	Punto pf=PFUGA;
	double k=1/(1-(o[2]/pf[2]));
	p[0]=pf[0]+k*(o[0]-pf[0]);
	p[1]=SCRH-(pf[1]+k*(o[1]-pf[1]));
	p[2]=0;
	for(u1 k=0;k<2;k++) if(p[k]<0) p[k]=0; 
}


