#include <gl/glut.h>
typedef struct {
	float x, y;
}point;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void drawCurve1(int n)
{
	point pixels[100];
	float delta, t, t2, t3;
	int i;

	delta = 1.0 / (n - 1);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++)
	{
		t = i * delta;
		t2 = t * t;
		t3 = t2 * t;
		pixels[i].x = t2 - 2 * t + 1;
		pixels[i].y = t3 - 2 * t2 + t;
		glVertex2f(pixels[i].x, pixels[i].y);
	}
	glEnd();
}
void drawCurve2(int n)
{
	point pixels[100];
	float delta, t, t2, t3;
	int i;

	delta = 1.0 / (n - 1);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++)
	{
		t = i * delta;
		t2 = t * t;
		t3 = t2 * t;
		pixels[i].x = t2 + 1;
		pixels[i].y = t3;
		glVertex2f(pixels[i].x, pixels[i].y);
	}
	glEnd();
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	drawCurve1(100);
	glColor3f(0.0, 1.0, 0.0);
	drawCurve2(100);
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
		glOrtho(-1.0, 3.0, -1.0 / aspectRatio, 3.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-1.0*aspectRatio, 3.0*aspectRatio, -1.0, 3.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("DrawCurve");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}