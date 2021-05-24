#include<gl/glut.h>
#include<iostream>
using namespace std;
static GLfloat mousex = 0, mousey = 0;
typedef struct point {
	GLfloat x, y;
};
point plist[100];
int pnum = 0;
bool newPolygon = false;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glColor3f(1.0, 0.0, 0.0);
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
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void DrawFrame() {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pnum; i++) {
		glColor3f(rand() % 100 / (double)101, rand() % 100 / (double)101, rand() % 100 / (double)101);
		glVertex2f(plist[i].x, plist[i].y);
	}
	glEnd();
	glFlush();
}
void polygonFill() {
	glBegin(GL_POLYGON);
	for (int i = 0; i < pnum; i++) {
		glColor3f(rand() % 100 / (double)101, rand() % 100 / (double)101, rand() % 100 / (double)101);
		glVertex2f(plist[i].x, plist[i].y);
	}
	glEnd();
	glFlush();
}
void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_RIGHT_BUTTON) {
			polygonFill();
			newPolygon = true;
		}
		if (button == GLUT_LEFT_BUTTON) {
			if (newPolygon) {
				glutPostRedisplay();
				newPolygon = false;
				pnum = 0;
			}
			glColor3f(rand() % 100 / (double)101, rand() % 100 / (double)101, rand() % 100 / (double)101);
			plist[pnum].x = x;
			plist[pnum].y = y;
			pnum++;
			cout << x << "   " << y << endl;
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
			glFlush();
			DrawFrame();
		}
		if (button == GLUT_MIDDLE_BUTTON);
	}
}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("DrawBezier");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MouseFunc);
	glutMainLoop();

	return 0;
}