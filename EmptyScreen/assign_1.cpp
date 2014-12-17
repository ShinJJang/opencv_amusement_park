#include <windows.h>
#include <gl/glut.h>

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLsizei rsize = 50.0f;
GLsizei padding = 10.0f;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x1 + rsize, y1 + rsize);
	glColor3f(0.0f, 0.5f, 0.0f);
	glRectf(x1 + padding, y1 + padding, x1 + rsize - padding, y1 + rsize - padding);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x1 + rsize*1, -y1, x1 + rsize*2, -(y1 + rsize));
	glColor3f(0.0f, 0.0f, 2.0f);
	glRectf(x1 + rsize*1 + padding, -(y1+padding), x1 + rsize*2 - padding, -(y1 + rsize - padding));

	glColor3f(1.0f, 1.0f, 0.5f);
	glRectf(x1 + rsize*2, y1, x1 + rsize*3, y1 + rsize);
	glColor3f(0.0f, 5.0f, 1.0f);
	glRectf(x1 + rsize*2 + padding, y1 + padding, x1 + rsize*3 - padding, y1 + rsize - padding);

	glColor3f(1.0f, 0.0f, 1.0f);
	glRectf(x1 + rsize*3, -y1, x1 + rsize*4, -(y1 + rsize));
	glColor3f(3.0f, 5.0f, 1.0f);
	glRectf(x1 + rsize*3 + padding, -(y1 + padding), x1 + rsize*4 - padding, -(y1 + rsize - padding));

	glutSwapBuffers();
}
void TimerFunction(int value) 
{
	if(x1 > window_width - rsize || x1 < -window_width)
		xstep = -xstep;

	if(y1 > window_height - rsize || y1 < -window_height)
		ystep = -ystep;
	if(x1 > window_width - rsize)
		x1 = window_width - rsize - 1;
	if(y1 > window_height - rsize)
		y1 = window_height - rsize - 1;
	
	y1 += ystep;
	glutPostRedisplay(); // refresh. renderScene와 같은 역할이지만 바로 호출하면, 점유율 문제
	glutTimerFunc(10, TimerFunction, 1); // 스스로 callback
}
void SetupRC(void)
{
   glClearColor(0.8f, 0.9f,1.0f,1.0f);
}
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) 
	{
		window_width = 150.0f;
		window_height = 150.0f*h/w;
		glOrtho (-150.0f, 150.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 150.0f*w/h;
		window_height = 150.0f;
		glOrtho (-window_width, window_width, -150.0f, 150.0f, 1.0, -1.0);
	}	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce Rectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}