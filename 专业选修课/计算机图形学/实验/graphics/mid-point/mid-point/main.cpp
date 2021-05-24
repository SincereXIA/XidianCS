#include <gl/glut.h>
struct Color
{
	double r;
	double g;
	double b;
};
void MidPointLine(GLint x0, GLint y0, GLint x1, GLint y1, Color color);
void MidpointCircle(GLint radius, GLint xc, GLint yc, Color color);

//设置渲染状态
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
//绘制场景
void RenderScene()
{
	Color RED{ 1.0,0,0 };
	Color BLUE{ 0,0,1.0 };
	glClear(GL_COLOR_BUFFER_BIT);//用当前清除颜色清除窗口
	
	MidPointLine(-60, 70, -15, 77,RED);
	MidPointLine(-15, 77, -20, 35, RED);
	MidPointLine(-20, 35, -65, 23, RED);
	MidPointLine(-65, 23, -75, -20, RED);
	MidPointLine(-75, -20, -17, -7, RED);
	MidPointLine(-17, -7, -23, -79, RED);
	MidPointLine(-23, -79, -45, -70, RED);
	MidPointLine(46, 77, 22, 13, RED);
	MidPointLine(-3, -2, 64, 5, RED);
	MidPointLine(12, 80, 10, -74, RED);
	MidPointLine(13, -3, 79, -56, RED);
	MidPointLine(8, -76, 38, -60, RED);
	MidpointCircle(90, 0, 0, RED);
	MidpointCircle(15, 60, -60, BLUE);
	
	glFlush();//刷新绘图命令
}

void MidPointLine(GLint x0, GLint y0, GLint x1, GLint y1, Color color) {


	int dx, dy, incrE, incrNE, d, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	double k;
	if (dx != 0)	k = (double) dy / dx;
	else k = 255*dy;

	x = x0;
	y = y0;
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2i(x, y);
	if (k >= 0 && k < 1) {
		if (x0 > x1)	return MidPointLine(x1, y1, x0, y0, color);
		d = dx - 2 * dy;
		incrE = -2 * dy;
		incrNE = 2 * (dx - dy);
		while (x < x1) {
			if (d > 0)	d += incrE;
			else {
				d += incrNE;
				y++;
			}
			x++;
			glVertex2i(x, y);
		}
		glEnd();
	}
	else if (k <= 0 && k >-1){
		if (x0 > x1)	return MidPointLine(x1, y1, x0, y0, color);
		d = dx + 2 * dy;
		incrE = 2 * dy;
		incrNE = 2 * (dx + dy);
		while (x < x1) {
			if (d > 0)	d += incrE;
			else {
				d += incrNE;
				y--;
			}
			x++;
			glVertex2i(x, y);
		}
		glEnd();
	}
	else if (k >= 0 && k >= 1) {
		if (y0 > y1)	return MidPointLine(x1, y1, x0, y0, color);
		d = -dy + 2 * dx;
		incrE = 2 * dx;
		incrNE = 2 * (-dy + dx);
		while (y < y1) {
			if (d < 0)	d += incrE;
			else {
				d += incrNE;
				x++;
			}
			y++;
			glVertex2i(x, y);
		}
		glEnd();
	}
	else  {
		if (y0 < y1)	return MidPointLine(x1, y1, x0, y0, color);
		d = -dy - 2 * dx;
		incrE = -2 * dx;
		incrNE = 2 * (-dy - dx);
		while (y > y1) {
			if (d > 0)	d += incrE;
			else {
				d += incrNE;
				x++;
			}
			y--;
			glVertex2i(x, y);
		}
		glEnd();
	}

	

}
void MidpointCircle(GLint radius, GLint xc, GLint yc, Color color)
{
	GLint x, y, d;
	x = 0, y = radius, d = 1 - radius;
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2i(xc, yc + y);
	while (y > x)
	{
		if (d < 0)//此时在第二个八分圆处，中点在圆内，选上方的点 
		{
			d += x * 2 + 3;
			x++;
		}
		else
		{
			d += (x - y) * 2 + 5;
			x++; y--;
		}
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc - x, yc + y);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc - y);
		glVertex2i(xc + y, yc + x);
		glVertex2i(xc - y, yc + x);
		glVertex2i(xc + y, yc - x);
		glVertex2i(xc - y, yc - x);
	}
	glEnd();
}



void changeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Simple");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);

	glutMainLoop();
}
