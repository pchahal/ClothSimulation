/*   routines for matrix operations   */


/*******************************************************************
 * multiply two matrices   a= b x c   b is 4x1   c is 4x4
 ******************************************************************/
void multiply2(double a[],double b[],double c[][4])
{
	int i,j,k;

	for (j=0;j<4; ++j){
		a[j]=0.0;
		for (k=0; k< 4; ++k)
			a[j] += b[k] * c[k][j];
	}
}




/*******************************************************************
 * multiply two 4x4 matrices   a= b x c    
 ******************************************************************/
void multiply(GLfloat a[4][4],GLfloat b[4][4],GLfloat c[4][4])
{
	int i,j,k;

	for (i=0;i<4;++i)
		for (j=0;j<4; ++j){
			a[i][j]=0.0;
			for (k=0; k< 4; ++k)
				a[i][j] += b[i][k] * c[k][j];
		}
}





/*-----------------------------------------------------------------------------------------
initialize matrix to zero
-------------------------------------------------------------------------------------------*/
void initializematrix(GLfloat a[4][4]){
	int i,j;


	for (i=0;i<4;i++)
		for(j=0;j<4;j++)
			a[i][j]=0;

}

/*-----------------------------------------------------------------------------------------
copy matrix a to b
-------------------------------------------------------------------------------------------*/
void copymatrix(GLfloat a[4][4],GLfloat b[4][4]){
	int i,j;


	for (i=0;i<4;i++)
		for(j=0;j<4;j++)
			b[i][j]=a[i][j];




}



/*******************************************************************
 * dot product of two vectors  (x1,x2,x3,x4)*(y1,y2,y3,y4)
 ******************************************************************/
double dotproduct4(double x1,double x2,double x3,double x4,
double y1,double y2,double y3,double y4){
	double sum=0;

	return sum= x1*y1+ x2*y2 + x3*y3 + x4 * y4;
}


/*******************************************************************
 * dot product of two vectors  (x1,x2,x3)*(y1,y2,y3)
 ******************************************************************/
double dotproduct3(double x1,double x2,double x3,
double y1,double y2,double y3){
	double sum=0;

	return sum= x1*y1+ x2*y2 + x3*y3;
}



/*******************************************************************
 * cross product of two vectors       a = b X c        in R3
 ******************************************************************/
void cross(double b1,double b2,double b3,double c1,double c2,double c3,
double *a1,double *a2,double *a3){

	*a1=b2*c3 - c2*b3;
	*a2=-1*(b1*c3 - c1*b3);
	*a3=b1*c2 - c1*b2;
}




/*******************************************************************
 *  normalize given vector   (x,y,z)
 ******************************************************************/
void normalized (double *x,double *y,double *z){
	double length;
	double a,b,c,sum;

	a=*x;
	b=*y;
	c=*z;
	sum= (a*a)+ (b*b) + (c*c);
	length=sqrt(sum);
	if (length!=0){
		*x=*x/length;
		*y=*y/length;
		*z=*z/length;
	}
}




/*******************************************************************
 *  multiply vector by scalar 
 ******************************************************************/
void ScalarMultiply (double s,double *x,double *y,double *z){

	*x=*x*s;
	*y=*y*s;
	*z=*z*s;
}
