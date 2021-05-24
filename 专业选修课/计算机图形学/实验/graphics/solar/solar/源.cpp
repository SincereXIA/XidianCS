#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include<memory> 
#include <cmath>
#include "light.h"
#include "tex.h"
#include "lookat.h"

using namespace std;

int currentMode = 0;
int time = 0;
const int ModeNums = 2;

//定义纹理对象编号
GLuint texGround;
GLuint sun;
GLuint moon;
GLuint earth;

void init()
{
	glClearColor(0, 0, 0, 0);
	//开启深度Z缓存   
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	//设置只有正面多边形进行光照计算   
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	//全局光照   
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	//glEnable(GL_LIGHTING);

	//太阳光源   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	glEnable(GL_LIGHT0);

	//启用颜色追踪
	glEnable(GL_COLOR_MATERIAL);

	//多边形正面材料环境和散射颜色 追踪glcolor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//进行了一些参数设置
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//放大过滤器：线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//缩小过滤器：线性过滤


	//指定环境模式为：纹理单位颜色与几何图形颜色相乘。
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);

	//开启纹理效果   
	glEnable(GL_TEXTURE_2D);
	earth = load_texture("earth.bmp");  //加载纹理
	moon = load_texture("moon.bmp");
	sun = load_texture("sun.bmp");

	//设置星体的材质   
	glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, planet_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, planet_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, planet_specular_parameter);
	glMaterialfv(GL_FRONT, GL_EMISSION, planet_self_emission);

}






void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	LookAt();


	glTexEnvi(GL_MODULATE, GL_TEXTURE_ENV_MODE, GL_DECAL); // 设置纹理贴图方式
	GLUquadricObj* pSphere = gluNewQuadric();
	gluQuadricDrawStyle(pSphere, GL_FILL);
	gluQuadricNormals(pSphere, GLU_SMOOTH);
	gluQuadricTexture(pSphere, true);

	glMaterialfv(GL_FRONT, GL_EMISSION, sun_self_emission);
	glBindTexture(GL_TEXTURE_2D, sun);

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(time / 100.0, 0.0f, 0.0f, 1.0f); //旋转
	glEnable(GL_TEXTURE_2D);
	gluSphere(pSphere, 10, 30, 30);				//太阳
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	glMaterialfv(GL_FRONT, GL_EMISSION, planet_self_emission);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_TEXTURE_2D);


	gluQuadricTexture(pSphere, GL_TRUE);


	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(time / 300.0, 0.0f, 0.0f, 1.0f); //地球公转
	glTranslatef(30.0, 0.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, earth);

	glPushMatrix();
	//glRotatef(-90, 1, 0, 0);
	glRotatef(time/3, 0.0f, 0.0f, 1.0f); //地球自转
	gluSphere(pSphere, 2, 30, 30);

	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, moon);
	glPushMatrix();
	//glRotatef(-90, 1, 0, 0);
	
	glRotatef(time/30.0, 0.0f, 0.0f, 1.0f); //月球公转
	glTranslatef(5.0, 0.0, 0.0);
	gluSphere(pSphere, 0.4, 60, 60);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
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
	gluPerspective(60, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void timer(int value)
{
	time += 1;
	time = time % (365*24*100);
	glutTimerFunc(1, timer, 0);
	glutPostRedisplay();
}




int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(360, 360);
	glutCreateWindow("KeyboardFunc");

	init();
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}