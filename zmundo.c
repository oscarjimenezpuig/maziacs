/*
============================================================
  Fichero: zmundo.c
  Creado: 04-06-2025
  Ultima Modificacion: diumenge, 29 de juny de 2025, 06:30:49
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zmundo.h"

static u1* mundo=NULL;
static u2 mundo_dimension=0;

static void set(u1 x,u1 y) {
	mundo[x+y*mundo_dimension]=1;
}

void mundo_new(u1 nivel) {
	mundo_del(mundo);
	u1 dimension=nivel*FACNIV;
	mundo_dimension=3*dimension;
	mundo=malloc(sizeof(u1)*mundo_dimension*mundo_dimension);
	if(mundo) {
		u1* ptr=mundo;
		while(ptr!=mundo+(mundo_dimension*mundo_dimension)) *ptr++=0;
		Maze m=mazenew(dimension,dimension);
		for(u1 j=0;j<dimension;j++) {
			for(u1 i=0;i<dimension;i++) {
				u1 s=mazeget(m,i,j);
				if(s & NORTH) set(3*i+1,3*j);
				if(s & SOUTH) set(3*i+1,3*j+2);
				if(s & EAST) set(3*i+2,3*j+1);
				if(s & WEST) set(3*i,3*j+1);
				set(3*i+1,3*j+1);
			}
		}
		mazedel(&m);
	} else mundo_dimension=0;
}

void mundo_del() {
	if(mundo) {
		free(mundo);
		mundo=NULL;
	}
}

u1 mundo_get(u2 x,u2 y) {
	if(mundo) {
		u4 pos=x+y*mundo_dimension;
		return mundo[pos];
	}
	return 0;
}

u1 mundo_sal(u2 x,u2 y) {
	u1 sal=0;
	if(x>0 && mundo_get(x-1,y)) sal|=WEST;
	if(x<mundo_dimension-1 && mundo_get(x+1,y)) sal|=EAST;
	if(y>0 && mundo_get(x,y-1)) sal|=NORTH;
	if(y<mundo_dimension-1 && mundo_get(x,y+1)) sal|=SOUTH;
	return sal;
}

u2 mundo_dim() {
	return mundo_dimension;
}

void mundo_rand(u2* x,u2* y) {
	if(mundo_dimension) {
		u2 xx,yy;
		xx=yy=0;
		while(!mundo_get(xx,yy)) {
			xx=rand()%mundo_dimension;
			yy=rand()%mundo_dimension;
		}
		*x=xx;
		*y=yy;
	}
}


