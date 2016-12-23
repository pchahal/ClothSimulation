/*-----------------------------------------------------------------------------------------
Pardeep Chahal
CMPT 461
Assignment 1 :  Curve Editor
-------------------------------------------------------------------------------------------*/

#include <math.h>	 
#include <stdio.h>						  
#include <stdlib.h>				
#include "GL/gl.h"     			/* import libraries */
#include "GL/glx.h"
#include "GL/glu.h"
#include "/gfs1/CMPT/461/aux.h"
#include "forms.h"
#include <stdlib.h>
#include "form.h"			/*  curve form header */
#include "form.c"
#include "mylib.h"


FD_form *ui;				/* handle to user interface xform */

/* declaration */



#define mpoints 8
#define npoints 8
#define MaxTriangles 100 
#define Triangles_per_Box 12
#define FALSE 0
#define TRUE 1

float           copx = 0;
float           copy = 50;
float           copz = 10;
float           vrpx = 0;
float           vrpy = 0;
float           vrpz = 0;

struct controlpoint {
	double x;
	double y;
	double z;
	double x0;
	double y0;
	double z0;
	double vx;
	double vy;
	double vz;
	double mass;
	double Fintx;
	double Finty;
	double Fintz;
	double Fextx;
	double Fexty;
	double Fextz;
} 
point[mpoints][npoints];

double structuralK=4;
double shearK=0;
double flexionK=0;

double gravityx=0;
double gravityy=-1;
double gravityz=0;

double ufluidx=.3;
double ufluidy=.2;
double ufluidz=.3;

double Cdis=.6;
double Cvi=0;			

double Tc=.10;
double naturalspringlength=1;
double vertexmass=.1;

struct triangle {
	double Ax,Ay,Az;
	double Bx,By,Bz;
	double Cx,Cy,Cz;
	double nx,ny,nz;
}
triangle[MaxTriangles];


double t=0;
double dt=.1;
int frame=0;
int iterations_per_frame=1;
int play=FALSE;
int nextframe=FALSE;
int collisions=TRUE;
int hangcloth=FALSE;
int hideobjects=FALSE;
int showclothmesh=TRUE;
int showsprings=FALSE;
int clothvertexmass=FALSE;




void init(void);
void translate(double,double,double);
void scale(double,double,double);
void rotate(double,double,double);
void initobjects(void);
void initializepoints(void);
/*  xform callback functions */



void StructK_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->StructK);
	structuralK=atof(s);
}

void ShearK_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->ShearK);
	shearK=atof(s);
}


void FlexK_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->FlexK);
	flexionK=atof(s);
}

void gravityx_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->gravityx);
	gravityx=atof(s);
}

void gravityy_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->gravityy);
	gravityy=atof(s);
}

void gravityz_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->gravityz);
	gravityz=atof(s);
}

void windx_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->windx);
	ufluidx=atof(s);
}

void windy_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->windy);
	ufluidy=atof(s);
}

void windz_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->windz);
	ufluidz=atof(s);
}

void Damping_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->Damping);
	Cdis=atof(s);
}

void Viscous_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->Viscous);
	Cvi=atof(s);
}

void VertexMass_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->VertexMass);
	vertexmass=atof(s);
}

void Play_callback(FL_OBJECT *ob, long data){
	play=TRUE;
	fl_set_button(ui->Stop_button,0);

}

void TimeStep_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->TimeStep);
	dt=atof(s);
}

void Stop_callback(FL_OBJECT *ob, long data){
	play=FALSE;
	fl_set_button(ui->Play_button,0);
}

void NextFrame_callback(FL_OBJECT *ob, long data){
	nextframe=TRUE;
}

void CameraX_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->CameraX);
	copx=atof(s);
}
void CameraY_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->CameraY);
	copy=atof(s);

}
void CameraZ_callback(FL_OBJECT *ob, long data){
	const char *s;
	s=fl_get_input(ui->CameraZ);
	copz=atof(s);
}

void Collision_callback(FL_OBJECT *ob, long data){
	if (collisions==FALSE)
		collisions=TRUE;
	else
		collisions=FALSE;
}

void Hang_callback(FL_OBJECT *ob, long data){
	if (hangcloth==FALSE)
		hangcloth=TRUE;
	else
		hangcloth=FALSE;
}

void TransformX_callback(FL_OBJECT *ob, long data){
}
void TransformY_callback(FL_OBJECT *ob, long data){
}
void TransformZ_callback(FL_OBJECT *ob, long data){
}

void Translate_callback(FL_OBJECT *ob, long data){
	const char *sx,*sy,*sz;
	double x,y,z;
	sx=fl_get_input(ui->TransformX);
	sy=fl_get_input(ui->TransformY);
	sz=fl_get_input(ui->TransformZ);
	x=atof(sx);
	y=atof(sy);
	z=atof(sz);
	translate(x,y,z);
}

void Scale_callback(FL_OBJECT *ob, long data){
	const char *sx,*sy,*sz;
	double x,y,z;
	sx=fl_get_input(ui->TransformX);
	sy=fl_get_input(ui->TransformY);
	sz=fl_get_input(ui->TransformZ);
	x=atof(sx);
	y=atof(sy);
	z=atof(sz);
	scale(x,y,z);
}

void Rotate_callback(FL_OBJECT *ob, long data){
	const char *sx,*sy,*sz;
	double x,y,z;
	sx=fl_get_input(ui->TransformX);
	sy=fl_get_input(ui->TransformY);
	sz=fl_get_input(ui->TransformZ);
	x=atof(sx);
	y=atof(sy);
	z=atof(sz);
	/*rotate(x,y,z);*/
}


extern void HideObject_callback(FL_OBJECT *ob, long data){
	if (hideobjects==FALSE)
		hideobjects=TRUE;
	else 
	    hideobjects=FALSE;
}

void Reset_callback(FL_OBJECT *ob, long data){
	initializepoints();
	initobjects();
}

void ShowClothMesh_callback(FL_OBJECT *ob, long data){
	if (showclothmesh==FALSE)
		showclothmesh=TRUE;
	else
		showclothmesh=FALSE;

}

void ShowSprings_callback(FL_OBJECT *ob,long data){
	if (showsprings==FALSE)
		showsprings=TRUE;
	else
		showsprings=FALSE;
}

void ShowVertexMass_callback(FL_OBJECT *ob, long data){
	if (vertexmass==FALSE)
		vertexmass=TRUE;
	else
		vertexmass=FALSE;
}


/*******************************************************************
 *  multiply object's transformation matrix by scale matrix 
 *  by scale factors x,y,z
 ******************************************************************/
void scale(double x,double y, double z){
	double scale[4][4]={
		0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1	};
	int i,j;
	double A[4],B[4],C[4],a[4],b[4],c[4];

	scale[0][0]=x;
	scale[1][1]=y;
	scale[2][2]=z;



	for (i=0;i<Triangles_per_Box;i++){	 
		A[0]=triangle[i].Ax;
		A[1]=triangle[i].Ay;
		A[2]=triangle[i].Az;
		A[3]=1;
		B[0]=triangle[i].Bx;
		B[1]=triangle[i].By;
		B[2]=triangle[i].Bz;
		B[3]=1;
		C[0]=triangle[i].Cx;
		C[1]=triangle[i].Cy;
		C[2]=triangle[i].Cz;
		C[3]=1;
		multiply2(a,A,scale);
		multiply2(b,B,scale);
		multiply2(c,C,scale);
		triangle[i].Ax=a[0];
		triangle[i].Ay=a[1];
		triangle[i].Az=a[2];
		triangle[i].Bx=b[0];
		triangle[i].By=b[1];
		triangle[i].Bz=b[2];
		triangle[i].Cx=c[0];
		triangle[i].Cy=c[1];
		triangle[i].Cz=c[2];

	}


}




/*******************************************************************
 *  multiply object's transformation matrix by translation matrix 
 *  with translation of   x,y,z
 ******************************************************************/
void translate(double x,double y,double z){
	double translate[4][4]={
		1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1	};
	int i,j;
	double A[4],B[4],C[4],a[4],b[4],c[4];

	translate[3][0]=x;
	translate[3][1]=y;
	translate[3][2]=z;

	/*multiply by translation matrix */

	for (i=0;i<Triangles_per_Box;i++){	 
		A[0]=triangle[i].Ax;
		A[1]=triangle[i].Ay;
		A[2]=triangle[i].Az;
		A[3]=1;
		B[0]=triangle[i].Bx;
		B[1]=triangle[i].By;
		B[2]=triangle[i].Bz;
		B[3]=1;
		C[0]=triangle[i].Cx;
		C[1]=triangle[i].Cy;
		C[2]=triangle[i].Cz;
		C[3]=1;
		multiply2(a,A,translate);
		multiply2(b,B,translate);
		multiply2(c,C,translate);
		triangle[i].Ax=a[0];
		triangle[i].Ay=a[1];
		triangle[i].Az=a[2];
		triangle[i].Bx=b[0];
		triangle[i].By=b[1];
		triangle[i].Bz=b[2];
		triangle[i].Cx=c[0];
		triangle[i].Cy=c[1];
		triangle[i].Cz=c[2];	  
	}
}




/*******************************************************************
 *  multiply object's transformation matrix by rotation matrix 
 *  rotate in on X-axs by x, y-axis by y, z-axis by z
 ******************************************************************/					
void rotate(double x,double y,double z){
	double rotatex[4][4]={
		1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1	};
	double rotatey[4][4]={
		0,0,0,0, 0,1,0,0, 0,0,0,0, 0,0,0,1	};  
	double rotatez[4][4]={
		0,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1	};
	int i,j;
	double A[4],B[4],C[4],a[4],b[4],c[4],N[4],n[4];
	const double PI=3.1415926535;

	rotatex[1][1]=cos(x*PI/180);     /*set sin and cos components */
	rotatex[1][2]=-sin(x*PI/180);	    /* for rotation matrices */
	rotatex[2][1]=sin(x*PI/180);
	rotatex[2][2]=cos(x*PI/180);

	rotatey[0][0]=cos(y*PI/180);
	rotatey[0][2]=sin(y*PI/180);
	rotatey[2][0]=-sin(y*PI/180);
	rotatey[2][2]=cos(y*PI/180);

	rotatez[0][0]=cos(z*PI/180);
	rotatez[0][1]=-sin(z*PI/180);
	rotatez[1][0]=sin(z*PI/180);
	rotatez[1][1]=cos(z*PI/180); 

	for (i=0;i<Triangles_per_Box;i++){	 
		A[0]=triangle[i].Ax;
		A[1]=triangle[i].Ay;
		A[2]=triangle[i].Az;
		A[3]=1;
		B[0]=triangle[i].Bx;
		B[1]=triangle[i].By;
		B[2]=triangle[i].Bz;
		B[3]=1;
		C[0]=triangle[i].Cx;
		C[1]=triangle[i].Cy;
		C[2]=triangle[i].Cz;
		C[3]=1;
		N[0]=triangle[i].nx;
		N[1]=triangle[i].ny;
		N[3]=triangle[i].nz;

		if (x!=0){
			multiply2(a,A,rotatex);
			multiply2(b,B,rotatex);
			multiply2(c,C,rotatex);
			multiply2(n,N,rotatex);
		}
		if (y!=0){		
			multiply2(a,A,rotatey);
			multiply2(b,B,rotatey);
			multiply2(c,C,rotatey);
			multiply2(n,N,rotatey);

		}
		if (z!=0){	
			multiply2(a,A,rotatez);
			multiply2(b,B,rotatez);
			multiply2(c,C,rotatez);
			multiply2(n,N,rotatez);
		}
		triangle[i].Ax=a[0];
		triangle[i].Ay=a[1];
		triangle[i].Az=a[2];
		triangle[i].Bx=b[0];
		triangle[i].By=b[1];
		triangle[i].Bz=b[2];
		triangle[i].Cx=c[0];
		triangle[i].Cy=c[1];
		triangle[i].Cz=c[2];
		triangle[i].nx=n[0];
		triangle[i].ny=n[1];
		triangle[i].nz=n[2];	  
	}  
}







int is_point_triangle_coplanar(int i,int j,int ABC,double *x,double *y,double *z){
	double ABx, ABy, ABz;
	double ACx, ACy, ACz;
	double AP0x,AP0y,AP0z;
	double APx, APy,APz;
	double AP0N;
	double APN;
	double length;
	double t;

	ABx=triangle[ABC].Bx-triangle[ABC].Ax;
	ABy=triangle[ABC].By-triangle[ABC].Ay;
	ABz=triangle[ABC].Bz-triangle[ABC].Az;

	ACx=triangle[ABC].Cx-triangle[ABC].Ax;
	ACy=triangle[ABC].Cy-triangle[ABC].Ay;
	ACz=triangle[ABC].Cz-triangle[ABC].Az;

	AP0x=point[i][j].x0- triangle[ABC].Ax;
	AP0y=point[i][j].y0- triangle[ABC].Ay;
	AP0z=point[i][j].z0- triangle[ABC].Az;

	APx=point[i][j].x- triangle[ABC].Ax;
	APy=point[i][j].y- triangle[ABC].Ay;
	APz=point[i][j].z- triangle[ABC].Az;

	AP0N = dotproduct3(AP0x,AP0y,AP0z,triangle[ABC].nx,triangle[ABC].ny,triangle[ABC].nz);
	APN  = dotproduct3(APx,APy,APz,triangle[ABC].nx,triangle[ABC].ny,triangle[ABC].nz);

	if (AP0N>0 && APN>0 || AP0N<0 && APN<0)
		return FALSE;

	else if (AP0N == 0){
		*x=point[i][j].x0;
		*y=point[i][j].y0;
		*z=point[i][j].z0;
		return TRUE;
	}
	else if (APN==0){
		*x=point[i][j].x;
		*y=point[i][j].y;
		*z=point[i][j].z;
		return TRUE;
	}

	else { /*
	    length=fabs(APN-AP0N);
		t=fabs(AP0N/length);
		*x=point[i][j].x0 + t*(point[i][j].x- point[i][j].x0);
		*y=point[i][j].y0 + t*(point[i][j].y- point[i][j].y0);
		*z=point[i][j].z0 + t*(point[i][j].z- point[i][j].z0); 
		*y=0.0;
		return TRUE;
	 }
		 */
	
		 double qx,qy,qz;
		 double wx,wy,wz;
		 double vx,vy,vz;
		 double px,py,pz;
		 double pqv;
		 double wv;
		  
		 qx=point[i][j].x0;
		 qy=point[i][j].y0;
		 qz=point[i][j].z0;
		 px=triangle[ABC].Ax;
		 py=triangle[ABC].Ay;
		 pz=triangle[ABC].Az;
		 vx=triangle[ABC].nx;
		 vy=triangle[ABC].ny;
		 vz=triangle[ABC].nz;
		 wx=point[i][j].x - point[i][j].x0;
		 wy=point[i][j].y - point[i][j].y0;
		 wz=point[i][j].z - point[i][j].z0;
	
		 pqv=dotproduct3(px-qx,py-qy,pz-qz,vx,vy,vz);
		 wv=dotproduct3(wx,wy,wz,vx,vy,vz);
		 qx=qx + (pqv/wv)*wx;
		 qy=qy + (pqv/wv)*wy;
		 qz=qz + (pqv/wv)*wz;
		 *x=qx;
		 *y=qy;
		 *z=qz;
		 return TRUE;
		 
		 }
	
		 
	
	
	
	}
	
	
	
	int is_point_in_triangle(int ABC,double x,double y,double z){
	  double ABx, ABy, ABz;
	  double ACx, ACy, ACz;
	  double APx, APy,APz;
	  double u1,v1;
	  double u2,v2;
	  double u3,v3;
	  double u,v,uv;
	
	  
	
	  ABx=triangle[ABC].Bx-triangle[ABC].Ax;
	  ABy=triangle[ABC].By-triangle[ABC].Ay;
	  ABz=triangle[ABC].Bz-triangle[ABC].Az;
	
	  ACx=triangle[ABC].Cx-triangle[ABC].Ax;
	  ACy=triangle[ABC].Cy-triangle[ABC].Ay;
	  ACz=triangle[ABC].Cz-triangle[ABC].Az;
	
	  APx=x- triangle[ABC].Ax;
	  APy=y- triangle[ABC].Ay;
	  APz=z- triangle[ABC].Az;
	  
	  if (ABz==0 && ACz==0 && APz==0){
	  if (ABx!=0)
	  	u=APx/ABx;
	  else 
	  	u=0;
	
	  if (ABx!=0)
	  	uv=ACx/ABx;
	  else
	  	uv=0;
		
	  if ((ACy-ABy*uv)!=0)
	  	v=(APy-ABy*u)/(ACy-ABy*uv);
	  else
		v=0;
	  
	  if (ABx!=0) 
	  	u=(APx-ACx*v)/ABx;
	  else
	    u=0;
	
	  if (u*ABx+v*ACx-APx<.01  &&  u*ABy+v*ACy-APy<.01 && u*ABz+v*ACz-APz<.01 && u>=0 && u<=1 && v>=0 && v<=1 /*&& u+v<=1*/
		){
			return TRUE;
		}
		else 	 {
			return FALSE;
		}

	}


	else if (ABy==0 && ACy==0 && APy==0){
		if (ABx!=0)
		    u=APx/ABx;
		else 
		    u=0;

		if (ABx!=0)
		    uv=ACx/ABx;
		else
			uv=0;

		if ((ACz-ABz*uv)!=0)
		    v=(APz-ABz*u)/(ACz-ABz*uv);
		else
			v=0;

		if (ABx!=0) 
		    u=(APx-ACx*v)/ABx;
		else
			u=0;

		if (u*ABx+v*ACx-APx<.01  &&  u*ABy+v*ACy-APy<.01 && u*ABz+v*ACz-APz<.01 && u>=0 && u<=1 && v>=0 && v<=1 /*&& u+v<=1*/){
			return TRUE;
		}
		else 	 {


			return FALSE;
		}

	}

	else /* (ABx==0 && ACx==0 && APx==0)*/{
		if (ABz!=0)
		    u=APz/ABz;
		else 
		    u=0;

		if (ABz!=0)
		    uv=ACz/ABz;
		else
			uv=0;

		if ((ACy-ABy*uv)!=0)
		    v=(APy-ABy*u)/(ACy-ABy*uv);
		else
			v=0;

		if (ABz!=0) 
		    u=(APz-ACz*v)/ABz;
		else
			u=0;

		if (u*ABx+v*ACx-APx<.01  &&  u*ABy+v*ACy-APy<.01 && u*ABz+v*ACz-APz<.01 && u>=0 && u<=1 && v>=0 && v<=1 /*&& u+v<=1*/){
			return TRUE;
		}
		else 	 {
			return FALSE;
		}

	}


}				  


int is_edge_edge_coplanar(int Ci,int Cj,int Di,int Dj,
double Ax,double Ay,double Az,
double Bx,double By,double Bz,
double *edge1x,double *edge1y,
double *edge1z,double *edge2x,double *edge2y,double *edge2z){

	double CD0x,CD0y,CD0z,AC0x,AC0y,AC0z;
	double ABx,ABy,ABz,CDx,CDy,CDz,ACx,ACy,ACz;

	double ABxCDx0,ABxCDy0,ABxCDz0,ABxCD_AC0;
	double ABxCDx,ABxCDy,ABxCDz,ABxCD_AC;
	double length,t;

	ABx=Bx-Ax;
	ABy=By-Ay;
	ABz=Bz-Az;

	CD0x=point[Di][Dj].x0-point[Ci][Cj].x0;
	CD0y=point[Di][Dj].y0-point[Ci][Cj].y0;
	CD0z=point[Di][Dj].z0-point[Ci][Cj].z0;

	AC0x=point[Ci][Cj].x0-Ax;
	AC0y=point[Ci][Cj].y0-Ay;
	AC0z=point[Ci][Cj].z0-Az;

	CDx=point[Di][Dj].x-point[Ci][Cj].x;
	CDy=point[Di][Dj].y-point[Ci][Cj].y;
	CDz=point[Di][Dj].z-point[Ci][Cj].z;

	ACx=point[Ci][Cj].x-Ax;
	ACy=point[Ci][Cj].y-Ay;								 
	ACz=point[Ci][Cj].z-Az;

	cross(ABx,ABy,ABz,CD0x,CD0y,CD0z,&ABxCDx0,&ABxCDy0,&ABxCDz0);
	ABxCD_AC0=dotproduct3(ABxCDx0,ABxCDy0,ABxCDz0,AC0x,AC0y,AC0z);

	cross(ABx,ABy,ABz,CDx,CDy,CDz,&ABxCDx,&ABxCDy,&ABxCDz);
	ABxCD_AC=dotproduct3(ABxCDx,ABxCDy,ABxCDz,ACx,ACy,ACz);


	if (ABxCD_AC0>0 && ABxCD_AC>0 || ABxCD_AC0<0 && ABxCD_AC<0)
	    return FALSE;

	else if (ABxCD_AC0 == 0){
		*edge1x=point[Ci][Cj].x0;
		*edge1y=point[Ci][Cj].y0;
		*edge1z=point[Ci][Cj].z0;
		*edge2x=point[Di][Dj].x0;
		*edge2y=point[Di][Dj].y0;
		*edge2z=point[Di][Dj].z0;

		return TRUE;
	}
	else if (ABxCD_AC==0){
		*edge1x=point[Ci][Cj].x;
		*edge1y=point[Ci][Cj].y;
		*edge1z=point[Ci][Cj].z;
		*edge2x=point[Di][Dj].x;
		*edge2y=point[Di][Dj].y;
		*edge2z=point[Di][Dj].z;
		return TRUE;
	}

	else { 
		length=fabs(ABxCD_AC-ABxCD_AC0);

		t=fabs(ABxCD_AC0/length);

		*edge1x=point[Ci][Cj].x0 + t*(point[Ci][Cj].x- point[Ci][Cj].x0);
		*edge1y=point[Ci][Cj].y0 + t*(point[Ci][Cj].y- point[Ci][Cj].y0);
		*edge1z=point[Ci][Cj].z0 + t*(point[Ci][Cj].z- point[Ci][Cj].z0);

		*edge2x=point[Di][Dj].x0 + t*(point[Di][Dj].x- point[Di][Dj].x0);
		*edge2y=point[Di][Dj].y0 + t*(point[Di][Dj].y- point[Di][Dj].y0);
		*edge2z=point[Di][Dj].z0 + t*(point[Di][Dj].z- point[Di][Dj].z0);



		/*y=0.0*/
		return TRUE;
	}














}


void checkcollisions(){
	int i,j,k;
	double x,y,z;
	double edge1x,edge1y,edge1z,edge2x,edge2y,edge2z;
	int collision=FALSE;

	/* point triangle collisions */ 

	for (i=0;i<mpoints;i++){
		for (j=0;j<npoints;j++){
			for (k=0;k<4;k++){
				if (i==0 && j==7 && point[i][j].y<0)
				    printf("");
				if (is_point_triangle_coplanar(i,j,k,&x,&y,&z)){	
					collision=is_point_in_triangle(0,x,y,z);
					if (collision==TRUE){
						point[i][j].x=x;
						point[i][j].y=y;
						point[i][j].z=z;
					}

				}

			}

		}
		/*  edge-edge collisions */

		is_edge_edge_coplanar(0,3,0,4,triangle[0].Ax,triangle[0].Ay,triangle[0].Az,
		triangle[0].Cx,triangle[0].Cy,triangle[0].Cz,
		&edge1x,&edge1y,&edge1z,&edge2x,&edge2x,&edge2z);



	}







}


void drawcloth(void){
	int i,j;
	double nx,ny,nz;

	GLfloat amb[]={
		.8,.8,.8,1	};
	GLfloat diff[]={
		.8,.8,.8,1	};
	GLfloat structamb[]={
		.8,0,0	};
	GLfloat structdiff[]={
		.8,.1,.1	};
	GLfloat shearamb[]={
		1,1,0	};
	GLfloat sheardiff[]={
		1,1,0	};
	GLfloat flexamb[]={
		0,1,0	};
	GLfloat flexdiff[]={
		0,1,0	};



	/* draw control points */

	glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);

	if (vertexmass==TRUE){
		for (i=0;i<mpoints;i++){
			for (j=0;j<npoints;j++){

				glMaterialfv(GL_FRONT,GL_AMBIENT,structamb);
				glMaterialfv(GL_FRONT,GL_DIFFUSE,structdiff);


				glPushMatrix();
				glTranslatef(point[i][j].x,point[i][j].y,point[i][j].z);
				auxSolidCube(.2);
				glPopMatrix();	 

			}
		}
	}


	/* draw structural springs */

	if (showsprings==TRUE){
		glMaterialfv(GL_FRONT,GL_AMBIENT,structamb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,structdiff);
		for (i=0;i<mpoints-1;i++){
			for (j=0;j<npoints;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i+1][j].x,point[i+1][j].y,point[i+1][j].z);
				glEnd();	

			}
		}

		for (i=0;i<mpoints;i++){
			for (j=0;j<npoints-1;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i][j+1].x,point[i][j+1].y,point[i][j+1].z);
				glEnd();


			}
		}

	}



	/* draw shear springs */
	if (showsprings==TRUE){
		glMaterialfv(GL_FRONT,GL_AMBIENT,shearamb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,sheardiff);
		for (i=0;i<mpoints-1;i++){
			for (j=0;j<npoints-1;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i+1][j+1].x,point[i+1][j+1].y,point[i+1][j+1].z);
				glEnd();	

			}
		}

		for (i=0;i<mpoints-1;i++){
			for (j=0;j<npoints-1;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i+1][j].x,point[i+1][j].y,point[i+1][j].z);
				glVertex3f(point[i][j+1].x,point[i][j+1].y,point[i][j+1].z);
				glEnd();


			}
		}
	}	

	/* draw flexion springs */
	if (showsprings==TRUE){
		glMaterialfv(GL_FRONT,GL_AMBIENT,flexamb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,flexdiff);
		for (i=0;i<mpoints-2;i++){
			for (j=0;j<npoints;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i+2][j].x,point[i+2][j].y,point[i+2][j].z);
				glEnd();	

			}
		}

		for (i=0;i<mpoints;i++){
			for (j=0;j<npoints-2;j++){
				glBegin(GL_LINES);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i][j+2].x,point[i][j+2].y,point[i][j+2].z);
				glEnd();


			}
		}

	}   


	/*  draw surface triangles */
	if (showclothmesh==TRUE){
		glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);	  
		for (i=0;i<mpoints-1;i++){
			for (j=0;j<npoints-1;j++){
				glBegin(GL_POLYGON);
				cross(point[i][j].x-point[i+1][j].x,point[i][j].y-point[i+1][j].y,point[i][j].z-point[i+1][j].z,
				point[i][j].x-point[i+1][j+1].x,point[i][j].y-point[i+1][j+1].y,point[i][j].z-point[i+1][j+1].z,
				&nx,&ny,&nz);
				normalized(&nx,&ny,&nz);			
				glNormal3f(nx,ny,nz);
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i+1][j+1].x,point[i+1][j+1].y,point[i+1][j+1].z);
				glVertex3f(point[i+1][j].x,point[i+1][j].y,point[i+1][j].z);
				glEnd();

				glBegin(GL_POLYGON);
				cross(point[i][j].x-point[i+1][j+1].x,point[i][j].y-point[i+1][j+1].y,point[i][j].z-point[i+1][j+1].z,
				point[i][j].x-point[i][j+1].x,point[i][j].y-point[i][j+1].y,point[i][j].z-point[i][j+1].z,
				&nx,&ny,&nz);																						
				normalized(&nx,&ny,&nz);
				glNormal3f(nx,ny,nz);  	
				glVertex3f(point[i][j].x,point[i][j].y,point[i][j].z);
				glVertex3f(point[i][j+1].x,point[i][j+1].y,point[i][j+1].z);
				glVertex3f(point[i+1][j+1].x,point[i+1][j+1].y,point[i+1][j+1].z);
				glEnd();


			}
		} 

	}
}



double getspringlength(int i,int j,int k, int l){
	double length;
	double a,b,c,sum;

	a=point[i][j].x-point[k][l].x;
	b=point[i][j].y-point[k][l].y;
	c=point[i][j].z-point[k][l].z;
	sum= (a*a)+ (b*b) + (c*c);
	length=sqrt(sum);

	return length;
}



void adjustspring(int i,int j,int k, int l,double springlength){
	double loosemass1x,loosemass1y,loosemass1z;
	double loosemass2x,loosemass2y,loosemass2z;
	double length;

	loosemass1x=point[i][j].x;
	loosemass1y=point[i][j].y;
	loosemass1z=point[i][j].z;

	loosemass2x=point[k][l].x;
	loosemass2y=point[k][l].y;
	loosemass2z=point[k][l].z;


	/*	
	
	  if (i==6 && j==0 && k==7 && l==0){
	    point[i][j].x=  loosemass2x +	 (loosemass1x-loosemass2x)/springlength;
	   	point[i][j].y=  loosemass2y +	 (loosemass1y-loosemass2y)/springlength;
	   	point[i][j].z=  loosemass2z +	 (loosemass1z-loosemass2z)/springlength; 
	
	  }
	 */
	   if (i==6 && j==7 && k==7 && l==7){
	    point[i][j].x=  loosemass2x +	 (loosemass1x-loosemass2x)/springlength;
	   	point[i][j].y=  loosemass2y +	 (loosemass1y-loosemass2y)/springlength;
	   	point[i][j].z=  loosemass2z +	 (loosemass1z-loosemass2z)/springlength; 
	
	  }
	/* 
	  else if (i==7 && j==0 && k==7 && l==1){
	    point[k][l].x=  loosemass1x +	 (loosemass2x-loosemass1x)/springlength;
	    point[k][l].y=  loosemass1y +	 (loosemass2y-loosemass1y)/springlength;
	   	point[k][l].z=  loosemass1z +	 (loosemass2z-loosemass1z)/springlength;
	  }
	*/
	
	  else if (i==7 && j==6 && k==7 && l==7){
	   	point[i][j].x=  loosemass2x +	 (loosemass1x-loosemass2x)/springlength;
	   	point[i][j].y=  loosemass2y +	 (loosemass1y-loosemass2y)/springlength;
	   	point[i][j].z=  loosemass2z +	 (loosemass1z-loosemass2z)/springlength; 
	  }
	
	   	 
	
	  else {{
	   
	
	
	
	   if (1==1)  /*(loosemass1length>loosemass2length)*/
	{


		point[i][j].x=  loosemass2x +	 (loosemass1x-loosemass2x)/springlength;
		point[i][j].y=  loosemass2y +	 (loosemass1y-loosemass2y)/springlength;
		point[i][j].z=  loosemass2z +	 (loosemass1z-loosemass2z)/springlength;


		/*	
		    point[i][j].x=  loosemass1x +	 (loosemass2x-loosemass1x)*((springlength-1)/2);
		   	point[i][j].y=  loosemass1y +	 (loosemass2x-loosemass1x)*((springlength-1)/2);
		   	point[i][j].z=  loosemass1z +	 (loosemass2x-loosemass1x)*((springlength-1)/2); 
			point[k][l].x=  loosemass1x +	 (loosemass2x-loosemass1x)*((springlength-1)/2);
		    point[k][l].y=  loosemass1y +	 (loosemass2y-loosemass1y)*((springlength-1)/2);
		   	point[k][l].z=  loosemass1z +	 (loosemass2z-loosemass1z)*((springlength-1)/2);
		*/	 
		   
		   }
		   
		   else if (1==0 )/*(loosemass1length<loosemass2length)*/{
			point[k][l].x=  loosemass1x +	 (loosemass2x-loosemass1x)/springlength;
			point[k][l].y=  loosemass1y +	 (loosemass2y-loosemass1y)/springlength;
			point[k][l].z=  loosemass1z +	 (loosemass2z-loosemass1z)/springlength;

			/*point[i][j].x=  loosemass2x +	 (loosemass1x-loosemass2x)/springlength + (loosemass1x-loosemass2x)/2;
			   	point[i][j].y=  loosemass2y +	 (loosemass1y-loosemass2y)/springlength + (loosemass1y-loosemass2y)/2;
			   	point[i][j].z=  loosemass2z +	 (loosemass1z-loosemass2z)/springlength + (loosemass1z-loosemass2z)/2;
			     
			    point[k][l].x=  loosemass1x +	 (loosemass2x-loosemass1x)/springlength + (loosemass2x-loosemass1x)/2;;
			    point[k][l].y=  loosemass1y +	 (loosemass2y-loosemass1y)/springlength + (loosemass2y-loosemass1y)/2;;
			   	point[k][l].z=  loosemass1z +	 (loosemass2z-loosemass1z)/springlength + (loosemass2z-loosemass1z)/2;;
				  */

		}


	}
}


}


void checkspringdeformation(void){
int i,j,k,iterations;
double springlength;
iterations=5;


/* structural springs */
for (k=0;k<iterations;k++){
	for (i=0;i<mpoints-1;i++){
		for (j=0;j<npoints;j++){
			springlength=getspringlength(i,j,i+1,j);
			if (springlength>(naturalspringlength + Tc*0)){

				adjustspring(i,j,i+1,j,springlength);	
			}
		}	
	}

	for (i=0;i<mpoints;i++){
		for (j=0;j<npoints-1;j++){
			springlength=getspringlength(i,j,i,j+1);
			if (springlength>(naturalspringlength + Tc*0)){
				if (i==7 && j==0 && springlength>(naturalspringlength + Tc) ){
					printf("");
					printf("");	
				}		
				adjustspring(i,j,i,j+1,springlength);	
			}
		}
	}


}

}






void structuralforces(int i,int j, double *Fstructx,double *Fstructy,double *Fstructz){
double lspringx,lspringy,lspringz;
double lspringnx,lspringny,lspringnz;




/* structural springs */

/* left */

if (j>0) {
	lspringx=point[i][j-1].x-point[i][j].x;
	lspringy=point[i][j-1].y-point[i][j].y;
	lspringz=point[i][j-1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fstructx=structuralK*(lspringx-lspringnx);
	*Fstructy=structuralK*(lspringy-lspringny);
	*Fstructz=structuralK*(lspringz-lspringnz);
}


/* top */

if (i>0) {
	lspringx=point[i-1][j].x-point[i][j].x;
	lspringy=point[i-1][j].y-point[i][j].y;
	lspringz=point[i-1][j].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fstructx+=structuralK*(lspringx-lspringnx);
	*Fstructy+=structuralK*(lspringy-lspringny);
	*Fstructz+=structuralK*(lspringz-lspringnz);
}


/* right */

if (j<npoints-1) {
	lspringx=point[i][j+1].x-point[i][j].x;
	lspringy=point[i][j+1].y-point[i][j].y;
	lspringz=point[i][j+1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fstructx+=structuralK*(lspringx-lspringnx);
	*Fstructy+=structuralK*(lspringy-lspringny);
	*Fstructz+=structuralK*(lspringz-lspringnz);
}

/* bottom */

if (i<mpoints-1) {
	lspringx=point[i+1][j].x-point[i][j].x;
	lspringy=point[i+1][j].y-point[i][j].y;
	lspringz=point[i+1][j].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fstructx+=structuralK*(lspringx-lspringnx);
	*Fstructy+=structuralK*(lspringy-lspringny);
	*Fstructz+=structuralK*(lspringz-lspringnz);
}




}


void shearforces(int i,int j, double *Fshearx,double *Fsheary,double *Fshearz){
double lspringx,lspringy,lspringz;
double lspringnx,lspringny,lspringnz;



/* shear springs */

/* top left */

if (i>0 && j>0  ) {
	lspringx=point[i-1][j-1].x-point[i][j].x;
	lspringy=point[i-1][j-1].y-point[i][j].y;
	lspringz=point[i-1][j-1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fshearx=shearK*(lspringx-lspringnx);
	*Fsheary=shearK*(lspringy-lspringny);
	*Fshearz=shearK*(lspringz-lspringnz);
}


/* top right */

if (i>0 && j<npoints-1) {
	lspringx=point[i-1][j+1].x-point[i][j].x;
	lspringy=point[i-1][j+1].y-point[i][j].y;
	lspringz=point[i-1][j+1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fshearx+=shearK*(lspringx-lspringnx);
	*Fsheary+=shearK*(lspringy-lspringny);
	*Fshearz+=shearK*(lspringz-lspringnz);
}


/* bottom right */

if (i< mpoints-1 && j<npoints-1) {
	lspringx=point[i+1][j+1].x-point[i][j].x;
	lspringy=point[i+1][j+1].y-point[i][j].y;
	lspringz=point[i+1][j+1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fshearx+=shearK*(lspringx-lspringnx);
	*Fsheary+=shearK*(lspringy-lspringny);
	*Fshearz+=shearK*(lspringz-lspringnz);
}

/* bottom left */

if (i<mpoints-1 && j>0) {
	lspringx=point[i+1][j-1].x-point[i][j].x;
	lspringy=point[i+1][j-1].y-point[i][j].y;
	lspringz=point[i+1][j-1].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fshearx+=shearK*(lspringx-lspringnx);
	*Fsheary+=shearK*(lspringy-lspringny);
	*Fshearz+=shearK*(lspringz-lspringnz);
}

}


void flexionforces(int i,int j, double *Fflexx,double *Fflexy,double *Fflexz){
double lspringx,lspringy,lspringz;
double lspringnx,lspringny,lspringnz;



/* flexion springs */

/* left */

if (j>1) {
	lspringx=point[i][j-2].x-point[i][j].x;
	lspringy=point[i][j-2].y-point[i][j].y;
	lspringz=point[i][j-2].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fflexx=flexionK*(lspringx-lspringnx);
	*Fflexy=flexionK*(lspringy-lspringny);
	*Fflexz=flexionK*(lspringz-lspringnz);
}


/* top */

if (i>1) {
	lspringx=point[i-2][j].x-point[i][j].x;
	lspringy=point[i-2][j].y-point[i][j].y;
	lspringz=point[i-2][j].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fflexx+=flexionK*(lspringx-lspringnx);
	*Fflexy+=flexionK*(lspringy-lspringny);
	*Fflexz+=flexionK*(lspringz-lspringnz);
}


/* right */

if (j<npoints-2) {
	lspringx=point[i][j+2].x-point[i][j].x;
	lspringy=point[i][j+2].y-point[i][j].y;
	lspringz=point[i][j+2].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fflexx+=flexionK*(lspringx-lspringnx);
	*Fflexy+=flexionK*(lspringy-lspringny);
	*Fflexz+=flexionK*(lspringz-lspringnz);
}

/* bottom */

if (i<mpoints-2) {
	lspringx=point[i+2][j].x-point[i][j].x;
	lspringy=point[i+2][j].y-point[i][j].y;
	lspringz=point[i+2][j].z-point[i][j].z;
	lspringnx=lspringx;
	lspringny=lspringy;
	lspringnz=lspringz;
	normalized(&lspringnx,&lspringny,&lspringnz);

	*Fflexx+=flexionK*(lspringx-lspringnx);
	*Fflexy+=flexionK*(lspringy-lspringny);
	*Fflexz+=flexionK*(lspringz-lspringnz);
}


}




void internalforces(int i,int j){
double Fstructx,Fstructy,Fstructz;		/* Force from structural spring */
double Fshearx,Fsheary,Fshearz;			/* Force from shear spring */
double Fflexx,Fflexy,Fflexz;		    /* Force from flexion spring */


Fstructx=0;
Fstructy=0;
Fstructz=0;
Fshearx=0;
Fsheary=0;
Fshearz=0;
Fflexx=0;
Fflexy=0;
Fflexz=0;

structuralforces(i,j,&Fstructx,&Fstructy,&Fstructz);
shearforces(i,j,&Fshearx,&Fsheary,&Fshearz);
flexionforces(i,j,&Fflexx,&Fflexy,&Fflexz);

point[i][j].Fintx=Fstructx + Fshearx + Fflexx;
point[i][j].Finty=Fstructy + Fsheary + Fflexy;
point[i][j].Fintz=Fstructz + Fshearz + Fflexz;

}



void externalforces(int i,int j){
double Fgrx,Fgry,Fgrz;				    /* Force of gravity  */
double Fdisx,Fdisy,Fdisz;
double Fvix,Fviy,Fviz;
double nx,ny,nz;
double point2x,point2y,point2z;
double point3x,point3y,point3z;
double u_vx,u_vy,u_vz;
double ndotu_v; 

/*   gravity 	*/

Fgrx= point[i][j].mass*gravityx;
Fgry= point[i][j].mass*gravityy;
Fgrz= point[i][j].mass*gravityz;

/* viscous damping */

Fdisx=-Cdis*point[i][j].vx;
Fdisy=-Cdis*point[i][j].vy;
Fdisz=-Cdis*point[i][j].vz; 



/*  wind/air resistance  */

if (j==npoints-1){
	point2x=point[i][j-1].x;
	point2y=point[i][j-1].y;
	point2z=point[i][j-1].z;
}
else {
	point2x=point[i][j+1].x;
	point2y=point[i][j+1].y;
	point2z=point[i][j+1].z;
}


if (i==mpoints-1){
	point3x=point[i-1][j].x;
	point3y=point[i-1][j].y;
	point3z=point[i-1][j].z;
}
else {
	point3x=point[i+1][j].x;
	point3y=point[i+1][j].y;
	point3z=point[i+1][j].z;
}

cross(point2x,point2y,point2z,point3x,point3y,point3z,&nx,&ny,&nz);
normalized(&nx,&ny,&nz);


u_vx=ufluidx-point[i][j].vx;
u_vy=ufluidy-point[i][j].vy;
u_vz=ufluidz-point[i][j].vz;

ndotu_v=dotproduct3(nx,ny,nz,u_vx,u_vy,u_vz);

Fvix=Cvi*ndotu_v*nx;
Fviy=Cvi*ndotu_v*ny;
Fviz=Cvi*ndotu_v*nz;


point[i][j].Fextx=Fgrx + Fdisx + Fvix;
point[i][j].Fexty=Fgry + Fdisy + Fviy;
point[i][j].Fextz=Fgrz + Fdisz + Fviz;


}


void calculatenewpoints(void){

int i,j;
double ax,ay,az;					    /* acceleration vector */
double Fx,Fy,Fz;						/* final force vector */



for (i=0;i<mpoints;i++){
	for (j=0;j<npoints;j++){
		internalforces(i,j);
	}
}





for (i=0;i<mpoints;i++){
	for (j=0;j<npoints;j++){	 
		externalforces(i,j);
	}
}




for (i=0;i<mpoints;i++){
	for (j=0;j<npoints;j++){	 



		Fx=point[i][j].Fintx + point[i][j].Fextx;
		Fy=point[i][j].Finty + point[i][j].Fexty;
		Fz=point[i][j].Fintz + point[i][j].Fextz;

		ax=(1/point[i][j].mass)*Fx;
		ay=(1/point[i][j].mass)*Fy;
		az=(1/point[i][j].mass)*Fz;

		point[i][j].vx=point[i][j].vx + dt*ax;
		point[i][j].vy=point[i][j].vy + dt*ay;
		point[i][j].vz=point[i][j].vz + dt*az;

		if (hangcloth==TRUE){
			if ((i==mpoints-1 && j==npoints-1) ||(i==mpoints-1 && j==0)||
			    (i==0 && j==0) || (i==0) && j==npoints-1){
				point[i][j].Fintx=0;
				point[i][j].Finty=0;
				point[i][j].Fintz=0;
				point[i][j].Fintx=0;
				point[i][j].Finty=0;
				point[i][j].Fintz=0;
				point[i][j].vx=0;
				point[i][j].vy=0;
				point[i][j].vz=0;
			}
		}

		point[i][j].x0=point[i][j].x;
		point[i][j].y0=point[i][j].y;
		point[i][j].z0=point[i][j].z;

		point[i][j].x= point[i][j].x + dt*point[i][j].vx;
		point[i][j].y= point[i][j].y + dt*point[i][j].vy;
		point[i][j].z= point[i][j].z + dt*point[i][j].vz;



	}
}

/*checkspringdeformation(); */

if (collisions==TRUE)
checkcollisions();


}


void drawobjects(void){
int i;
GLfloat amb[]={
	.5,.5,.5,1};
GLfloat diff[]={
	.5,.5,.5,1};

glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);


for (i=0;i<Triangles_per_Box;i++){
	glBegin(GL_POLYGON);
	glNormal3f(triangle[i].nx,triangle[i].ny,triangle[i].nz);
	glVertex3f(triangle[i].Ax,triangle[i].Ay,triangle[i].Az);
	glVertex3f(triangle[i].Bx,triangle[i].By,triangle[i].Bz);
	glVertex3f(triangle[i].Cx,triangle[i].Cy,triangle[i].Cz);
	glEnd();
}





}

void initializepoints(void){

int i,j;

for (i=0;i<mpoints;i++){
	for (j=0;j<npoints;j++){
		point[i][j].x=j-4;
		point[i][j].y=8;
		point[i][j].z=i-4;
		point[i][j].x0=0;
		point[i][j].y0=0;
		point[i][j].z0=0;
		point[i][j].vx=0;
		point[i][j].vy=0;
		point[i][j].vz=0;
		point[i][j].mass=1;
		point[i][j].Fintx=0;
		point[i][j].Finty=0;
		point[i][j].Fintz=0;
		point[i][j].Fextx=0;
		point[i][j].Fexty=0;
		point[i][j].Fextz=0;

	}
}


}



void initobjects(void){


triangle[0].Ax=-2;
triangle[0].Ay=0;
triangle[0].Az=2;
triangle[0].Bx=2;
triangle[0].By=0;
triangle[0].Bz=2;
triangle[0].Cx=-2;
triangle[0].Cy=0;
triangle[0].Cz=-2;
triangle[0].nx=0;
triangle[0].ny=1;
triangle[0].nz=0;

triangle[1].Ax=-2;
triangle[1].Ay=0;
triangle[1].Az=-2;
triangle[1].Bx=2;
triangle[1].By=0;
triangle[1].Bz=2;
triangle[1].Cx=2;
triangle[1].Cy=0;
triangle[1].Cz=-2;
triangle[1].nx=0;
triangle[1].ny=1;
triangle[1].nz=0;


triangle[2].Ax=-2;
triangle[2].Ay=-1;
triangle[2].Az=2;
triangle[2].Bx=2;
triangle[2].By=-1;
triangle[2].Bz=2;
triangle[2].Cx=-2;
triangle[2].Cy=-1;
triangle[2].Cz=-2;
triangle[2].nx=0;
triangle[2].ny=-1;
triangle[2].nz=0;

triangle[3].Ax=-2;
triangle[3].Ay=-1;
triangle[3].Az=-2;
triangle[3].Bx=2;
triangle[3].By=-1;
triangle[3].Bz=2;
triangle[3].Cx=2;
triangle[3].Cy=-1;
triangle[3].Cz=-2;
triangle[3].nx=0;
triangle[3].ny=-1;
triangle[3].nz=0;


triangle[4].Ax=-2;
triangle[4].Ay=-1;
triangle[4].Az=2;
triangle[4].Bx=2;
triangle[4].By=0;
triangle[4].Bz=2;
triangle[4].Cx=-2;
triangle[4].Cy=0;
triangle[4].Cz=2;
triangle[4].nx=0;
triangle[4].ny=0;
triangle[4].nz=1;

triangle[5].Ax=-2;
triangle[5].Ay=-1;
triangle[5].Az=2;
triangle[5].Bx=2;
triangle[5].By=-1;
triangle[5].Bz=2;
triangle[5].Cx=2;
triangle[5].Cy=0;
triangle[5].Cz=2;
triangle[5].nx=0;
triangle[5].ny=0;
triangle[5].nz=1;

triangle[6].Ax=2;
triangle[6].Ay=0;
triangle[6].Az=2;
triangle[6].Bx=-2;
triangle[6].By=-1;
triangle[6].Bz=2;
triangle[6].Cx=-2;
triangle[6].Cy=0;
triangle[6].Cz=2;
triangle[6].nx=0;
triangle[6].ny=0;
triangle[6].nz=-1;

triangle[7].Ax=2;
triangle[7].Ay=-1;
triangle[7].Az=2;
triangle[7].Bx=-2;
triangle[7].By=-1;
triangle[7].Bz=2;
triangle[7].Cx=2;
triangle[7].Cy=0;
triangle[7].Cz=2;
triangle[7].nx=0;
triangle[7].ny=0;
triangle[7].nz=-1;

triangle[8].Ax=-2;
triangle[8].Ay=-1;
triangle[8].Az=-2;
triangle[8].Bx=-2;
triangle[8].By=0;
triangle[8].Bz=2;
triangle[8].Cx=-2;
triangle[8].Cy=0;
triangle[8].Cz=-2;
triangle[8].nx=-1;
triangle[8].ny=0;
triangle[8].nz=0;

triangle[9].Ax=-2;
triangle[9].Ay=-1;
triangle[9].Az=-2;
triangle[9].Bx=-2;
triangle[9].By=-1;
triangle[9].Bz=2;
triangle[9].Cx=-2;
triangle[9].Cy=0;
triangle[9].Cz=2;
triangle[9].nx=-1;
triangle[9].ny=0;
triangle[9].nz=0;

triangle[10].Ax=2;
triangle[10].Ay=0;
triangle[10].Az=2;
triangle[10].Bx=2;
triangle[10].By=-1;
triangle[10].Bz=-2;
triangle[10].Cx=2;
triangle[10].Cy=0;
triangle[10].Cz=-2;
triangle[10].nx=1;
triangle[10].ny=0;
triangle[10].nz=0;

triangle[11].Ax=2;
triangle[11].Ay=-1;
triangle[11].Az=2;
triangle[11].Bx=2;
triangle[11].By=-1;
triangle[11].Bz=-2;
triangle[11].Cx=2;
triangle[11].Cy=0;
triangle[11].Cz=2;
triangle[11].nx=1;
triangle[11].ny=0;
triangle[11].nz=0;





}


/*-----------------------------------------------------------------------------------------
handle X idle events this is the main display routine which 
sets up the camera and draws the current curve
-------------------------------------------------------------------------------------------*/
int
idle_cb(XEvent *ev, void *data)
{ 	
int i,j;
static GLfloat xrot, yrot, zrot;
if(!ui->form->visible  || ! ui->canvas->visible)
return 0;

glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glPushMatrix();		

/*  set up camera */
gluLookAt(copx, copy, copz,	/* eye is at (0,0,10) */
vrpx, vrpy, vrpz,	/* center is at (0,0,0) */
0, 1, 0);	/* up is in positive Y direction */

if (play==TRUE||nextframe==TRUE){
	calculatenewpoints();
	frame+=1;
	nextframe=FALSE;
}


drawcloth();
if (hideobjects==FALSE)
drawobjects();





glPopMatrix();
glFinish();
glXSwapBuffers(fl_display, fl_get_canvas_id(ui->canvas));
return 0;
}



/*-----------------------------------------------------------------------------------------
initialize the the light source,light color, camera position, 
-------------------------------------------------------------------------------------------*/
void init(void){

GLfloat ambient[] = { 
	0.2, 0.2, 0.2, 1.0 	};
GLfloat position[] = { 
	0, 0, -10, 1 	};
GLfloat mat_diffuse[] = { 
	0, 1, 0, 1.0 	};
GLfloat mat_specular[] = { 
	1.0, 1.0, 1.0, 1.0 	};
GLfloat mat_shininess[] = { 
	50.0 	};

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
glLightfv(GL_LIGHT0, GL_POSITION, position);

glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);


initializepoints();
initobjects();
fl_set_input(ui->StructK,"4.00");
fl_set_input(ui->ShearK,"0.00");
fl_set_input(ui->FlexK,"0.00");
fl_set_input(ui->VertexMass,"0.1");	
fl_set_input(ui->gravityx,"0.0");
fl_set_input(ui->gravityy,"-9.8");
fl_set_input(ui->gravityz,"0.0");
fl_set_input(ui->windx,"0.0");
fl_set_input(ui->windy,"0.0");
fl_set_input(ui->windz,"0.0");
fl_set_input(ui->Damping,"0.0");
fl_set_input(ui->Viscous,"0.0");
fl_set_input(ui->CameraX,"0.0");
fl_set_input(ui->CameraY,"70.0");	
fl_set_input(ui->CameraZ,"10.0");
fl_set_input(ui->TimeStep,"0.1");
fl_set_button(ui->Collision_button,1);
fl_set_button(ui->ShowClothMesh,1);
fl_set_button(ui->Stop_button,1);



}



/*-----------------------------------------------------------------------------------------
set up the viewport and modelling and projection matrices
-------------------------------------------------------------------------------------------*/
int
canvas_expose(FL_OBJECT *ob, Window win, int w, int h, XEvent *xev, void *ud)
{

glViewport(0,0, (GLint)w, (GLint)h);
glClearColor(0.0,0.0,0.0,0.0);
glEnable(GL_DEPTH_TEST);
init();
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluPerspective( 30.0,1.0,1.0,1000);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glShadeModel( GL_SMOOTH );

/* refresh */
idle_cb(xev, 0);
return 0;
}


/*-----------------------------------------------------------------------------------------
initilize the windows and xforms for rendering
call the display routines and 
-------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

FL_OBJECT *ob;
static int dbuf[] = {
	GLX_RGBA,GLX_DEPTH_SIZE,1,GLX_RED_SIZE,1,GLX_GREEN_SIZE,  
	1,GLX_BLUE_SIZE,1,GLX_DOUBLEBUFFER,None	};


fl_initialize(&argc, argv, "FormDemo", 0, 0);
ui = create_form_form();

/* fill-in form initialization code */
/*fl_set_glcanvas_attributes(ui->canvas,dbuf);*/
fl_add_canvas_handler(ui->canvas, Expose, canvas_expose, 0);
fl_set_idle_callback(idle_cb, 0);


/* geometry stuff */
fl_set_form_minsize(ui->form, 340, 280);

fl_show_form(ui->form,FL_PLACE_CENTER|FL_FREE_SIZE,FL_FULLBORDER,
"OpenGL Canvas");



while ((ob=fl_do_forms()) !=ui->quit_button )
;
return 0;
}





