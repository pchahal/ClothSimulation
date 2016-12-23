
#define X .525731112119133606
#define Z .850650808352039932

static double vdata[12][3]={
{-X,0.0,Z},{X,0.0,Z},{-X,0.0,-Z},{X,0.0,Z},
{0.0,Z,X},{0.0,Z,-X},{0.0,-Z, X},{0.0,-Z,-X},
{Z,X,0.0},{-Z,X,0.0},{Z,-X,0.0 },{-Z,-X,0.0}
};

static int tindices[20][3]={

{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}};

float rot=0;
void normalizevector(float v[3]){
 GLfloat d=sqrt(v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
 if (d==0.0)
 	return;

 v[1]/=d;v[2]/=d;v[3]/=d;

}


void normcrossprod(float v1[3],float v2[3],float out[3]){
 
 int i,j;

 float length;

 out[0]=v1[1]*v2[2]-v1[2]*v2[1];
 out[1]=v1[2]*v2[0]-v1[0]*v2[2];
 out[2]=v1[0]*v2[1]-v1[1]*v2[0];
 normalizevector(out);

}

void drawtriangle(float v1[3],float v2[3],float v3[3]){
   glBegin(GL_POLYGON);
   glNormal3fv(v1);
   glVertex3fv(v1);
   glNormal3fv(v2);
   glVertex3fv(v2);
   glNormal3fv(v3);
   glVertex3fv(v3);
   glEnd();

}


void subdivide(float v1[3],float v2[3],float v3[3]){
 float v12[3],v23[3],v31[3];
 int i;

 for (i=0;i<3;i++){
 	v12[i]=v1[i]+v2[i];
	v23[i]=v2[i]+v3[i];
	v31[i]=v3[i]+v1[i];

 }

 normalizevector(v12);
 normalizevector(v23);
 normalizevector(v31);
 drawtriangle(v1,v12,v31);
 drawtriangle(v2,v23,v12);
 drawtriangle(v3,v23,v31);
 drawtriangle(v12,v23,v31);


}

void draw(void){
int i,j;
  float d1[3],d2[3],norm[3];
  for (i=0;i<20;i++){
  /* 
  
   subdivide(&vdata[tindices[0][0]][0],
    	&vdata[tindices[0][1]][0],
    	&vdata[tindices[0][2]][0]);
*/	
	 

  
   triangle[i].Ax=vdata[tindices[i][0]][0];
   triangle[i].Ay=vdata[tindices[i][0]][1];
   triangle[i].Az=vdata[tindices[i][0]][2];
   triangle[i].Bx=vdata[tindices[i][1]][0];
   triangle[i].By=vdata[tindices[i][1]][1];
   triangle[i].Bz=vdata[tindices[i][1]][2];
   triangle[i].Cx=vdata[tindices[i][2]][0];
   triangle[i].Cy=vdata[tindices[i][2]][1];
   triangle[i].Cz=vdata[tindices[i][2]][2];
   triangle[i].nx=vdata[tindices[i][2]][2];
   for (j=0;j<3;j++){
   	d1[j]=vdata[tindices[i][1]][j]-vdata[tindices[i][2]][j];
   	d2[j]=vdata[tindices[i][0]][j]-vdata[tindices[i][1]][j];
   }
   
   normcrossprod(d1,d2,norm);
   triangle[i].nx=norm[0];
   triangle[i].ny=norm[1];
   triangle[i].nz=norm[2];
   
   
   /*	
   glBegin(GL_POLYGON);
   glNormal3fv(&vdata[tindices[k][0]][0]);
   glVertex3fv(&vdata[tindices[k][0]][0]);
   glNormal3fv(&vdata[tindices[k][1]][0]);
   glVertex3fv(&vdata[tindices[k][1]][0]);
   glNormal3fv(&vdata[tindices[k][2]][0]);
   glVertex3fv(&vdata[tindices[k][2]][0]);
   glEnd();
  	 */
  }	
  		
}	  

