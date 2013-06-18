#include "PictTool.h"

IplImage* resizeImage(IplImage *src){
	IplImage *dst;
	
	//�ҏW���₷���悤�Ɉ��̃T�C�Y�ɉ摜��ύX
	int inputw = src->width;
	int inputh = src->height;
	int M = max(inputw, inputh);//�c���̑傫�������擾
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw) dst = cvCreateImage( cvSize(600,o),IPL_DEPTH_8U, 3);
	else  dst = cvCreateImage( cvSize(o,600),IPL_DEPTH_8U, 3);
	cvResize(src,dst,CV_INTER_CUBIC);

	return dst;
}

Mat resizeImage(Mat src){
	Mat dst;
	
	//�ҏW���₷���悤�Ɉ��̃T�C�Y�ɉ摜��ύX
	int inputw = src.cols;
	int inputh = src.rows;
	int M = max(inputw, inputh);//�c���̑傫�������擾
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw)
		resize(src,dst,cv::Size(600,o));
	else
		resize(src,dst,cv::Size(o,600));

	return dst;
}