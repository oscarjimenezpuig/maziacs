/*
============================================================
  Fichero: zdraw.c
  Creado: 04-06-2025
  Ultima Modificacion: diumenge, 22 de juny de 2025, 07:42:38
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zdraw.h"

static void edgesget(Punto e,Vector n,u2* edge) {
	Vector cn={1-n[0],0,1-n[2]};
	Punto esi={e[0],e[1],e[2]};
	Punto esd={e[0]+cn[0]*PARDIM,e[1],e[2]+cn[2]*PARDIM};
	Punto eid={e[0]+cn[0]*PARDIM,e[1]-PARDIM,e[2]+cn[2]*PARDIM};
	Punto eii={e[0],e[1]-PARDIM,e[2]};
	Punto pesi,pesd,peid,peii;
	proyecta(esi,pesi);
	proyecta(esd,pesd);
	proyecta(eid,peid);
	proyecta(eii,peii);
	edge[0]=pesi[0];
	edge[1]=pesi[1];
	edge[2]=pesd[0];
	edge[3]=pesd[1];
	edge[4]=peid[0];
	edge[5]=peid[1];
	edge[6]=peii[0];
	edge[7]=peii[1];
}

void pared_draw(Punto e,Vector n) {
	u2 edge[8];
	edgesget(e,n,edge);
	pon(4,edge);
}

void pared_erase(Punto e,Vector n) {
	u2 edge[8];
	edgesget(e,n,edge);
	u2 max[2];
	u2 min[2];
	for(u1 k=0;k<2;k++) {
		for(u1 n=0;n<4;n++) {
			u1 pos=2*n+k;
			if(n==0) max[k]=min[k]=edge[pos];
			else {
				if(edge[pos]>max[k]) max[k]=edge[pos];
				else if(edge[pos]<min[k]) min[k]=edge[pos];
			}
		}
	}
	for(u2 i=min[0];i<=max[0];i++) {
		for(u2 j=min[1];j<=max[1];j++) {
			off(i,j);
		}
	}
}

#define DEL 1
#define IZQ 2
#define DER 4

static u1 vista(u1 d,u1 s) {
	u1 const DIRS[]={NORTH,EAST,SOUTH,WEST};
	int k=0;
	u1 del=0;
	u1 izq=0;
	u1 der=0;
	for(;k<4;k++) {
		if(d==DIRS[k]) break;
	}
	del=d;
	izq=DIRS[(k+3)%4];
	der=DIRS[(k+1)%4];
	u1 v=0;
	if(s & del) v|=DEL;
	if(s & izq) v|=IZQ;
	if(s & der) v|=DER;
	return v;
}

#define NX (Vector){1,0,0}
#define NZ (Vector){0,0,1}

#define P(A,B,C) (Punto){A,B,C}

static void eradrw(Punto esi,Vector normal) {
	pared_erase(esi,normal);
	pared_draw(esi,normal);
}

void posicion_draw(u1 b,u1 d,u1 s) {
	u1 vistas=vista(d,s);
	if(!(vistas & DEL)) {
			eradrw(P(0,PARDIM,PARDIM*(1+b)),NZ);
	}
	if(vistas & IZQ) {
		eradrw(P(-PARDIM,PARDIM,(b+1)*PARDIM),NZ);
	} else {
		eradrw(P(0,PARDIM,b*PARDIM),NX);
	}
	if(vistas & DER) {
		eradrw(P(PARDIM,PARDIM,(b+1)*PARDIM),NZ);
	} else {
		eradrw(P(PARDIM,PARDIM,b*PARDIM),NX);
	}
}

void nubes(u1 b) {
	const u2 PUNTOS=500;
	u2 inicio=b*PARDIM;
	for(u2 k=0;k<PUNTOS;k++) {
		Punto p;
		p[0]=rand()%PARDIM;
		p[1]=rand()%PARDIM;
		p[2]=rand()%PARDIM+inicio;
		Punto pp;
		proyecta(p,pp);
		on(pp[0],pp[1]);
	}
}


static void desp(u1 d,int* x,int* y) {
	int dx,dy;
	dx=dy=0;
	switch(d) {
		case NORTH:
			dy=-1;
			break;
		case SOUTH:
			dy=+1;
			break;
		case EAST:
			dx=+1;
			break;
		case WEST:
			dx=-1;
			break;
	}
	*x+=dx;
	*y+=dy;
}

			
u1 total_draw(u2 x,u2 y,u1 d) {
	u1 ret=0;
	u1 bloc=0;
	u1 salidas[VIS];
	int rx=x;
	int ry=y;
	u1 salida=0;
	while((salida=mundo_sal(rx,ry)) && (salidas[bloc]=salida) && (salida & d) && bloc<VIS) {
		bloc++;
		desp(d,&rx,&ry);
	}
	for(int k=bloc;k>=0;k--) {
		posicion_draw(k,d,salidas[k]);
		//nubes(k);

	}
	ret=visualizar_objetos(x,y,d);
	return ret;
}

	





		

	
