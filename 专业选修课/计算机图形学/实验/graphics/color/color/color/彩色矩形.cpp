#include<gl/glut.h>
#include <iostream>
using namespace std;
GLfloat p1[] = { -2,-2 };
GLfloat p2[] = { 2,2 };
GLfloat color1[] = { 0,0,1 };
GLfloat color2[] = { 1,0,0 };
GLfloat viewSize = 10.0;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void DrawColorLine(GLfloat *p1, GLfloat *p2, GLfloat *color1, GLfloat *color2)
{
	glLineWidth(3);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_LINES);
	glColor3f(color1[0], color1[1], color1[2]);
	glVertex2i(p1[0], p1[1]);
	glColor3f(color2[0], color2[1], color2[2]);
	glVertex2i(p2[0], p2[1]);
	glEnd();
}
void DrawColorCube(GLfloat cubeSize) {
	GLfloat cx = 0;
	GLfloat cy = 0;
	int color = 0;
	
	for (int i = 0; i < 3; i++) {
		cy += viewSize / 4.0;
		cx = 0;
		for (int j = 0; j < 3; j++) {
			cx += viewSize / 4.0;
			glColor3f(color%2, (color%4)/2,(color%8)/4);
			glRectf(cx - cubeSize/2, cy - cubeSize/2, cx + cubeSize/2, cy + cubeSize/2);
			color++;
		}
	}
	glColor3f(1, 0.5, 0);
	glRectf(cx - cubeSize / 2, cy - cubeSize / 2, cx + cubeSize / 2, cy + cubeSize / 2);
}
void RenderScence()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	DrawColorCube(2.0);
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
	if (w <= h)
		glOrtho(0, viewSize, 0 / aspectRatio, viewSize / aspectRatio, 1.0, -1.0);
	else
		glOrtho(0*aspectRatio, viewSize*aspectRatio, 0, viewSize, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("DrawBezier");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}