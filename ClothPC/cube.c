
/* draw a unit cube centered at the origin */
void draw_cube(void){


	glPushMatrix();

	glScalef(.05,.05,.05);
	glNormal3f(1,0,0);
	glBegin( GL_POLYGON );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 1.0, -1.0, 1.0 );
	glVertex3f( 1.0, -1.0, -1.0 );
	glVertex3f( 1.0, 1.0, -1.0 );
	glEnd();

	glNormal3f(-1,0,0);
	glBegin( GL_POLYGON);
	glVertex3f( -1.0, 1.0, 1.0 );
	glVertex3f( -1.0, 1.0, -1.0 );
	glVertex3f( -1.0, -1.0, -1.0 );
	glVertex3f( -1.0, -1.0, 1.0 );
	glEnd();

	/* Y faces */

	glNormal3f(0,1,0);
	glBegin( GL_POLYGON);
	glVertex3f(  1.0, 1.0,  1.0 );
	glVertex3f(  1.0, 1.0, -1.0 );
	glVertex3f( -1.0, 1.0, -1.0 );
	glVertex3f( -1.0, 1.0,  1.0 );
	glEnd();

	glNormal3f(0,-1,0);
	glBegin( GL_POLYGON);
	glVertex3f(  1.0, -1.0,  1.0 );
	glVertex3f( -1.0, -1.0,  1.0 );
	glVertex3f( -1.0, -1.0, -1.0 );
	glVertex3f(  1.0, -1.0, -1.0 );
	glEnd();

	/* Z faces */

	glNormal3f(0,0,1);
	glBegin( GL_POLYGON);
	glVertex3f(  1.0,  1.0,  1.0 );
	glVertex3f( -1.0,  1.0,  1.0 );
	glVertex3f( -1.0, -1.0,  1.0 );
	glVertex3f(  1.0, -1.0,  1.0 );
	glEnd();

	glNormal3f(0,0,-1);
	glBegin( GL_POLYGON);
	glVertex3f(  1.0, 1.0, -1.0 );
	glVertex3f(  1.0,-1.0, -1.0 );
	glVertex3f( -1.0,-1.0, -1.0 );
	glVertex3f( -1.0, 1.0, -1.0 );
	glEnd();

	glPopMatrix();

}

