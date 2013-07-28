#pragma once

#include "define.h"

//コールバック関数のプロトタイプ
void onMouse(int event, int x, int y, int flags, void* param);

//簡易処理系
IplImage* resizeImage(IplImage *src);
Mat resizeImage(Mat src);
Mat histImage(Mat src);