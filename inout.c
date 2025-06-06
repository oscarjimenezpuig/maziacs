/*
============================================================
  Fichero: inout.c
  Creado: 22-05-2025
  Ultima Modificacion: dimecres, 4 de juny de 2025, 11:28:26
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "inout.h"

#define STRSIZ 256
#define KPSIZ 128

static u1 keyprs[KPSIZ];

static void stprt(u2* x,u2* y, s1 dx,s1 dy,u1 r,Attribute a,char* s,u1 on) {
	char* ptr=s;
	while(*ptr!='\0' && ptr-s<STRSIZ) {
		if(on) son(*ptr,*x,*y,r,a);
		else soff(*ptr,*x,*y,r,a);
		ptr++;
		*x+=dx*r*8;
		*y+=dy*r*8;
	}
}

void ston(u2* x,u2* y,s1 dx,s1 dy,u1 r,Attribute a,char* s) {
	stprt(x,y,dx,dy,r,a,s,1);
}

void stoff(u2* x,u2* y,s1 dx,s1 dy,u1 r,Attribute a,char* s) {
	stprt(x,y,dx,dy,r,a,s,0);
}

static void keyprsinit() {
	static u1 defined=0;
	if(!defined) {
		u1* ptr=keyprs;
		while(ptr!=keyprs+KPSIZ) *ptr++=0;
		defined=1;
	}
}

static u1 metakey(KeySym k) {
	const u1 METAS=10;
	const KeySym KS[]={XK_Escape,XK_Delete,XK_Left,XK_Right,XK_Up,XK_Down,XK_Shift_L,XK_Shift_R,XK_space,XK_Return};
	const u1 KC[]={ESCAPE,DELETE,LEFT,RIGHT,UP,DOWN,SHIFT,SHIFT,SPACE,ENTER};
	const KeySym* ptr=KS;
	while(ptr!=KS+METAS) {
		if(*ptr==k) return KC[ptr-KS];
		ptr++;
	}
	return 0;
}

static u1 alphanum(KeySym k) {
	char* ck=x_keystr(k);
	if(*(ck+1)=='\0') {
		if(*ck>='a' && *ck<='z') return *ck;
		else if(*ck>='0' && *ck<='9') return *ck;
	}
	return 0;
}
	
s1 kread() {
	keyprsinit();
	KeySym k;
	s1 ks=x_inkey(&k);
	if(ks) {
		u1 code=metakey(k);
		if(!code) {
			code=alphanum(k);
		}
		if(code) {
			keyprs[code]=(ks==1);
			return (ks==1)?code:-code;
		}
	}
	return 0;
}
	
u1 kison(u1 key) {
	if(key<KPSIZ) {
		return keyprs[key];
	}
	return 0;
}

void koff(u1 key) {
	if(key<KPSIZ) keyprs[key]=0;
}

static u1 chrptd(s1 dir,u1 shift) {
	char* const CRN="0123456789 ";
	char* const CRA="ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	char* const CRC="!\"#$%&/()[]/*+,-.:;><?@=\\^_{}|~ ";
	const u1 CRNS=11;
	const u1 CRAS=27;
	const u1 CRCS=32;
	static char* ptr=CRN;
	static u1 type=0;
	if(shift) {
		type=(type+1)%3;
		if(type==0) ptr=CRN;
		else if(type==1) ptr=CRA;
		else if(type==2) ptr=CRC;
	} else {
		if(dir==1) {
			ptr++;
			if(*ptr=='\0') ptr=(type==0)?CRN:(type==1)?CRA:CRC;
		} else if(dir==-1) {
			if(*ptr=='0') ptr=(type==0)?CRN+CRNS:(type==1)?CRA+CRAS:CRC+CRCS;
			ptr--;
		}
	}
	return *ptr;
}

static void erainp(u2 x,u2 y,s1 dx,s1 dy,u1 r,char* intro,u1 len) {
	char* ptr=intro;
	u2 f=y;
	u2 c=x;
	while(*ptr!='\0') {
		soff(' ',c,f,r,INV);
		c+=dx*8*r;
		f+=dy*8*r;
		ptr++;
	}
	for(u2 l=0;l<len;l++) {
		soff(' ',c,f,r,INV);
		c+=dx*8*r;
		f+=dy*8*r;
	}
}

static void visinp(u2 x,u2 y,s1 dx,s1 dy,u1 r,Attribute a,char* intro,char* str,u1 pos) {
	char* ptr=intro;
	u2 f=y;
	u2 c=x;
	while(*ptr!='\0') {
		son(*ptr,c,f,r,a);
		c+=dx*8*r;
		f+=dy*8*r;
		ptr++;
	}
	ptr=str;
	Attribute atr=a;
	while(*ptr!='\0') {
		if(pos==ptr-str) atr |= INV;
		else atr &= (~INV);
		son(*ptr,c,f,r,atr);
		c+=dx*8*r;
		f+=dy*8*r;
		ptr++;
	}
}
static u1 arrinp(char* str) {
	char* ptr=str;
	while(*ptr!='\0') ptr++;
	ptr--;
	while(*ptr==' ') ptr--;
	ptr++;
	*ptr='\0';
	return ptr-str;
}

u1 stin(u2 x,u2 y,s1 dx,s1 dy,u1 r,Attribute a,char* prompt,u1 len,char* str) {
	for(u1 k=0;k<len;k++) str[k]=' ';
	str[len]='\0';
	u1 finish=0;
	u1 poses=0;
	str[poses]=chrptd(0,0);
	visinp(x,y,dx,dy,r,a,prompt,str,poses);
	fls();
	while(!finish) {
		s1 code=kread();
		if(code>0) {
			if(code==LEFT && poses>0) {
				str[--poses]=chrptd(0,0);
			} else if(code==RIGHT && poses<len) {
				str[++poses]=chrptd(0,0);
			} else if(code==UP) {
				str[poses]=chrptd(-1,0);
			} else if(code==DOWN) {
				str[poses]=chrptd(1,0);
			} else if(code==ENTER) {
				finish=1;
			} else if(code==ESCAPE) {
				*str='\0';
				finish=1;
			} else if(code==SHIFT) {
				str[poses]=chrptd(0,1);
			}
			koff(code);
			erainp(x,y,dx,dy,r,prompt,len);
			if(!finish) visinp(x,y,dx,dy,r,a,prompt,str,poses);
			fls();
		}
	}
	return arrinp(str);
}


				




