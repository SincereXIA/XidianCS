#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
int currentMode = 0;
int time = 0;
const int ModeNums = 7;

GLfloat X1 = 3;
GLfloat Y1 = 20;
GLfloat X2 = 19;
GLfloat Y2 = 6;
GLfloat X3 = 46;
GLfloat Y3 = 40;

void init()
{
	glClearColor(0, 0, 0, 0);
}
void myKey(unsigned char key, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。
{
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
	glMatrixMode(GL_MODELVIEW);
	switch (currentMode)
	{
	case 0: glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		break;
	case 1: glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 1.0, 0.0);
		break;
	case 2: glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 1.0);
		break;
	case 3:
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.0);
		break;
	case 4:
		glLoadIdentity();
		glTranslatef(0.01*time, 0.01*time, 0);
		glBegin(GL_TRIANGLES);
	case 5:
		glLoadIdentity();
		glScalef(1+0.02*time, 1-0.01*time, 0);
		glBegin(GL_TRIANGLES);
	case 6:
		glLoadIdentity();
		glTranslatef(centx(X1, Y1, X2, Y2, X3, Y3), centy(X1, Y1, X2, Y2, X3, Y3), 0);
		glRotatef(1*time,0,0,1);
		glTranslatef(-centx(X1, Y1, X2, Y2, X3, Y3), -centy(X1, Y1, X2, Y2, X3, Y3), 0);
		glBegin(GL_TRIANGLES);
	}
	glVertex2f(X1, Y1);
	glVertex2f(X2, Y2);
	glVertex2f(X3, Y3);
	glEnd();
	glutSwapBuffers();

}

void timer(int value)
{
	if (currentMode > 3)
	{
		time += 1;
	}
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
	if (w <= h)
		gluOrtho2D(0.0, 50.0, 0.0 / ratio, 50.0 / ratio);
	else
		gluOrtho2D(0.0*ratio, 50.0*ratio, 0.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(360, 360);
	glutCreateWindow("KeyboardFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	glutTimerFunc(0, timer, 0);

	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
}