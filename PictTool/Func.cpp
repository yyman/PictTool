#include "PictTool.h"

IplImage* resizeImage(IplImage *src){
	IplImage *dst;
	
	//編集しやすいように一定のサイズに画像を変更
	int inputw = src->width;
	int inputh = src->height;
	int M = max(inputw, inputh);//縦横の大きい方を取得
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw) dst = cvCreateImage( cvSize(600,o),IPL_DEPTH_8U, 3);
	else  dst = cvCreateImage( cvSize(o,600),IPL_DEPTH_8U, 3);
	cvResize(src,dst,CV_INTER_CUBIC);

	return dst;
}

Mat resizeImage(Mat src){
	Mat dst;
	
	//編集しやすいように一定のサイズに画像を変更
	int inputw = src.cols;
	int inputh = src.rows;
	int M = max(inputw, inputh);//縦横の大きい方を取得
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw)
		resize(src,dst,cv::Size(600,o));
	else
		resize(src,dst,cv::Size(o,600));

	return dst;
}