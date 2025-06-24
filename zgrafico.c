/*
============================================================
  Fichero: zgrafico.c
  Creado: 06-06-2025
  Ultima Modificacion: diumenge, 22 de juny de 2025, 05:19:02
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zgrafico.h"

Grafico grafico_new(u1 w,u1 h,u1 a,char x,char* l[]) {
	Grafico g={0,0,0,NULL};
	u2 d=w*h;
	g.bit=malloc(sizeof(u1)*d);
	if(g.bit) {
		g.w=w;
		g.h=h;
		g.alpha=a;
		u1* ptru=g.bit;
		for(u1 j=0;j<h;j++) {
			char* ptr=l[j];
			while(ptr!=l[j]+w) {
				if(*ptr++==x) *ptru=0;
				else *ptru=1;
				ptru++;
			}
		}
	}
	return g;
}

Grafico grafico_flip(Grafico g) {
	Grafico gf={0,0,0,NULL};
	u2 w=g.w;
	u2 h=g.h;
	gf.bit=malloc(sizeof(u1)*w*h);
	if(gf.bit) {
		gf.w=w;
		gf.h=h;
		gf.alpha=g.alpha;
		for(u1 f=0;f<h;f++) {
			for(u1 c=0;c<w;c++) {
				gf.bit[c+f*w]=g.bit[(w-1-c)+f*w];
			}
		}
	}
	return gf;
}

void grafico_del(Grafico* g) {
	if(g) {
		free(g->bit);
		g->bit=NULL;
		g->w=g->h=0;
	}
}

static double ratio_previa(u1 b) {
	Punto poi={0,0,b*PARDIM};
	Punto ppoi;
	proyecta(poi,ppoi);
	Punto pod={PIXDIM,0,b*PARDIM};
	Punto ppod;
	proyecta(pod,ppod);
	return ((ppod[0]-ppoi[0])/PIXDIM);
}

static void pixel_onoff(u2 x,u2 y,u1 ratio,u1 o) {
	for(u1 i=0;i<ratio;i++) {
		for(u1 j=0;j<ratio;j++) {
			if(o) on(x+i,y+j);
			else off(x+i,y+j);
		}
	}
}

static double round(double value) {
	double intv=(int)value;
	double decv=value-intv;
	if(decv>=0.5) intv+=1.0;
	return intv;
}

void grafico_on(Grafico g,u2 y,u2 z) {
	const double FACTOR=PIXDIM; //factor de ratio de primer plano
	Punto pgo={(PARDIM-PIXDIM*g.w)/2,PIXDIM*(g.h)+y,z*PARDIM};
	Punto pgp;
	proyecta(pgo,pgp);
	double ratio=FACTOR*ratio_previa(z);
	ratio=round(ratio);//dbg
	for(u1 f=0;f<g.h;f++) {
		for(u1 c=0;c<g.w;c++) {
			u1 v=*(g.bit+c+f*g.w);
			if(v) pixel_onoff(ratio*c+pgp[0],ratio*f+pgp[1],ratio,1);
			else if(!g.alpha) pixel_onoff(ratio*c+pgp[0],ratio*f+pgp[1],ratio,0);
		}
	}
}


