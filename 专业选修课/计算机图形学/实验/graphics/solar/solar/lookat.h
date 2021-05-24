#pragma once
void RotateLeft();
void RotateRight();
void MoveForward();
void MoveBackward();
void RotateUp();
void RotateDown();
void LookAt();
void myKey(unsigned char key, int x, int y); //响应ASCII对应键，鼠标的当前x和y位置也被返回。
void MouseFunc(int button, int state, int x, int y);
void MouseMotion(int x, int y);