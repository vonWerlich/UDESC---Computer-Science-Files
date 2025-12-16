//Trabalho Complementar 1 (TC1) - Kauan Henrique Werlich - Computação Gráfica

// comando para rodar em Linux:
// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman
// No Windows a vida é mais complicada

#include <GL/glut.h>
  
// Rotation
static GLfloat xRot = 0.00f;
static GLfloat yRot = 0.00f;

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
        xRot += 5.0f;
    
    if(key == GLUT_KEY_DOWN)
        xRot -= 5.0f;
                  
    yRot = (GLfloat)((const int)yRot % 360);  
    xRot = (GLfloat)((const int)xRot % 360);

  
    // Refresh the Window  
    glutPostRedisplay();  
}
  
// Called to draw scene  
void RenderScene(void){  

	// Quadric Object 
    GLUquadricObj *pObj;     
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	glColor3f(1.0f, 1.0f, 1.0f);  // white
	
	// Head
	glPushMatrix(); // save transform matrix state
	glTranslatef(0.0f, 1.25f, 0.5f); //posição (x,y,z) = (horizontal, vertical, profundidade)
	gluSphere(pObj, 0.25f, 26, 13);
	glPopMatrix(); // restore transform matrix state
	
	//  Mid section
	glPushMatrix(); 
	glTranslatef(0.0f, 0.75f, 0.5f);
	gluSphere(pObj, 0.3f, 26, 13);
	glPopMatrix(); // restore transform matrix state
	
	glColor3f(0.0f,0.0f,1.0f); //blue
	
	// buttons
	glPushMatrix(); 
	glTranslatef(0.0f, 0.9f, 0.75f);
	gluSphere(pObj, 0.035f, 13, 7);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.0f, 0.7f, 0.78f);
	gluSphere(pObj, 0.035f, 13, 7);
	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);  // white
	// Bottom
	glPushMatrix(); 
	glTranslatef(0.0f, 0.25f, 0.5f);
	gluSphere(pObj, 0.35f, 26, 13);
	glPopMatrix(); // restore transform matrix state
	
	// Nose (orange)
	glColor3f(1.0f, 0.4f, 0.5f);  
	glPushMatrix();
	glTranslatef(0.0f, 1.25f, 0.7f);
	gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);  
	glPopMatrix();  
	
	glColor3f(0.0f,0.0f,0.0f); //black
	
	// Left eye
	glPushMatrix(); 
	glTranslatef(-0.1f, 1.3f, 0.7f);
	gluSphere(pObj, 0.035f, 13, 7);
	glPopMatrix();
	
	// Right eye
	glPushMatrix(); 
	glTranslatef(0.1f, 1.3f, 0.7f);
	gluSphere(pObj, 0.035f, 13, 7);
	glPopMatrix();

	// Hat Brim
	glPushMatrix(); 
	glTranslatef(0.0f, 1.48f, 0.5f);
	glRotated(90, 1, 0, 0);
	gluCylinder(pObj, 0.25f, 0.25f, 0.03, 26, 13);
	//gluCylinder(*qobj, baseRadius, topRadius, height, slices, stacks)
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.0f, 1.48f, 0.5f);
	glRotated(90, 1, 0, 0);
	gluDisk(pObj, 0.0, 0.25, 26, 13);
	//gluDisk(*qobj, innerRadius, outerRadius, slices, loops);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.0f, 1.45f, 0.5f);
	glRotated(270, 1, 0, 0);
	gluDisk(pObj, 0.0, 0.25, 26, 13);
	glPopMatrix();
	
	// Hat Top
	glPushMatrix(); 
	glTranslatef(0.0f, 1.46f, 0.5f);
	glRotated(270, 1, 0, 0);
	gluCylinder(pObj, 0.17f, 0.17f, 0.3, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.0f, 1.76f, 0.5f);
	glRotated(270, 1, 0, 0);
	gluDisk(pObj, 0.0, 0.17, 26, 13);
	glPopMatrix();
      
	//arms
	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix(); 
	glTranslatef(0.0f, 0.90f, 0.5f);
	glRotated(90, 0, 1, 0);
	glRotated(5, 1, 0, 0);
	gluCylinder(pObj, 0.04f, 0.02f, 0.75, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.0f, 0.90f, 0.5f);
	glRotated(270, 0, 1, 0);
	glRotated(5, 1, 0, 0);
	gluCylinder(pObj, 0.04f, 0.02f, 0.75, 26, 13);
	glPopMatrix();
	
	//right fingers
	glPushMatrix(); 
	glTranslatef(0.7f, 0.85f, 0.5f);
	glRotated(90, 0, 1, 0);
	glRotated(30, 1, 0, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.7f, 0.85f, 0.5f);
	glRotated(90, 0, 1, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.7f, 0.85f, 0.5f);
	glRotated(90, 0, 1, 0);
	glRotated(-30, 1, 0, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	
	//left fingers
	glPushMatrix(); 
	glTranslatef(-0.7f, 0.85f, 0.5f);
	glRotated(-90, 0, 1, 0);
	glRotated(30, 1, 0, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-0.7f, 0.85f, 0.5f);
	glRotated(-90, 0, 1, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-0.7f, 0.85f, 0.5f);
	glRotated(-90, 0, 1, 0);
	glRotated(-30, 1, 0, 0);
	gluCylinder(pObj, 0.02f, 0.0f, 0.15, 26, 13);
	glPopMatrix();
	    
    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Snowman");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}

