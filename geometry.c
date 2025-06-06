/*
============================================================
  Fichero: geometry.c
  Creado: 02-06-2025
  Ultima Modificacion: dimecres, 4 de juny de 2025, 11:29:56
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "geometry.h"

void rdrw(int xi,int yi,int xf,int yf,u1 o) {
	int x0=xi;
	int y0=yi;
	int x1=xf;
	int y1=yf;
	int dx=x1-x0;
	int dy=y1-y0;
	int ix=1;
	int iy=1;
	if(dy<0)
	{
		dy=-dy;
		iy=-1;
	}
	if(dx<0)
	{
		dx=-dx;
		ix=-1;
	}
	int irx=ix;
	int iry=iy;
	if(dx>=dy)
		iry=0;
	else
	{
		irx=0;
		int k=dx;
		dx=dy;
		dy=k;
	}
	int ar=2*dy;
	int ag=ar-dx;
	int ai=ag-dx;
	int nx=x0;
	int ny=y0;
	int step=0;
	int x,y;
	while(step!=dx+1)
	{
		x=nx;
		y=ny;
		if(o) on(x,y);
		else off(x,y);
		if(ag>=0)
		{
			nx+=ix;
			ny+=iy;
			ag+=ai;
		}
		else
		{
			nx+=irx;
			ny+=iry;
			ag+=ar;
		}
		step++;
	}
}

void ron(u2 xi,u2 yi,u2 xf,u2 yf) {
	rdrw(xi,yi,xf,yf,1);
}

void roff(u2 xi,u2 yi,u2 xf,u2 yf) {
	rdrw(xi,yi,xf,yf,0);
}

void pdrw(u1 es,u2* e,u1 o) {
	if(es>1) {
		u2* ptr=e;
		u1 iniciado=0;
		u2 xo,yo;
		u2 xi,yi;
		u2 xf,yf;
		xo=yo=xi=yi=xf=yf=0;
		while(ptr!=e+2*es) {
			if(!iniciado) {
				xi=xo=*ptr++;
				yi=yo=*ptr++;
				iniciado=1;
			} else {
				xi=xf;
				yi=yf;
			}
			xf=*ptr++;
			yf=*ptr++;
			if(o) ron(xi,yi,xf,yf);
			else roff(xi,yi,xf,yf);
		}
		if(o) ron(xf,yf,xo,yo);
		else roff(xf,yf,xo,yo);
	}
}

void pon(u1 es,u2* e) {
	pdrw(es,e,1);
}

void poff(u1 es,u2* e) {
	pdrw(es,e,0);
}
