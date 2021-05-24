#pragma once
#include<GL/glut.h>
//太阳光源   
GLfloat sun_ambient[] = { 0 , 0 , 0 , 1.0 };
GLfloat sun_diffuse[] = { 1.0 , 1.0 , 1.0 , 1.0 };
GLfloat sun_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
GLfloat sun_position[] = { 0.0 , 0.0 , 0.0 , 1.0 };

//全局光照系数   
GLfloat globel_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };

//行星材质   
GLfloat planet_ambient[] = { 0.01 , 0.01 , 0.01 , 1.0 };
GLfloat planet_diffuse[] = { 0.7 , 0.7 , 0.7 , 1.0 };
GLfloat planet_specular[] = { 0.5 , 0.5 , 0.5 , 0.5 };
GLfloat planet_specular_parameter[] = { 120.0 };

//材质自发光   
GLfloat planet_self_emission[] = { 0.1 , 0.1 , 0.1 , 1.0 };

GLfloat sun_self_emission[] = { 2 , 2 , 2 , 1.0 };
