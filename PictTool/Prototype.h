#pragma once

#include "define.h"

//�R�[���o�b�N�֐��̃v���g�^�C�v
void onMouse(int event, int x, int y, int flags, void* param);

//�ȈՏ����n
IplImage* resizeImage(IplImage *src);
Mat resizeImage(Mat src);
Mat histImage(Mat src);