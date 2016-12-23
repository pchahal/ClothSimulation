/*-----------------------------------------------------------------------------------------
Pardeep Chahal
CMPT 461
Assignment 1 :  Curve Editor
-------------------------------------------------------------------------------------------*/
				
#include <stdlib.h>

#include "matrices.h"			/* curve basis matrices */
#include "cube.c"			
					
#define unrbs 3
#define N 4


					/* declaration */


int current_controlpoint=1;		/* selected control point */
int controlpoint_row=0;
int controlpoint_col=0;

float xrotation=180;
float yrotation=0;
float zrotation=0;





					/* function prototypes */
void set_default_control_points(void);
void convert_to_unrbs(void);


	
	
	   




/*-----------------------------------------------------------------------------------------
set the control points of the current curve to the appropriate default control 
points
-------------------------------------------------------------------------------------------*/
void set_default_control_points(void){
	int i,j,k;

		for (i=0;i<8;i++)
			for(j=0;j<4;j++)
				for(k=0;k<3;k++)
					ctrlpoints[i][j][k]=unrbs_default[i][j][k];
}



/*-----------------------------------------------------------------------------------------
draw the control points for the bezier curve.
each control point is drawn as a cube with the selected one in a different color
-------------------------------------------------------------------------------------------*/
void draw_controlpoints_bezier(void){
	GLfloat mat_diffuse[] = { 
		1, 0, 0, 1.0 	};
	int i,j;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	for (i=0;i<8;i++){
		for (j=0;j<4;j++){
			glPushMatrix();
			glTranslatef(ctrlpoints[i][j][0],ctrlpoints[i][j][1],ctrlpoints[i][j][2]);
			draw_cube();
			glPopMatrix();
		}
	}


	/* highlight the selected control point  */
	mat_diffuse[0]= 0;
	mat_diffuse[1]=1;
	mat_diffuse[2]=0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	glTranslatef(ctrlpoints[controlpoint_row][controlpoint_col][0],
	    ctrlpoints[controlpoint_row][controlpoint_col][1],
	    ctrlpoints[controlpoint_row][controlpoint_col][2]);
	glScalef(1.1,1.1,1.1);
	draw_cube();
	glPopMatrix();

}



/*-----------------------------------------------------------------------------------------
build the unrbs geometry matrix for the given patch
for each the x,y,z components
-------------------------------------------------------------------------------------------*/
void set_unrbs_geometry_vector(int patch){
	int i,j;

	for (i=0;i<N;i++){
		for(j=0;j<N;j++){
			Gbsx[i][j]=ctrlpoints[i+patch][j][0];
			Gbsy[i][j]=ctrlpoints[i+patch][j][1];
			Gbsz[i][j]=ctrlpoints[i+patch][j][2];
		}
	}
}


/*-----------------------------------------------------------------------------------------
set the unrbs control points from the newly calculated bezier geometry
for the given patch
-------------------------------------------------------------------------------------------*/
void set_control_points_from_unrbs_geometry(int patch){
	int i,j;

	
		for (i=0;i<N;i++){
			for(j=0;j<N;j++){
				unrbspline[i+patch*4][j][0]=Gbx[i][j];
				unrbspline[i+patch*4][j][1]=Gby[i][j];
				unrbspline[i+patch*4][j][2]=Gbz[i][j];
			}
		}
	


}



/*-----------------------------------------------------------------------------------------
convert the unrbs geometry to the equivalent bezier geometry for each of the 5 patches
for each the x,y,z components
Using the equation to convert between representations.
-------------------------------------------------------------------------------------------*/
void convert_to_unrbs(void){
	int i,j,k;
	GLfloat temp[4][4];
	int patches;
						/* for patch 1 to 5 */
	for (patches=0;patches<=4;patches++){


		set_unrbs_geometry_vector(patches);

		initializematrix(Gbx);
		initializematrix(Gby);
		initializematrix(Gbz);

		multiply(Gbx,Mb_1,Mbs);			/* x component */
		copymatrix(Gbx,temp);
		multiply(Gbx,temp,Gbsx);
		copymatrix(Gbx,temp);
		multiply(Gbx,temp,MbsT);
		copymatrix(Gbx,temp);
		multiply(Gbx,temp,MbT_1);

		multiply(Gby,Mb_1,Mbs);			/* y component */
		copymatrix(Gby,temp);
		multiply(Gby,temp,Gbsy);
		copymatrix(Gby,temp);
		multiply(Gby,temp,MbsT);
		copymatrix(Gby,temp);
		multiply(Gby,temp,MbT_1);

		multiply(Gbz,Mb_1,Mbs);			/* z component */
		copymatrix(Gbz,temp);
		multiply(Gbz,temp,Gbsz);
		copymatrix(Gbz,temp);
		multiply(Gbz,temp,MbsT);
		copymatrix(Gbz,temp);
		multiply(Gbz,temp,MbT_1);

		set_control_points_from_unrbs_geometry(patches);

	}

}


/*-----------------------------------------------------------------------------------------
draw the unrbs patches as a bezier curve from the converted unrbs
geometry using the bezier evaluator function
-------------------------------------------------------------------------------------------*/
void draw_unrbs(void){
	int i,j;
	int patches=5;
	GLfloat mat_diffuse[] = { 
		1, 1, 0.2, 1.0 	};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	/* draw curve1 */



	for (i=0;i<patches;i++){
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
	    0, 1, 12, 4, &unrbspline[i*4][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    }

}



   


	

		 
			
