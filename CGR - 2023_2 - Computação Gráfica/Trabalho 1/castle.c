//Trabalho Complementar 1 (TC1) - Kauan Henrique Werlich - Computação Gráfica

// comando para rodar em Linux:
// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman
// No Windows a vida é mais complicada

#include <GL/glut.h>
  
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
   
    if(h == 0)  
        h = 1;  
   
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);   // Hidden surface removal  
    glFrontFace(GL_CCW);    // Counter clock-wise polygons face out  
    //glEnable(GL_CULL_FACE);  // adicionar pontos no sentido horário põe a figura na frente
  
    // Enable lighting  
    glEnable(GL_LIGHTING)
  
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

void paralepipedo(GLfloat x, GLfloat y, GLfloat z,
						GLfloat length, GLfloat height, GLfloat width){
							
	glColor3f(0.6f, 0.6f, 0.6f);//color
	
	// FRONT
    glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
	// BACK
	glBegin(GL_POLYGON);	
	glRotated(180, 1, 0, 0);
	glVertex3f(x, y, z - width);
	glVertex3f(x + length, y, z - width);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x, y + height, z - width);
	glEnd();
	// LEFT
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y + height, z);
	glVertex3f(x, y + height, z - width);
	glVertex3f(x, y, z - width);
	glEnd();
	// RIGHT
	glBegin(GL_POLYGON);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x + length, y, z - width);
	glEnd();
	// TOP
	glBegin(GL_POLYGON);
	glVertex3f(x, y + height, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x , y + height, z - width);
	glEnd();
	// BOTTOM
	glBegin(GL_POLYGON);	
	glVertex3f(x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z - width);	
	glVertex3f(x + length, y, z - width);
    glEnd();
}

void paralepipedo2(GLfloat x, GLfloat y, GLfloat z,
						GLfloat length, GLfloat height, GLfloat width, 
						GLfloat a, GLfloat b, GLfloat c){
							
	glColor3f(a, b, c);//color
	
	// FRONT
    glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
	// BACK
	glBegin(GL_POLYGON);	
	glRotated(180, 1, 0, 0);
	glVertex3f(x, y, z - width);
	glVertex3f(x + length, y, z - width);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x, y + height, z - width);
	glEnd();
	// LEFT
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y + height, z);
	glVertex3f(x, y + height, z - width);
	glVertex3f(x, y, z - width);
	glEnd();
	// RIGHT
	glBegin(GL_POLYGON);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x + length, y, z - width);
	glEnd();
	// TOP
	glBegin(GL_POLYGON);
	glVertex3f(x, y + height, z);
	glVertex3f(x + length, y + height, z);
	glVertex3f(x + length, y + height, z - width);
	glVertex3f(x , y + height, z - width);
	glEnd();
	// BOTTOM
	glBegin(GL_POLYGON);	
	glVertex3f(x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z - width);	
	glVertex3f(x + length, y, z - width);
    glEnd();
}
  
void RenderScene(void){  

    GLUquadricObj *pObj; // Quadric Object  
      
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

	//floor
	//paralepipedo2(-5.0f, -5.0f, 5.0f, 10.0, 5.0, 10.0, 0, 1, 0);//chao sem fosso
	paralepipedo2(-5.0f, -5.0f, 5.0f, 10.0, 5.0, 4.0, 0, 1, 0);
	paralepipedo2(-5.0f, -5.0f, 5.0f, 3.5f, 5.0, 10.0, 0, 1, 0);
	paralepipedo2(1.9f, -5.0f, 5.0f, 3.5f, 5.0, 10.0, 0, 1, 0);
	paralepipedo2(-5.0, -5.0f, -2.0f, 10.0f, 5.0, 10.0, 0, 1, 0);
	paralepipedo2(-1.5, -5.0f, 1.0f, 4.0f, 4.9, 4.0, 0, 0, 1); //fosso
	paralepipedo2(-1.2, -5.0f, 0.7f, 2.6f, 5.0, 2.4, 0, 1, 0);
	
	//right wall
	paralepipedo(-1.0f, 0.0f, 0.5f, 0.2f, 0.5f, 2.0f);
	//left wall
	paralepipedo(1.0f, 0.0f, 0.5f, 0.2f, 0.5f, 2.0f);
	//back wall
	paralepipedo(-1.0f, 0.0f, -1.3f, 2.0f, 0.5f, 0.2f);
	//front wall
	paralepipedo(-0.8f, 0.0f, 0.5f, 0.7f, 0.5f, 0.2f);
	paralepipedo(0.3f, 0.0f, 0.5f, 0.7f, 0.5f, 0.2f);
	paralepipedo(-0.1f, 0.3f, 0.5f, 0.4f, 0.2f, 0.2f);
	
	//front right tower
	//gluCylinder(*qobj, baseRadius, topRadius, height, slices, stacks)
	glColor3f(0.65f, 0.65f, 0.65f);
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.0f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.3f, 0.3f, 0.7, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.7f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluDisk(pObj, 0.0f, 0.35f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.7f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.35f, 0.0f, 0.4, 26, 13);
	glPopMatrix();
	
	//back rigth tower
	glColor3f(0.65f, 0.65f, 0.65f);
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.0f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.3f, 0.3f, 0.7, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.7f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluDisk(pObj, 0.0f, 0.35f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix(); 
	glTranslatef(-0.9f, 0.7f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.35f, 0.0f, 0.4, 26, 13);
	glPopMatrix();
	
	//front left tower
	glColor3f(0.65f, 0.65f, 0.65f);
	glPushMatrix(); 
	glTranslatef(1.1f, 0.0f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.3f, 0.3f, 0.7, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(1.1f, 0.7f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluDisk(pObj, 0.0f, 0.35f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix(); 
	glTranslatef(1.1f, 0.7f, 0.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.35f, 0.0f, 0.4, 26, 13);
	glPopMatrix();
	
	//back left tower
	glColor3f(0.65f, 0.65f, 0.65f);
	glPushMatrix(); 
	glTranslatef(1.1f, 0.0f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.3f, 0.3f, 0.7, 26, 13);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(1.1f, 0.7f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluDisk(pObj, 0.0f, 0.35f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix(); 
	glTranslatef(1.1f, 0.7f, -1.4f);
	glRotated(-90, 1, 0, 0);
	gluCylinder(pObj, 0.35f, 0.0f, 0.4, 26, 13);
	glPopMatrix();
	
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

