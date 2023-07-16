
#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "OpenGL纹理测试"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

//定义两个纹理对象编号
GLuint texGround;
GLuint texWall;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
static GLfloat angle = 0.0f;   //旋转角度

// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE * pFile;
	fopen_s(&pFile, file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}


void display(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置视角
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(75, 1, 1, 21);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(-4, 7, 7, 0, 0, 0, 0, 0, 1);

	//glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转

	/*
	// 绘制底面以及纹理
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 3.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	// 绘制立面
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	//绘制另外一个立面
	glBegin(GL_QUADS);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
	glEnd();
	*/
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); // 设置纹理贴图方式

	GLUquadricObj* pSphere = gluNewQuadric();

	gluQuadricDrawStyle(pSphere, GL_FILL);

	gluQuadricNormals(pSphere, GLU_SMOOTH);

	gluQuadricTexture(pSphere, true);
	glBindTexture(GL_TEXTURE_2D, texGround);
	gluSphere(pSphere,6, 60, 60);
	glPushMatrix();
	glTranslatef(60.0, 60, 0.0);

	//gluSphere(pSphere, 1, 30, 30);
	glPopMatrix();

	/*
	//太阳光源   
	GLfloat sun_ambient[] = { 1.0 , 1.0 , 1.0 , 0.0 };
	GLfloat sun_diffuse[] = { 1.0 , 1.0 , 1.0 , 1.0 };
	GLfloat sun_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
	GLfloat sun_position[] = { 0.0 , 0.0 , 0.0 , 1.0 };

	//行星材质   
	GLfloat planet_ambient[] = { 0.01 , 0.01 , 0.01 , 1.0 };
	GLfloat planet_diffuse[] = { 0.7 , 0.7 , 0.7 , 1.0 };
	GLfloat planet_specular[] = { 0.5 , 0.5 , 0.5 , 0.5 };
	GLfloat planet_specular_parameter[] = { 120.0 };

	//材质自发光   
	GLfloat planet_self_emission[] = { 0.01 , 0.01 , 0.01 , 1.0 };


	//全局光照系数   
	GLfloat globel_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	glMaterialfv(GL_FRONT, GL_EMISSION, planet_self_emission);

	//设置只有正面多边形进行光照计算   
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	//全局光照   
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glEnable(GL_LIGHTING);

	//太阳光源   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	glEnable(GL_LIGHT0);

	//glutSolidTeapot(2.0);
	

	//开启纹理效果   
	glEnable(GL_TEXTURE_2D);
	//开启纹理映射对象的纹理映射开关   
	//gluQuadricTexture(g_text, GL_TRUE);


	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_TEXTURE_2D);
	*/

	glutSwapBuffers();
}

void myIdle(void)
{
	angle += 0.18f;
	if (angle >= 360.0f)
		angle = 0.0f;
	display();
}



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

}

GLfloat centx(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3) {
	return (x1 + x2 + x3) / 3;
}
GLfloat centy(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3) {
	return (y1 + y2 + y3) / 3;
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



int main(int argc, char* argv[])
{
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    // 启用纹理
	texGround = load_texture("earth.bmp");  //加载纹理
	texWall = load_texture("earth.bmp");
	glutDisplayFunc(&display);   //注册函数 
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(&myIdle);
	glutMainLoop(); //循环调用
	return 0;
}

