#include <GL/glut.h>
#include <iostream>

typedef GLfloat martix33[3][3];

martix33 MARTIX = { {1,0,0},{0,1,0},{0,0,1} };

void martixmulti(martix33 &m1, martix33 &m2) {
	double mt[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mt[i][j] = m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j] + m1[i][2] * m2[2][j];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			MARTIX[i][j] = mt[i][j];
		}
	}
}

void martix33init() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			MARTIX[i][j] = i == j ? 1 : 0;
		}
	}
}


void drawrect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {

	GLfloat n = MARTIX[2][0] * x1 + MARTIX[2][1] * y1 + MARTIX[2][2] * 1;

	GLfloat nx1 = (MARTIX[0][0] * x1 + MARTIX[0][1] * y1 + MARTIX[0][2] * 1)/n;
	GLfloat ny1 = (MARTIX[1][0] * x1 + MARTIX[1][1] * y1 + MARTIX[1][2] * 1)/n;

	GLfloat nx2 = (MARTIX[0][0] * x2 + MARTIX[0][1] * y2 + MARTIX[0][2] * 1) / n;
	GLfloat ny2 = (MARTIX[1][0] * x2 + MARTIX[1][1] * y2 + MARTIX[1][2] * 1) / n;
	std::cout << nx1 << " " << ny1 << " " << nx2 << ny2 << std::endl;

	glRectf(nx1, ny1, nx2, ny2);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	glRectf(50.0, 100.0, 200.0, 150.0);
	

	glColor3f(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);

	glLineStipple(1, 0x00FF);//第一个参数是倍数，第二个参数是一个十六进制数，用来表示如何显示的
	glBegin(GL_LINES);
	glVertex3f(-1000, 0, 0.0f);
	glVertex3f(1000, 0.0f, 0.0f);
	glEnd();

	glLineStipple(1, 0x01FF);//第一个参数是倍数，第二个参数是一个十六进制数，用来表示如何显示的
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0.0f);
	glVertex3f(0, -1000, 0.0f);
	glEnd();

	glLineStipple(1, 0x01FF);//第一个参数是倍数，第二个参数是一个十六进制数，用来表示如何显示的
	glBegin(GL_LINES);
	glVertex3f(100, 105, 0.0f);
	glVertex3f(-105, -100, 0.0f);
	glEnd();

	glLoadIdentity();
	drawrect(50, 100, 200, 150);
	martix33init();

	/*glTranslatef(-5, 0, 0);

	glRotatef(-45, 0, 0, 1);

	glScalef(-1, 1, 1);

	glRotated(45, 0, 0, 1);

	glTranslatef(5, 0, 0);
	glColor3f(0, 1, 0);
	glRectf(50.0, 100.0, 200.0, 150.0);*/

	martix33 move1 = { {1,0,5},{0,1,0},{0,0,1} };
	martix33 rotat1 = { {0.7071,-0.7071,0},{0.7071,0.7071,0},{0,0,1} };
	martix33 scale = { {-1,0,0},{0,1,0},{0,0,1} };
	martix33 rotat2 = { {0.7071,0.7071,0},{-0.7071,0.7071,0},{0,0,1} };
	martix33 move2 = { {1,0,-5},{0,1,0},{0,0,1} };

	martixmulti(move1, MARTIX);
	martixmulti(rotat1, MARTIX);
	martixmulti(scale, MARTIX);
	martixmulti(rotat2, MARTIX);
	martixmulti(move2, MARTIX);

	glColor3f(0, 1, 0);

	drawrect(50, 100, 200, 150);
	glFlush();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	float ratio;
	if (h == 0)
		h = 1;
	ratio = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(-200.0, 200.0, -200.0 / ratio, 200.0 / ratio);
	else
		gluOrtho2D(-200.0*ratio, 200.0*ratio, -200.0, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Geometric transformation 2");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}