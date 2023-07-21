#include"GL/glut.h"
#include<memory> 
#include <cmath>
using namespace std;

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

							  /// calculate the eye position according to center position and angle,length
void CalEyePostion()
{
	if (yrotate > PI / 2.2) yrotate = PI / 2.2;   /// 限制看得方向
	if (yrotate < 0.01)  yrotate = 0.01;
	if (xrotate > 2 * PI)   xrotate = 0.01;
	if (xrotate < 0)   xrotate = 2 * PI;
	if (celength > 50)  celength = 50;     ///  缩放距离限制
	if (celength < 5)   celength = 5;
	/// 下面利用球坐标系计算 eye 的位置，
	eye[0] = center[0] + celength * sin(yrotate) * cos(xrotate);
	eye[2] = center[2] + celength * sin(yrotate) * sin(xrotate);
	eye[1] = center[1] + celength * cos(yrotate);
}

/// center moves
void MoveBackward()              /// center 点沿视线方向水平向后移动
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

/// CALLBACK func for keyboard presses
void KeyFunc(unsigned char key, int x, int y)
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
	glutPostRedisplay();
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
	{       /// 所除以的数字是调整旋转速度的，
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

void LookAt()            /// 调用 gluLookAt(), 主要嫌直接调用要每次都写好几个参数。。
{
	CalEyePostion();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
}
void RenderScene()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	LookAt();
	//glRotatef(45.0, 1.0, 1.0, 1.0);//绕着向量（1,1,1）所指定的轴旋转45°
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF);
	glBegin(GL_LINES);
	glVertex3f(50, 0, 0.0f);
	glVertex3f(0, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 50, 0.0f);
	glVertex3f(0, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 50);
	glVertex3f(0, 0.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(10.0);

	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(10.0, 20.0, 10.0); 

	glScalef(2.0, 1.0, 0.5);  //在x、y和z轴放大2倍
	glTranslatef(-10.0, -20.0, -10.0); 
	glutWireCube(10.0);

	glFlush();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	/*if (w <= h)
		glOrtho(-30.0, 30.0, -30.0 / aspectRatio, 30.0 / aspectRatio, -30.0, 30.0);
	else
		glOrtho(-30.0*aspectRatio, 30.0*aspectRatio, -30.0, 30.0, -30.0, 30.0);*/
	gluPerspective(60, aspectRatio, 10, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Cube");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyFunc);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotion);

	glutMainLoop();
}
