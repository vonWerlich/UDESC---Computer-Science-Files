#include <GL/glut.h>
  
// Rotation
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
        
    if(key == GLUT_KEY_UP)
        zRot += 5.0f;
    
    if(key == GLUT_KEY_DOWN)
        zRot -= 5.0f;
                  
    yRot = (GLfloat)((const int)yRot % 360);  
    zRot = (GLfloat)((const int)zRot % 360);
  
    // Refresh the Window  
    glutPostRedisplay();  
}

typedef struct ponto
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}Ponto;

void DrawParallelepiped(Ponto p1, Ponto p2, Ponto p3, Ponto p4, Ponto p5, Ponto p6, 
						Ponto p7, Ponto p8){
	//			5----6
	//          |  1----2
	//          7--|-8  |
	//             3----4

    glBegin(GL_POLYGON);
    // FRONT
    glColor3f(1.0f, 0.4f, 0.5f);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();/*
	glBegin(GL_POLYGON);
	// BACK
	glColor3f(0.0f, 0.4f, 0.5f);
	glVertex3f(p5.x, p5.y, p5.z);
	glVertex3f(p6.x, p6.y, p6.z);
	glVertex3f(p8.x, p8.y, p8.z);
	glVertex3f(p7.x, p7.y, p7.z);
	glEnd();
	glBegin(GL_POLYGON);
	// LEFT
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p7.x, p7.y, p7.z);
	glVertex3f(p5.x, p5.y, p5.z);
	glEnd();
	glBegin(GL_POLYGON);
	// RIGHT
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p8.x, p8.y, p8.z);
	glVertex3f(p6.x, p6.y, p6.z);
	glEnd();
	glBegin(GL_POLYGON);
	// TOP
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p6.x, p6.y, p6.z);
	glVertex3f(p5.x, p5.y, p5.z);
	glEnd();
	glBegin(GL_POLYGON);
	// BOTTOM
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p8.x, p8.y, p8.z);	
	glVertex3f(p7.x, p7.y, p7.z);
    glEnd();*/
}
  
// Called to draw scene  
void RenderScene(void){  

    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  
	glRotatef(zRot, 1.0f, 0.0f, 0.0f);


	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// white
	glColor3f(1.0f, 1.0f, 1.0f);  


	/*glBegin(GL_POLYGON);
	//glVertex3f = (horizontal, vertical, profundidade)
	glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  1.0, -0.5, -0.5 );      // P1 is red
	glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  1.0,  0.5, -0.5 );      // P2 is green
	glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -1.0,  0.5, -0.5 );      // P3 is blue
	glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -1.0, -0.5, -0.5 );      // P4 is purple

	glEnd();*/
	Ponto p1; p1.x = -1.0f; p1.y = 1.0f; p1.z = 1.0f;
	Ponto p2; p2.x = 1.0f; p2.y = 1.0f; p2.z = 1.0f;
	Ponto p3; p3.x = -1.0f; p3.y = -1.0f; p3.z = 1.0f;
	Ponto p4; p4.x = 1.0f; p4.y = -1.0f; p4.z = 1.0f;
	Ponto p5; p5.x = -1.0f; p5.y = 1.0f; p5.z = -1.0f;
	Ponto p6; p6.x = 1.0f; p6.y = 1.0f; p6.z = -1.0f;
	Ponto p7; p7.x = -1.0f; p7.y = -1.0f; p7.z = -1.0f;
	Ponto p8; p8.x = 1.0f; p8.y = -1.0f; p8.z = -1.0f;
	
	//DrawParallelepiped(p1, p2, p3, p4, p5, p6, p7, p8);
	glFlush();
	glBegin(GL_QUADS);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
	
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Castelo");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}

