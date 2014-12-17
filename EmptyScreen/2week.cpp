#include <stdlib.h>
#include <gl/glut.h>
#include <Windows.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

bool iCull = FALSE;
bool iOutline = FALSE;
bool iDepth = FALSE;

void ProcessMenu(int value) //add
{
	switch(value)
	{
	case 1:
		iDepth = !iDepth;
		break;
	case 2:
		iCull = !iCull;
		break;
	case 3:
		iOutline = !iOutline;
		break;
	default :
		break;
	}
	glutPostRedisplay();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

	glShadeModel(GL_FLAT); // add
	glFrontFace(GL_CW);    // add 

}

/* spring - point */
/*
void RenderScene(void)
{
	GLfloat x, y, z, angle;
	GLfloat sizes[2];
	GLfloat step;
	GLfloat cursize;

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	cursize = sizes[0];	
	z=-50.0f;

	for(angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
	{
		x = 60.0f*sin(angle);
		y = 60.0f*cos(angle);
		glPointSize(cursize);
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);		
		glEnd();
		z += 0.5f;
		cursize += step;
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
//*/

/* line */
/*
void RenderScene(void)
{
	GLfloat x,y,z,angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot,1.0f,0.0f,0.0f); 
	glRotatef(yRot,0.0f,1.0f,0.0f);
	glBegin(GL_LINES); //add
	z =  0.0f;
	for(angle =0.0f ; angle < GL_PI; angle +=(GL_PI/20.0f))	// add - 20개의 line drawing
	{
		x = 50.0f*sin(angle);            
		y = 50.0f*cos(angle);
		glVertex3f(x,y,z);
		x = 50.0f*sin(angle+GL_PI);       
		y = 50.0f*cos(angle+GL_PI);
		glVertex3f(x,y,z);               
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
//*/

/* spring - line */
/*
void RenderScene(void)
{
	GLfloat x,y,z,angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot,1.0f,0.0f,0.0f); 
	glRotatef(yRot,0.0f,1.0f,0.0f);
	
	glBegin(GL_LINE_STRIP); //add
	z = -50.0f;	
	for(angle =0.0f ; angle < 3.0f*(GL_PI*2.0f); angle +=0.1f) 
	{
		x = 50.0f*sin(angle);             
		y = 50.0f*cos(angle);
		glVertex3f(x,y,z);
		z += 0.5f;
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
} 	
//*/

/* strips width */
/*
void RenderScene(void)
{
	GLfloat x,y,z;
	GLfloat fSizes[2]; // add
	GLfloat fCurSize;  // add
	glClear(GL_COLOR_BUFFER_BIT);

	x = 0.0f;
	z = 0.0f;
	glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes); // add
	fCurSize = fSizes[0];
	for(y =- 90.0f; y <= 90.0f ; y+=20.0f) 
	{
		glLineWidth(fCurSize);  // add - 선 두께를 설정
		glBegin(GL_LINES);
		glVertex3f(-80,y,z);
		glVertex3f(80,y,z);
		glEnd();
		fCurSize += 1.0f;      // add 선 두께를 증가
	}
	glutSwapBuffers();
}
//*/

/* triangle */
///*
void RenderScene()
{
	GLfloat x,y,angle;
	int iPivot =1;           // add
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(iCull)
		glEnable(GL_CULL_FACE);   
	else
		glDisable(GL_CULL_FACE);  
	
	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	
	if(iOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN); // add
	glVertex3f(0.0f, 0.0f, 75.0f); // add - 기준점
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) 
	{		
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0) // add
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;           // add
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN); // add
	glVertex2f(0.0f, 0.0f);   // add - 기준점
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0)    // add
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();

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

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if(w <= h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	
	glutCreateWindow("SpringVertex");
	glutCreateMenu(ProcessMenu); // add - Create the Menu
	glutAddMenuEntry("깊이 테스트",1); 
	glutAddMenuEntry("은면 제거",2);
	glutAddMenuEntry("뒷면 라인 그리기",3);
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}