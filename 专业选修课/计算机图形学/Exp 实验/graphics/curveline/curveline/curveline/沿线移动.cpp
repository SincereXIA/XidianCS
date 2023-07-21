#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include<memory> 
#include <cmath>

using namespace std;

int currentMode = 0;
int time = 0;
const int ModeNums = 2;

GLfloat X1 = 3;
GLfloat Y1 = 20;
GLfloat X2 = 19;
GLfloat Y2 = 6;
GLfloat X3 = 46;
GLfloat Y3 = 40;

const GLfloat PI = 3.14;

/// record the state of mouse
GLboolean mouserdown = GL_FALSE;
GLboolean mouseldown = GL_FALSE;
GLboolean mousemdown = GL_FALSE;

/// when a mouse-key is pressed, record current mouse position 
static GLint mousex = 0, mousey = 0;

static GLfloat center[3] = { 0.0f, 0.0f, 0.0f }; /// center position
static GLfloat eye[3]; /// eye's position

static GLfloat yrotate = PI / 4; /// angle between y-axis and look direction
static GLfloat xrotate = PI / 4; /// angle between x-axis and look direction
static GLfloat celength = 20.0f;/// lenght between center and eye

static GLfloat mSpeed = 0.4f; /// center move speed
static GLfloat rSpeed = 0.02f; /// rotate speed
static GLfloat lSpeed = 0.4f; /// reserved

void RotateLeft();
void RotateRight();
void MoveForward();
void MoveBackward();
void RotateUp();
void RotateDown();
void LookAt();
void init()
{
	glClearColor(0, 0, 0, 0);
}
void myKey(unsigned char key, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。
{
	switch (key)
	{
	case 'a': RotateLeft(); break;
	case 'd': RotateRight(); break;
	case 'w': MoveForward(); break;
	case 's': MoveBackward(); break;
	case 'q': RotateUp(); break;
	case 'e': RotateDown(); break;
	}
	switch (key)
	{
	case ' ': currentMode = (currentMode + 1) % ModeNums;
		time = 0;
		glutPostRedisplay();
		break;
	case 27:  exit(-1);
	}
}

GLfloat centx(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3) {
	return (x1 + x2 + x3) / 3;
}
GLfloat centy(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3) {
	return (y1 + y2 + y3) / 3;
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	LookAt();
	switch (currentMode)
	{
	case 0: 
		//glLoadIdentity();
		glTranslatef(-0.06*time, -0.06*time, 0);
		break;
	case 1:
		glRotatef(1 * time, 0, 1, 0);
	}
	glutWireTeapot(10);
	glEnd();
	glutSwapBuffers();

}

void timer(int value)
{

	time += 1;
	time = time % 365;
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	float ratio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (float)w / (float)h;
	/*
	if (w <= h)
		glOrtho(0.0, 50.0, 0.0 / ratio, 50.0 / ratio,);
	else
		glOrtho(0.0*ratio, 50.0*ratio, 0.0, 50.0);
	*/
	gluPerspective(60, ratio, 10, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}





							  /// calculate the eye position according to center position and angle,length
void CalEyePostion()
{
	if (yrotate > PI / 2.2) yrotate = PI / 2.2;   /// ���ƿ��÷���
	if (yrotate < 0.01)  yrotate = 0.01;
	if (xrotate > 2 * PI)   xrotate = 0.01;
	if (xrotate < 0)   xrotate = 2 * PI;
	if (celength > 50)  celength = 50;     ///  ���ž�������
	if (celength < 5)   celength = 5;
	/// ��������������ϵ���� eye ��λ�ã�
	eye[0] = center[0] + celength * sin(yrotate) * cos(xrotate);
	eye[2] = center[2] + celength * sin(yrotate) * sin(xrotate);
	eye[1] = center[1] + celength * cos(yrotate);
}

/// center moves
void MoveBackward()              /// center �������߷���ˮƽ����ƶ�
{
	center[0] += mSpeed * cos(xrotate);
	center[2] += mSpeed * sin(xrotate);
	CalEyePostion();
}

void MoveForward()
{
	center[0] -= mSpeed * cos(xrotate);
	center[2] -= mSpeed * sin(xrotate);
	CalEyePostion();
}

/// visual angle rotates
void RotateLeft()
{
	xrotate -= rSpeed;
	CalEyePostion();
}

void RotateRight()
{
	xrotate += rSpeed;
	CalEyePostion();
}

void RotateUp()
{
	yrotate += rSpeed;
	CalEyePostion();
}

void RotateDown()
{
	yrotate -= rSpeed;
	CalEyePostion();
}



/// CALLBACK func for mouse kicks
void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_TRUE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_TRUE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_TRUE;
	}
	else
	{
		if (button == GLUT_RIGHT_BUTTON) mouserdown = GL_FALSE;
		if (button == GLUT_LEFT_BUTTON) mouseldown = GL_FALSE;
		if (button == GLUT_MIDDLE_BUTTON)mousemdown = GL_FALSE;
	}
	mousex = x, mousey = y;
}

/// CALLBACK func for mouse motions
void MouseMotion(int x, int y)
{
	if (mouserdown == GL_TRUE)
	{       /// �����Ե������ǵ�����ת�ٶȵģ�
		xrotate += (x - mousex) / 180.0f;
		yrotate -= (y - mousey) / 120.0f;
	}

	if (mouseldown == GL_TRUE)
	{
		celength += (y - mousey) / 25.0f;
	}
	mousex = x, mousey = y;
	CalEyePostion();
	glutPostRedisplay();
}

void LookAt()            /// ���� gluLookAt(), ��Ҫ��ֱ�ӵ���Ҫÿ�ζ�д�ü�����������
{
	CalEyePostion();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(360, 360);
	glutCreateWindow("KeyboardFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(0, timer, 0);

	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
}