#include<gl/glut.h>
#include<math.h>
#include<windows.h>
#include<algorithm>
using namespace std;
struct Vertex
{
	GLfloat x, y;
	Vertex(GLfloat tx, GLfloat ty)
	{
		x = tx;
		y = ty;
	}
};

Vertex p0(0, 1);        //型值点
Vertex p1(3, 0);
Vertex c0(0, 2);        //控制点
Vertex c1(0, 0);

GLsizei W;
GLsizei H;

bool mouseLeftIsDown = false;
bool mouseRightIsDown = false;

void ChangeMouse(Vertex &a)
{
	a.x = a.x / W * 20 - 10;
	a.y = - (a.y / H * 20 * (W / H) - 10 * (W / H));
}

GLfloat caculateSquareDistance(Vertex &a, Vertex b)
{
	

	//b.x = (b.x + 10) / 20 * W;
	//b.y = (b.y + 10 / (W / H)) / (20 / (W / H)) *H;
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y);
}
void Hermite(int n)     //精度
{
	//求出相对于控制点的向量（切线）
	//这里把切点的长度人为扩大4倍，划线的效果更为明显（实际上不符合计算出的公式）
	Vertex tempC0((c0.x - p0.x) * 4, (c0.y - p0.y) * 4);
	Vertex tempC1((c1.x - p1.x) * 4, (c1.y - p1.y) * 4);

	double delTa = 1.0 / n;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i++)
	{
		double t = i * delTa;

		double t1 = 2 * pow(t, 3) - 3 * pow(t, 2) + 1;
		double t2 = -2 * pow(t, 3) + 3 * pow(t, 2);
		double t3 = pow(t, 3) - 2 * pow(t, 2) + t;
		double t4 = pow(t, 3) - pow(t, 2);

		glVertex2d(p0.x*t1 + p1.x*t2 + tempC0.x*t3 + tempC1.x*t4, p0.y*t1 + p1.y*t2 + tempC0.y*t3 + tempC1.y*t4);
	}
	glEnd();
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);       //清除。GL_COLOR_BUFFER_BIT表示清除颜色

	glPointSize(10.0f);
	glColor3f(0, 0, 1);
	//画出型值点和控制点（蓝色）
	glBegin(GL_POINTS);
	glVertex2d(p0.x, p0.y);
	glVertex2d(p1.x, p1.y);
	glVertex2d(c0.x, c0.y);
	glVertex2d(c1.x, c1.y);
	glEnd();

	//画出控制点与型值点的连线（红色）
	glColor3f(1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2d(p0.x, p0.y);    glVertex2d(c0.x, c0.y);
	glVertex2d(p1.x, p1.y);    glVertex2d(c1.x, c1.y);
	glEnd();

	Hermite(200);

	glFlush();
	glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)       //监听鼠标动作
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftIsDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouseLeftIsDown = false;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouseRightIsDown = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mouseRightIsDown = false;
	}
}
void motion(int x, int y)       //移动点
{
	GLfloat x0 = x;
	GLfloat y0 = y;
	Vertex mouse{ x0,y0 };
	ChangeMouse(mouse);
	if (mouseLeftIsDown)        //左键移动控制点
	{
		if (caculateSquareDistance(mouse, c0) < 0.6)     //防止鼠标移动过快点位无法及时读取，经测试，400为一个较适合的值
		{
			c0.x = mouse.x;
			c0.y = mouse.y;
		}
		else if (caculateSquareDistance(mouse, c1) < 0.6)
		{
			c1.x = mouse.x;
			c1.y = mouse.y;
		}
	}
	else if (mouseRightIsDown)      //右键移动型值点
	{
		if (caculateSquareDistance(mouse, p0) < 0.6)
		{
			p0.x = mouse.x;
			p0.y = mouse.y;
		}
		else if (caculateSquareDistance(mouse, p1) < 0.6)
		{
			p1.x = mouse.x;
			p1.y = mouse.y;
		}
	}
	glutPostRedisplay();        //重新构图
}
void ChangeSize(GLsizei w, GLsizei h)
{
	/*
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	if (w <= h)
		glOrtho(-400.0, 500.0, -400.0 / aspectRatio, 500.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-400.0*aspectRatio, 500.0*aspectRatio, -400.0, 500.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	W = w;
	H = h;
	glViewport(0, 0, w, h);
	double aspectRatio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10/aspectRatio, 10/aspectRatio);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Hermit");

	puts("\n\t使用Hermite算法，用两顶点两控制点绘制三次曲线。");
	puts("\t左键移动控制点，右键移动型值点");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();

	return 0;
}