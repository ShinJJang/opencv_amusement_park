// Shadow.c   
// OpenGL SuperBible   
// Demonstrates simple planar shadows   
// Program by Richard S. Wright Jr.   
   
// These values need to be available globally   
// Light values and coordinates   

#include <stdlib.h>  
#include <math.h>
#include <gl/glut.h>
#include <gl/gltools.h>
#include <gl/glaux.h>  

static GLfloat viking_xRot = 0.0f;
static GLfloat viking_yRot = 0.0f;
static GLfloat viking_zDistance = 0.0f;

static GLfloat hurricane_xRot = 0.0f;
static GLfloat hurricane_yRot = 0.0f;
static GLfloat hurricane_zDistance = 0.0f;

static GLfloat lx, lz = 0.0f;
static GLfloat angle = 0.0f;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;
static GLfloat viking_increment = 1.0f;

static int firecraker_count_points = 0;
static GLfloat firecraker_x, firecraker_y = 0;

GLfloat window_width;
GLfloat window_height;

AUX_RGBImageRec * texRec[2];
GLuint texID[2];

#define PI 3.14f

GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };   
GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };   
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};   
GLfloat  lightPos[] = { -75.0f, 150.0f, -50.0f, 0.0f };   
GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f }; 

GLTVector3 vPoints[3];
   
// Transformation matrix to project shadow   
GLTMatrix shadowMat;   

void SetupRC()
{   
     // Any three points on the ground (counter clockwise order)   
    GLTVector3 points[3] = {{ -30.0f, -149.0f, -20.0f },   
                            { -30.0f, -149.0f, 20.0f },   
                            { 40.0f, -149.0f, 20.0f }};   
   
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal   
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out   
    glEnable(GL_CULL_FACE);     // Do not calculate inside of jet   
   
    // Setup and enable light 0   
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);   
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);   
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);   
    glEnable(GL_LIGHT0);   
   
    // Enable color tracking   
    glEnable(GL_COLOR_MATERIAL);   
       
    // Set Material properties to follow glColor values   
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   
   
    // All materials hereafter have full specular reflectivity   
    // with a high shine   
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);   
    glMateriali(GL_FRONT,GL_SHININESS,128);   
   
    // Light blue background   
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f );   
   
    // Calculate projection matrix to draw shadow on the ground   
    //gltMakeShadowMatrix(points, lightPos, shadowMat);   
}

void Viking(){
	glTranslatef(0.0f + lx, 0.0f, 0.0f + lz);
    glRotatef(viking_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(viking_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(viking_zDistance, 0.0f, 0.0f, 1.0f);   
	glTranslatef(0.0f, -50.0f, 0.0f);

	// BODY	
    glPushMatrix();
    glColor4f(0.7f, 0.3f, 0.3f, 0.9f);
    
    float int_axis=40.f;
    float long_axis=80.f;
	
	for(GLfloat Alpha=PI*11/6 ; Alpha>=PI*5/6 ; Alpha-=PI/6)
    {
        for(GLfloat Beta=-PI/2;Beta<=PI/2;Beta+=PI/12)
        {
            glBegin(GL_POLYGON);
            glNormal3f(int_axis*cos(PI+Beta)*cos(PI+Alpha),            int_axis*cos(PI+Beta)*sin(PI+Alpha),            long_axis*sin(PI+Beta));
            glVertex3f(int_axis*cos(PI+Beta)*cos(PI+Alpha),            int_axis*cos(PI+Beta)*sin(PI+Alpha),            long_axis*sin(PI+Beta));
            glVertex3f(int_axis*cos(PI+Beta)*cos(PI+PI/6+Alpha),       int_axis*cos(PI+Beta)*sin(PI+PI/6+Alpha),       long_axis*sin(PI+Beta));
            glVertex3f(int_axis*cos(PI+PI/12+Beta)*cos(PI+PI/6+Alpha), int_axis*cos(PI+PI/12+Beta)*sin(PI+PI/6+Alpha), long_axis*sin(PI+PI/12+Beta));
            glVertex3f(int_axis*cos(PI+PI/12+Beta)*cos(PI+Alpha),      int_axis*cos(PI+PI/12+Beta)*sin(PI+Alpha),      long_axis*sin(PI+PI/12+Beta));
            glEnd();
        }	
    }	
    glPopMatrix();

	
	glPushMatrix();
	// LINE
	glColor4f(0.7f, 0.3f, 0.3f, 0.9f);
	glLineWidth(10.0f);

	glBegin(GL_LINES);	
	glVertex3f(0.0f, 0.0f, long_axis);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);	
	glVertex3f(0.0f, 0.0f, -long_axis);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glEnd();

	// TOP CIRCLE
	glTranslatef(0.0f, 50.0f, 0.0f);
	glutSolidSphere(6.0f,15,15);
	glPopMatrix();
}

void DrawCircle(float cx, float cy, float cz, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glShadeModel(GL_SMOOTH);
	GLubyte tmp = 50;
    for (int ii = 0; ii < num_segments; ii++)   {
		if(ii % 90 == 0) {
			tmp += 50;
			glColor3ub((GLubyte)tmp, (GLubyte)30, (GLubyte)10);
		}

        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float z = r * sinf(theta);//calculate the y component 		
        glVertex3f(x+cx, cy, z+cz);//output vertex 
    }
	glColor3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

void Hurricane() {
	glTranslatef(200.0f + lx, 0.f, 0.0f + lz);
	glRotatef(viking_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(viking_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(viking_zDistance, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.f, -50.0f, 0.0f);

	glPushMatrix();
	
	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);   

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();	
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 30.0f, 30.0f, 10.0f, 32, 64);
			
	glPopMatrix();

	glPushMatrix();

	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);   

	DrawCircle(0.0f, -10.0f, 0.0f, 30.0f, 360);	
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	DrawCircle(0.0f, 0.0f, 0.0f, 30.0f, 360);		
	glPopMatrix();

	glPushMatrix();
	// LINE
	glColor4f(0.7f, 0.3f, 0.3f, 0.9f);
	glLineWidth(10.0f);

	GLUquadricObj *quadratic_line;
	quadratic = gluNewQuadric();	
	glTranslatef(0.0f, 80.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);	
	gluCylinder(quadratic, 3.0f, 3.0f, 80.0f, 32, 64);	

	glPopMatrix();
}

void Rollarcoaster(void) {
	
}

void Merry_go_round(void) {
	GLfloat x,y,angle;
	int iPivot =1;           // add

	glTranslatef(-100.0f + lx, -50.0f, -100.0f + lz);

	// 하판
	glPushMatrix();
	
	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);   

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();	
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 60.0f, 60.0f, 5.0f, 32, 64);
			
	glPopMatrix();

	glPushMatrix();

	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);   

	DrawCircle(0.0f, -5.0f, 0.0f, 60.0f, 360);	
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	DrawCircle(0.0f, 0.0f, 0.0f, 60.0f, 360);		
	glPopMatrix();

	// 상판	
	glPushMatrix();
	glTranslatef(0.f, 50.f, 0.f);
	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	
	glDisable(GL_CULL_FACE);  	
	glBegin(GL_TRIANGLE_FAN); // add
	glVertex3f(0.0f, 0.0f, 45.0f); // add - 기준점
	for(angle = 0.0f; angle < (2.0f*PI); angle += (PI/8.0f)) 
	{		
		x = 60.0f*sin(angle);
		y = 60.0f*cos(angle);
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
	for(angle = 0.0f; angle < (2.0f*PI); angle += (PI/8.0f))
	{
		x = 60.0f*sin(angle);
		y = 60.0f*cos(angle);
		if((iPivot %2) == 0)    // add
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();

	// 하판 위에 올라올 오브젝트
	glPopMatrix();

	glPushMatrix();
	glRotatef(hurricane_xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(hurricane_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(hurricane_zDistance, 0.0f, 0.0f, 1.0f);
	
	glTranslatef(35.0f, 0.f, 0.f);
	glutSolidCube(20);
	
	glTranslatef(-35.f, 0.f, 35.f);
	glutSolidCube(20);
	
	glTranslatef(-35.f, 0.f, -35.f);
	glutSolidCube(20);
	
	glTranslatef(35.f, 0.f, -35.f);
	glutSolidCube(20);
	
	glPopMatrix();

	glPushMatrix();
	// LINE
	glColor4f(0.7f, 0.3f, 0.3f, 0.9f);
	glLineWidth(10.0f);

	GLUquadricObj *quadratic_line;
	quadratic = gluNewQuadric();	
	glTranslatef(0.0f, 50.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);	
	gluCylinder(quadratic, 3.0f, 3.0f, 50.0f, 32, 64);	

	glPopMatrix();
}

void FireCraker(void) {
	GLfloat z,angle;
	int i;

	glPushMatrix();
	glTranslatef(0.f, 100.f, -100.f);
	glRotatef(-70.f, 1.0f, 0.f, 0.f);
	
	glBegin(GL_POINTS); //add
	z = -50.0f;
	for(angle = 0.0f, i = 0; i < firecraker_count_points; i++, angle += 0.1f) 
	{
		firecraker_x = (angle)*sin(angle*i);
		firecraker_y = (angle)*cos(angle*i);
		glVertex3f(firecraker_x,firecraker_y,z);
		z += 0.5f;
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(200.f, 100.f, -100.f);
	glRotatef(-70.f, 1.0f, 0.f, 0.f);
	
	glBegin(GL_POINTS); //add
	z = -50.0f;
	for(angle = 0.0f, i = 0; i < firecraker_count_points; i++, angle += 0.1f) 
	{
		firecraker_x = (angle)*sin(angle*i);
		firecraker_y = (angle)*cos(angle*i);
		glVertex3f(firecraker_x,firecraker_y,z);
		z += 0.5f;
	}

	glEnd();
	glPopMatrix();
}

void RenderScene(void)
{
	// Clear the window with current clearing color   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   
	/* 너무 느려져서 안씀
	texRec[0] = auxDIBImageLoad(L"Earth.bmp"); //add  
	texRec[1] = auxDIBImageLoad(L"Sun.bmp"); //add  
	glGenTextures(2, texID); // 두 개의 멀티 텍스쳐 ID 배열 설정
	
	for(int i =0; i<2 ; i++) //add  ///////////////////////////////////////////
	{
	glBindTexture(GL_TEXTURE_2D, texID[i]);  // 사용할 텍스쳐  ID 지정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0, GL_RGB, 
                 GL_UNSIGNED_BYTE, texRec[i]->data);  //ID 지정 후 해당 텍스쳐 정의 (자동으로 연결된다)
	}*/


    // Draw the ground, we do manual shading to a darker green   
    // in the background to give the illusion of depth
	glPushMatrix();
	glTranslatef(lx, 0.0f, lz);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);    
	FireCraker();
    glBegin(GL_QUADS);   
        glColor3ub(0,32,0);   
        glVertex3f(400.0f, -150.0f, -200.0f);   
        glVertex3f(-400.0f, -150.0f, -200.0f);   
        glColor3ub(0,255,0);   
        glVertex3f(-400.0f, -150.0f, 200.0f);   
        glVertex3f(400.0f, -150.0f, 200.0f);   
    glEnd();
	glPopMatrix();
   
	// 바이킹
    // Save the matrix state and do the rotations   
    glPushMatrix();   
       
    glEnable(GL_LIGHTING);   
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);
    //DrawJet(0);
	Viking();
   
    // Restore original matrix state   
    glPopMatrix();     
   
	// 허리케인
    glPushMatrix();   
   
    glEnable(GL_LIGHTING);   
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);    

	Hurricane();
	
   
    // Restore original matrix state   
    glPopMatrix();
   
	// 롤러코스터
    glPushMatrix();   
   
    glEnable(GL_LIGHTING);   
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);    

	Rollarcoaster();	
   
    // Restore original matrix state   
    glPopMatrix();

	// 회전 목마
    glPushMatrix();   
   
    glEnable(GL_LIGHTING);   
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);    

	Merry_go_round();	
   
    // Restore original matrix state   
    glPopMatrix();

    // Get ready to draw the shadow and the ground   
    // First disable lighting and save the projection state   
    glDisable(GL_DEPTH_TEST);   
    glDisable(GL_LIGHTING);   
    glPushMatrix();   
   
    // Multiply by shadow projection matrix   
    glMultMatrixf((GLfloat *)shadowMat);   
   
    // Now rotate the jet around in the new flattend space   
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);   
	glRotatef(zDistance, 0.0f, 0.0f, 1.0f);
   
    // Pass true to indicate drawing shadow   
   
    // Restore the projection to normal   
    glPopMatrix();   
   
    // Draw the light source   
    glPushMatrix();   
    glTranslatef(lightPos[0],lightPos[1], lightPos[2]);   
    glColor3ub(255,255,0);   
    glutSolidSphere(5.0f,10,10);   
    glPopMatrix();   
   
    // Restore lighting state variables   
    glEnable(GL_DEPTH_TEST);   
   
    // Display the results   
    glutSwapBuffers(); 
}

void ContorolKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		lz += 5.0f;

	if(key == GLUT_KEY_DOWN)		
		lz -= 5.0f;

	if(key == GLUT_KEY_LEFT)		
		lx += 5.0f;

	if(key == GLUT_KEY_RIGHT)	
		lx -= 5.0f;

	if(key == GLUT_KEY_HOME)
		yRot += 5.0f;
	
	if(key == GLUT_KEY_END)
		yRot -= 5.0f;

	if(key == GLUT_KEY_PAGE_UP)
		xRot += 5.0f;

	if(key == GLUT_KEY_PAGE_DOWN)
		xRot -= 5.0f;	

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
    GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };  
     //light position 

	window_width = w;
	window_height = h;

	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(100.0f,fAspect,1.0f,500.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//light position 
    glTranslatef(0.0f, 0.0f, -150.0f);
	
}

void TimerFunction(int value) 
{	
	// 바이킹 흔들림
	if(viking_increment == 0)
		viking_increment = 1.0f;

	if(viking_xRot <= -70.0f || viking_xRot >= 70.0f)
		viking_increment = -viking_increment;

	viking_xRot += viking_increment*((70.0f-abs(viking_xRot)+1.0f)/40.0f);	

	// 허리케인 회전
	if(hurricane_yRot >= 360.0f || hurricane_yRot <= 0.0f)
		hurricane_yRot = 0;

	hurricane_yRot += 5.0f;

	// 폭죽
	firecraker_count_points += 1;

	if(firecraker_count_points > 200)
		firecraker_count_points = 1;

	glutPostRedisplay(); // refresh. renderScene와 같은 역할이지만 바로 호출하면, 점유율 문제
	glutTimerFunc(10, TimerFunction, 1); // 스스로 callback
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(500,200);
	glutCreateWindow("GL Amusement park");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}

