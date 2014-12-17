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
static GLfloat viking_xRot = 0.0f;
static GLfloat viking_yRot = 0.0f;
static GLfloat viking_zDistance = 0.0f;

static GLfloat hurricane_xRot = 0.0f;
static GLfloat hurricane_yRot = 0.0f;
static GLfloat hurricane_zDistance = 0.0f;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;
static GLfloat viking_increment = 1.0f;
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


void DrawJet(int nShadow)
{
	 GLTVector3 vNormal; // Storeage for calculated surface normal   
   
    // Nose Cone /////////////////////////////   
    // Set material color, note we only have to set to black   
    // for the shadow once   
    if(nShadow == 0)   
           glColor3ub(128, 128, 128);   
    else   
            glColor3ub(0,0,0);   
   
   
    // Nose Cone - Points straight down   
    glBegin(GL_TRIANGLES);   
                glNormal3f(0.0f, -1.0f, 0.0f);   
        glNormal3f(0.0f, -1.0f, 0.0f);   
        glVertex3f(0.0f, 0.0f, 60.0f);   
        glVertex3f(-15.0f, 0.0f, 30.0f);   
        glVertex3f(15.0f,0.0f,30.0f);   
                   
       
		// Verticies for this panel   
                {   
                GLTVector3 vPoints[3] = {{ 15.0f, 0.0f,  30.0f},   
                                        { 0.0f,  15.0f, 30.0f},   
                                        { 0.0f,  0.0f,  60.0f}};   
   
                // Calculate the normal for the plane   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
        glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }      
   
   
                {   
                GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, 60.0f },   
                                        { 0.0f, 15.0f, 30.0f },   
                                        { -15.0f, 0.0f, 30.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
   
   
                // Body of the Plane ////////////////////////   
                {   
                GLTVector3 vPoints[3] = {{ -15.0f, 0.0f, 30.0f },   
                                        { 0.0f, 15.0f, 30.0f },   
                        { 0.0f, 0.0f, -56.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                       
                {   
                GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, -56.0f },   
                                        { 0.0f, 15.0f, 30.0f },   
                                        { 15.0f,0.0f,30.0f }};   
       
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                           
       
        glNormal3f(0.0f, -1.0f, 0.0f);   
        glVertex3f(15.0f,0.0f,30.0f);   
        glVertex3f(-15.0f, 0.0f, 30.0f);   
        glVertex3f(0.0f, 0.0f, -56.0f);   
       
                ///////////////////////////////////////////////   
                // Left wing   
                // Large triangle for bottom of wing   
                {   
                GLTVector3 vPoints[3] = {{ 0.0f,2.0f,27.0f },   
                                        { -60.0f, 2.0f, -8.0f },   
                                        { 60.0f, 2.0f, -8.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                               
                {   
                GLTVector3 vPoints[3] = {{ 60.0f, 2.0f, -8.0f},   
                    {0.0f, 7.0f, -8.0f},   
                    {0.0f,2.0f,27.0f }};   
                   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                {   
                GLTVector3 vPoints[3] = {{60.0f, 2.0f, -8.0f},   
                    {-60.0f, 2.0f, -8.0f},   
                    {0.0f,7.0f,-8.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                {   
                GLTVector3 vPoints[3] = {{0.0f,2.0f,27.0f},   
                                        {0.0f, 7.0f, -8.0f},   
                                        {-60.0f, 2.0f, -8.0f}};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                           
                // Tail section///////////////////////////////   
                // Bottom of back fin   
        glNormal3f(0.0f, -1.0f, 0.0f);   
        glVertex3f(-30.0f, -0.50f, -57.0f);   
        glVertex3f(30.0f, -0.50f, -57.0f);   
        glVertex3f(0.0f,-0.50f,-40.0f);   
   
                {   
                GLTVector3 vPoints[3] = {{ 0.0f,-0.5f,-40.0f },   
                    {30.0f, -0.5f, -57.0f},   
                    {0.0f, 4.0f, -57.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                           
                {   
                GLTVector3 vPoints[3] = {{ 0.0f, 4.0f, -57.0f },   
                    { -30.0f, -0.5f, -57.0f },   
                    { 0.0f,-0.5f,-40.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
   
   
                {   
                GLTVector3 vPoints[3] = {{ 30.0f,-0.5f,-57.0f },   
                    { -30.0f, -0.5f, -57.0f },   
                    { 0.0f, 4.0f, -57.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                {   
                GLTVector3 vPoints[3] = {{ 0.0f,0.5f,-40.0f },   
                    { 3.0f, 0.5f, -57.0f },   
                    { 0.0f, 25.0f, -65.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                           
                {   
                GLTVector3 vPoints[3] = {{ 0.0f, 25.0f, -65.0f },   
                    { -3.0f, 0.5f, -57.0f},   
                    { 0.0f,0.5f,-40.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                {   
                GLTVector3 vPoints[3] = {{ 3.0f,0.5f,-57.0f },   
                    { -3.0f, 0.5f, -57.0f },   
                    { 0.0f, 25.0f, -65.0f }};   
   
                gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);   
                glNormal3fv(vNormal);   
        glVertex3fv(vPoints[0]);   
        glVertex3fv(vPoints[1]);   
        glVertex3fv(vPoints[2]);   
                }   
                   
                   
        glEnd(); 
}

void Viking(){
	
	
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
	glRotatef(viking_xRot, 1.0f, 0.0f, 0.0f);   
    glRotatef(viking_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(viking_zDistance, 0.0f, 0.0f, 1.0f);   
	glTranslatef(200.0f, -50.0f, 0.0f);

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

void RenderScene(void)
{
	// Clear the window with current clearing color   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   
    // Draw the ground, we do manual shading to a darker green   
    // in the background to give the illusion of depth   
    glBegin(GL_QUADS);   
        glColor3ub(0,32,0);   
        glVertex3f(400.0f, -150.0f, -200.0f);   
        glVertex3f(-400.0f, -150.0f, -200.0f);   
        glColor3ub(0,255,0);   
        glVertex3f(-400.0f, -150.0f, 200.0f);   
        glVertex3f(400.0f, -150.0f, 200.0f);   
    glEnd();   
   
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
    //DrawJet(1);	
   
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
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key == GLUT_KEY_HOME)
		zDistance += 5.0f;
	
	if(key == GLUT_KEY_END)
		zDistance -= 5.0f;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
    GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };  
     //light position 

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
	if(viking_xRot <= -70.0f || viking_xRot >= 70.0f)
		viking_increment = -viking_increment;

	viking_xRot += viking_increment*((70.0f-abs(viking_xRot)+1.0f)/40.0f);	

	if(hurricane_yRot >= 360.0f || hurricane_yRot <= 0.0f)
		hurricane_yRot = 0;

	hurricane_yRot += 5.0f;

	glutPostRedisplay(); // refresh. renderScene와 같은 역할이지만 바로 호출하면, 점유율 문제
	glutTimerFunc(10, TimerFunction, 1); // 스스로 callback
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Light Jet");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}

