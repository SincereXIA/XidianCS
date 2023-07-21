#include<gl/glut.h>
GLfloat p1[] = { -2,-2 };
GLfloat p2[] = { 2,2 };
GLfloat color1[] = { 0,0,1 };
GLfloat color2[] = { 1,0,0 };
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
	glVertex2i(p1[0],p1[1]);
	glColor3f(color2[0], color2[1], color2[2]);
	glVertex2i(p2[0], p2[1]);
	glEnd();
}
void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	DrawColorLine(p1,p2,color1,color2);

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
		glOrtho(-5.0, 5.0, -5.0 / aspectRatio, 5.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-5.0*aspectRatio, 5.0*aspectRatio, -5.0, 5.0, 1.0, -1.0);
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