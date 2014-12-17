#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static int count_points = 0;

GLfloat window_width;
GLfloat window_height;
GLfloat x, y;

void SetupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f); 

	glColor3f(0.0f,1.0f,0.0f);
	
}

void RenderScene(void)
{
	GLfloat z, angle, r;
	int i;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot,1.0f,0.0f,0.0f); 
	glRotatef(yRot,0.0f,1.0f,0.0f);
	
	glBegin(GL_POINTS); //add
	z = -50.0f;
	for(angle = 0.0f, i = 0, r = 3.0f; i < count_points; i++, angle += 0.1f) 
	{	
		r = r * 1.008f;
		x = (r)*sin(angle);
		y = (r)*cos(angle);
		glVertex3f(x,y,z);	
		//z += 0.5f;
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w ,h );

	if(w<=h) {
		window_width = nRange;
		window_height = nRange*h/w;
		glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange, nRange);
	}
	else {
		window_width = nRange*w/h;
		window_height = nRange;
		glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange, nRange);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();

}

void TimerFunction(int value) 
{		
	count_points += 1;

	if(x > window_width || x < -window_width || y > window_height || y < -window_height)
		count_points = 1;
	
	glutPostRedisplay(); // refresh. renderScene와 같은 역할이지만 바로 호출하면, 점유율 문제
	glutTimerFunc(11, TimerFunction, 1); // 스스로 callback
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0); // add
	glutInitWindowSize(512,512); // add
	glutCreateWindow("SpringVertex");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutTimerFunc(1000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	
}