// gcc fireworks_glut.c -lglut -lGL -lGLU -lm -o fireworks_glut
#include <GL/glut.h>  // Header File For The GLUT Library 
#include <GL/gl.h>	  // Header File For The OpenGL32 Library
#include <GL/glu.h>	  // Header File For The GLu32 Library
#include <math.h>
#include <unistd.h>

#define ESCAPE 27
#define NUM_PARTICLES 100000
#define GRAVITY 0.0003

static GLfloat xRot = 0.00f;
static GLfloat yRot = 0.00f;

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

void RenderScene() {  

    GLUquadricObj *pObj;     
       
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
   
    glPushMatrix();
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  

	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glPushMatrix(); // save transform matrix state
	glTranslatef(0.0f, 1.25f, 0.5f); //posição (x,y,z) = (horizontal, vertical, profundidade)
	gluSphere(pObj, 0.25f, 26, 13);
	glPopMatrix();
	
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
	
	glColor3f(1.0f, 0.4f, 0.5f);  
	glPushMatrix();
	glTranslatef(0.0f, 1.25f, 0.7f);
	gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);  
	glPopMatrix();  
	
	glColor3f(0.0f,0.0f,0.0f); //black
	
	glPushMatrix(); 
	glTranslatef(-0.1f, 1.3f, 0.7f);
	gluSphere(pObj, 0.035f, 13, 7);
	glPopMatrix();
	
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
    
    glColor3f(1.0, 1.0, 1.0);
    
    // Buffer swap  
    //glutSwapBuffers();  
}    

struct s_pf {
  	float x, y, veloc_x, veloc_y;
  	unsigned lifetime;
} particles[NUM_PARTICLES];

int window; 

// Initialize the snowstorm
void InitParticle(int pause)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1.8);
 	int i;

 	if(pause) usleep(200000 + rand() % 2000000);

 	for (i=0; i<NUM_PARTICLES; i++) {
   		float velocity = (float)(rand() % 100)/5000.0;
   		int angle = rand() % 170;
   		// * pi / 180 -> converter para radianos
    	particles[i].veloc_x = cos( (M_PI * angle/180.0) ) * velocity;
    	particles[i].veloc_y = sin( (M_PI * angle/180.0) ) * velocity;
    	particles[i].x = (rand() % 200 - 100) / 10.0; 
    	particles[i].y = 3.0;
    	particles[i].lifetime = rand() % 200;
  	}
}

void InitGL(int Width, int Height)
{
  	glClearColor(0.25f, 0.25f, 0.50f, 1.0f);// This Will Clear The Background Color To Black Blue
  	glClearDepth(1.0);		// Enables Clearing Of The Depth Buffer
  	glDepthFunc(GL_LESS);	// The Type Of Depth Test To Do
  	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
  	glShadeModel(GL_SMOOTH);		// Enables Smooth Color Shading

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();	// Reset The Projection Matrix

  	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);// Calculate The Aspect Ratio Of The Window

  	glMatrixMode(GL_MODELVIEW);
  	InitParticle(0); // first firework
}


void ReSizeGLScene(int Width, int Height)
{
  	if (Height==0)	// Prevent A Divide By Zero If The Window Is Too Small
   	 	Height=1;

 	glViewport(0, 0, Width, Height);	// Reset The Current Viewport And Perspective Transformation

  	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();

 	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  	glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  	int i, ative_particles=0;
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
  	glLoadIdentity();	// Reset The View
  	
	RenderScene();
  	glTranslatef(0.0f,0.0f,-6.0f);	//Move particles 6.0 units into the screen
	
  	glBegin(GL_POINTS);
  	for(i=0;i<NUM_PARTICLES;i++) {
	    if (particles[i].lifetime) {
	     	ative_particles++;
	     	particles[i].veloc_y -= GRAVITY;
	      	particles[i].x += particles[i].veloc_x;
	      	particles[i].y += particles[i].veloc_y;
	      	particles[i].lifetime--;
	
	      	glVertex3f( particles[i].x, particles[i].y, 0.0f); // draw pixel
	    	}
  	}
  	glEnd();
	
  	// swap buffers to display, since we're double buffered.
  	glutSwapBuffers();
  	usleep(20000);

  	if(!ative_particles) InitParticle(1); //reset particles
}

void keyPressed(unsigned char key, int x, int y) 
{
  	if (key == ESCAPE) 
  	{ 
		glutDestroyWindow(window); 
		exit(0);                   
  	}
}

int main(int argc, char **argv) 
{  
 	glutInit(&argc, argv);  
  	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  	glutInitWindowSize(640, 480);  
  	glutInitWindowPosition(0, 0);  
  	window = glutCreateWindow("Tempestade de Neve");   
  	glutDisplayFunc(&DrawGLScene);  
  	glutFullScreen();
  	glutIdleFunc(&DrawGLScene);
  	glutReshapeFunc(&ReSizeGLScene);
  	glutSpecialFunc(SpecialKeys); 
  	glutKeyboardFunc(&keyPressed);
  	InitGL(800, 600);
  	glutMainLoop();  

 	 return 0;
}

