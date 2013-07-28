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

Mat histImage(Mat src){
	Mat dst(cv::Size(640,480), CV_8UC3, cv::Scalar::all(255));
	if(src.empty()) return dst; 

	// �q�X�g�O������`�悷��摜���蓖��
	const int ch_width = 260, ch_height=200;
	cv::Mat hist_img(cv::Size(ch_width, ch_height), CV_8UC3, cv::Scalar::all(255));

	cv::Mat hist;
	const int hdims[] = {256}; // �������̃q�X�g�O�����T�C�Y
	const float hranges[] = {0,256};
	const float* ranges[] = {hranges}; // �������̃r���̉������
	double max_val = .0;

	// �V���O���`�����l���̃q�X�g�O�����v�Z
	// �摜�i�����j�C�摜�����C�v�Z����`�����l���C�}�X�N�C�q�X�g�O�����i�o�́j�C
	// �q�X�g�O�����̎����C�q�X�g�O�����r���̉������
	cv::calcHist(&src, 1, 0, cv::Mat(), hist, 1, hdims, ranges);

	// �ő�l�̌v�Z
	cv::minMaxLoc(hist, 0, &max_val);

	// �q�X�g�O�����̃X�P�[�����O�ƕ`��
	cv::Scalar color = cv::Scalar::all(100);
	// �X�P�[�����O
	hist = hist * (max_val? ch_height/max_val:0.);
	for(int j=0; j<hdims[0]; ++j) {
		int bin_w = cv::saturate_cast<int>((double)ch_width/hdims[0]);
		cv::rectangle(hist_img, 
			cv::Point(j*bin_w, hist_img.rows),
			cv::Point((j+1)*bin_w, hist_img.rows-cv::saturate_cast<int>(hist.at<float>(j))),
			color, -1);
	}
	
	return hist_img;
}