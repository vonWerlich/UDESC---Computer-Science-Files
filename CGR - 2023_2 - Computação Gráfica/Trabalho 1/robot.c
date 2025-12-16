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
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    //glEnable(GL_CULL_FACE);     // adicionar pontos no sentido horário põe a figura na frente
  
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

void paralepipedoBottomUp (GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat height, GLfloat width) {
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

void paralepipedoTopDown (GLfloat x, GLfloat y, GLfloat z, GLfloat length,
						GLfloat height, GLfloat width, GLdouble anglex, GLdouble angley) {

	glPushMatrix();
	//glTranslatef(-x, -y, -z);
	//glTranslatef(x, y, z);
	glRotated(anglex, 1, 0, 0);
	glRotated(angley, 0, 1, 0);
	//glTranslatef(0, 0, 0);
	// FRONT
    glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y - height, z);
	glVertex3f(x, y - height, z);
	glEnd();
	// BACK
	glBegin(GL_POLYGON);	
	glRotated(180, 1, 0, 0);
	glVertex3f(x, y, z - width);
	glVertex3f(x + length, y, z - width);
	glVertex3f(x + length, y - height, z - width);
	glVertex3f(x, y - height, z - width);
	glEnd();
	// LEFT
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - height, z);
	glVertex3f(x, y - height, z - width);
	glVertex3f(x, y, z - width);
	glEnd();
	// RIGHT
	glBegin(GL_POLYGON);
	glVertex3f(x + length, y, z);
	glVertex3f(x + length, y - height, z);
	glVertex3f(x + length, y - height, z - width);
	glVertex3f(x + length, y, z - width);
	glEnd();
	// TOP
	glBegin(GL_POLYGON);
	glVertex3f(x, y - height, z);
	glVertex3f(x + length, y - height, z);
	glVertex3f(x + length, y - height, z - width);
	glVertex3f(x , y - height, z - width);
	glEnd();
	// BOTTOM
	glBegin(GL_POLYGON);	
	glVertex3f(x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x + length, y, z - width);	
	glVertex3f(x + length, y, z - width);
    glEnd();
    //glRotated(-anglex, 1, 0, 0);
	//glRotated(-angley, 0, 1, 0);
	glPopMatrix();
}

void desenhaCorpo(GLfloat x, GLfloat y, GLfloat z, GLdouble anglex, GLdouble angley) {
	glRotated(anglex, 1, 0, 0);
	glRotated(angley, 0, 1, 0);
	glColor3f(0.6f, 0.6f, 0.6f);//color
	
	//corpo
	GLfloat length = 0.8f;
	GLfloat height = 0.8f;
	GLfloat width = 0.4f;
	paralepipedoBottomUp(x, y, z, length, height, width);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	//pescoço
	length = 0.1f;
	height = 0.1f;
	width = 0.2f;
	paralepipedoBottomUp(x + 0.35, y + 0.8, z - 0.1, length, height, width);
	
	glColor3f(0.6f, 0.6f, 0.6f);//color
	//cabeça
	length = 0.7f;
	height = 0.4f;
	width = 0.4f;
	paralepipedoBottomUp(x + 0.05, y + 0.9, z, length, height, width);
	
	//ombros
	length = 0.2f;
	height = 0.2f;
	width = 0.4f;
	paralepipedoBottomUp(x - 0.2f, y + 0.6, z, length, height, width);//direito
	paralepipedoBottomUp(x + 0.8f, y + 0.6, z, length, height, width);//esquerdo
	
	//braços
	glColor3f(1.0f, 1.0f, 1.0f);
	length = 0.15f;
	height = 0.6f;
	width = 0.3f;
	paralepipedoTopDown(x - 0.2f, y + 0.6, z - 0.05, length, height, width, 0, 0);//direito
	paralepipedoTopDown(x + 0.85, y + 0.6, z - 0.05, length, height, width, 0, 0);//esquerdo

	//pernas
	length = 0.2f;
	height = 0.6f;
	width = 0.3f;
	paralepipedoTopDown(x + 0.1, y, z, length, height, width, 0, 0);//direita
	paralepipedoTopDown(x + 0.5, y, z, length, height, width, 0, 0); //esquerda
  	glColor3f(0.6f, 0.6f, 0.6f);//color
  	

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

	desenhaCorpo(0.0f, 1.0f, -0.3f, 0, 0);

    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Robô");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}

