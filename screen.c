/*
============================================================
  Fichero: screen.c
  Creado: 15-05-2025
  Ultima Modificacion: divendres, 6 de juny de 2025, 10:22:19
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "screen.h"

struct Node {
	u2 x,y;
	u1 on;
	struct Node* nxt;
};

typedef struct {
	struct Node* frs;
	struct Node* lst;
} List;

static X_Color ink=0;
static X_Color paper=0;
static u1* memory=NULL;
static u4 memsize=0;
static List list={NULL,NULL};
static u2 rw=0;
static u2 rh=0;

static u1 mst(u2 x,u2 y,u1 on) {
	u2 rx=x/8;
	if(rx<rw && y<rh) {
		u1* ptr=memory+rx+y*rw;
		u1 f=(1<<(x%8));
		if(on && (*ptr & f) == 0) {
			*ptr|=f;
			return 1;
		} else if(!on && (*ptr & f) == f) {
			*ptr&=(~f);
			return 1;
		}
	}
	return 0;
}

static u1 mgt(u2 x,u2 y,u1* on) {
	u2 rx=x/8;
	if(rx<rw && y<rh) {
		u1 val=*(memory+rx+y*rw);
		u1 f=(1<<(x%8));
		*on=(val & f)?1:0;
		return 1;
	}
	return 0;
}	

static u1 lps(u2 x,u2 y,u1 on) {
	struct Node* nn=malloc(sizeof(struct Node));
	if(nn) {
		*nn=(struct Node){x,y,on,NULL};
		if(list.lst) {
			list.lst->nxt=nn;
			list.lst=nn;
		} else {
			list.frs=list.lst=nn;
		}
		return 1;
	}
	return 0;
}

static u1 lpp(u2* x,u2* y,u1* on) {
	if(list.frs) {
		struct Node* td=list.frs;
		list.frs=list.frs->nxt;
		*x=td->x;
		*y=td->y;
		*on=td->on;
		free(td);
		return 1;
	} else {
		list.lst=NULL;
		return 0;
	}
}

static void lcl() {
	u2 x,y;
	u1 o;
	while(lpp(&x,&y,&o));
}

static u1 emp() {
	return (list.frs==NULL);
}

static void shw(u2 x,u2 y,u1 on) {
	X_Point p={x,y};
	X_Color c=(on)?ink:paper;
	x_point(p,c);
}

#define cc(A) ((double)(A)/(double)255)

u1 ini(Color i,Color p,u2 w,u2 h) {
	memory=malloc(sizeof(u1)*((w/8)+1)*h);
	if(memory) {
		memsize=((w/8)+1)*h;
		rw=(w/8)+1;
		rh=h;
		x_init(w,h);
		ink=x_color(cc(i.r),cc(i.g),cc(i.b));
		paper=x_color(cc(p.r),cc(p.g),cc(p.b));
		clr();
		return 1;
	}
	return 0;
}

#undef cc

void end() {
	free(memory);
	lcl();
	x_end();
}

void fls() {
	if(!emp()) {
		u2 x,y;
		u1 on;
		while(lpp(&x,&y,&on)) {
			shw(x,y,on);
		}
		x_flush();
	}
}

void rfl(u2 x,u2 y,u2 w,u2 h) {
	for(u2 i=x;i<x+w;i++) {
		for(u2 j=y;j<y+h;j++) {
			u1 r=0;
			if(mgt(i,j,&r)) shw(i,j,r);
		}
	}
	x_flush();
}

void rev() {
	X_Color brg=ink;
	ink=paper;
	paper=brg;
	u2 w=8*(rw-1);
	u2 h=rh;
	rfl(0,0,w,h);
}

void on(u2 x,u2 y) {
	if(mst(x,y,1)) lps(x,y,1);
}

void off(u2 x,u2 y) {
	if(mst(x,y,0)) lps(x,y,0);
}

u1 get(u2 x,u2 y) {
	u1 r=0;
	mgt(x,y,&r);
	return r;
}

void clr() {
	x_background(paper);
	x_flush();
	u1* ptr=memory;
	while(ptr!=memory+memsize) *ptr++=0;
	lcl();
}


