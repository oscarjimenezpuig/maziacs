/*
============================================================
  Fichero: zobjeto.c
  Creado: 08-06-2025
  Ultima Modificacion: divendres, 13 de juny de 2025, 15:40:49
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "zobjeto.h"

Objeto objetos[OBJETOS];

u1 objeto_new(Objeto o) {
	static u1 def=0;
	if(!def) {
		Objeto* ptr=objetos;
		while(ptr!=objetos+OBJETOS) {
			ptr->tipo=0;
			ptr++;
		}
		def=1;
	}
	Objeto* ptr=objetos+o.id;
	if(ptr->tipo==0) {
		*ptr=o;
		ptr->activo=1;
		return 1;
	}
	return 0;
}

void objeto_del(u1 id) {
	objetos[id].tipo=0;
	objetos[id].activo=0;
}

static u1 face(u1 dp,u1 fo) {
	//dp: direccion del personaje fo:hacia donde encara el objeto
	if(dp==fo) return TRASERA;
	else if(dp*fo==8) return FRONTAL;
	else return LATERAL;
}

static s1 arrive(u2 ox,u2 oy,u2 fx,u2 fy,s1 dx,s1 dy,u1 paso) {
	if(ox==fx && oy==fy) return paso;
	else {
		u2 nox=ox+dx;
		u2 noy=oy+dy;
		if(mundo_get(nox,noy)) return arrive(nox,noy,fx,fy,dx,dy,paso+1);
		else return -1;
	}
}

static u1 obisvis(Objeto o,u1* bloc,u1 dp,u2 px,u2 py) {
	if(dp==NORTH) {
		if(px==o.x && o.y<py && py-o.y<VIS) {
			s1 r=arrive(px,py,o.x,o.y,0,-1,0);
			if(r>=0) {
				*bloc=r;
				return face(NORTH,o.face);
			}
		}
	} else if(dp==SOUTH) {
		if(px==o.x && o.y>py && o.y-py<VIS) {
			s1 r=arrive(px,py,o.x,o.y,0,1,0);
			if(r>=0) {
				*bloc=r;
				return face(SOUTH,o.face);
			}
		}
	} else if(dp==EAST) {
		if(py==o.y && o.x>px && o.x-px<VIS) {
			s1 r=arrive(px,py,o.x,o.y,1,0,0);
			if(r>=0) {
				*bloc=r;
				return face(EAST,o.face);
			}
		}
	} else if(dp==WEST) {
		if(py==o.y && o.x<px && px-o.x<VIS) {
			s1 r=arrive(px,py,o.x,o.y,-1,0,0);
			if(r>=0) {
				*bloc=r;
				return face(WEST,o.face);
			}
		}
	}
	return 0;
}

u1 objeto_visto(Objeto o,u1* bloc) {
	return obisvis(o,bloc,personaje.face,personaje.x,personaje.y);
}

static struct Visto* ordena(struct Visto* v,struct Visto* nv) {
	struct Visto* a=NULL;
	struct Visto* s=v;
	if(s) {
		while(s && s->bloc>nv->bloc) {
			a=s;
			s=s->next;
		}
		nv->next=s;
		if(a) {
			a->next=nv;
			return v;
		}
	}
	return nv;
}

static struct Visto* visto_ins(struct Visto* visto,Objeto* o,u1 v,u1 b) {
	void* ptr=malloc(sizeof(struct Visto));
	if(ptr) {
		struct Visto* nv=ptr;
		nv->objeto=o;
		nv->vista=v;
		nv->bloc=b;
		nv->next=NULL;
		return ordena(visto,nv);
	}
	return visto;
}

static struct Visto* objetos_vistos() {
	struct Visto* v=NULL;
	Objeto* ptr=objetos;
	while(ptr!=objetos+OBJETOS) {
		if(ptr->activo) {
			u1 bloc=0;
			u1 vista=objeto_visto(*ptr,&bloc);
			v=visto_ins(v,ptr,vista,bloc);
		}
		ptr++;
	}
	return v;
}

static struct Visto* pop(struct Visto* a,Objeto** o,u1* v,u1* b) {
	if(a) {
		*o=a->objeto;
		*v=a->vista;
		*b=a->bloc;
		struct Visto* td=a;
		a=a->next;
		free(td);
	}
	return a;
}

static void objetos_on(struct Visto* vs) {
	struct Visto* a=vs;
	Objeto* o;
	u1 v,b;
	while((a=pop(a,&o,&v,&b))) {
		grafico_on(o->grafico[v],o->altura,b);
	}
}

u1 visualizar_objetos() {
	struct Visto* v=objetos_vistos();
	u1 r=(v)?1:0;
	objetos_on(v);
	return r;
}





			

	
