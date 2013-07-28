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

Mat histImage(Mat src){
	Mat dst(cv::Size(640,480), CV_8UC3, cv::Scalar::all(255));
	if(src.empty()) return dst; 

	// ヒストグラムを描画する画像割り当て
	const int ch_width = 260, ch_height=200;
	cv::Mat hist_img(cv::Size(ch_width, ch_height), CV_8UC3, cv::Scalar::all(255));

	cv::Mat hist;
	const int hdims[] = {256}; // 次元毎のヒストグラムサイズ
	const float hranges[] = {0,256};
	const float* ranges[] = {hranges}; // 次元毎のビンの下限上限
	double max_val = .0;

	// シングルチャンネルのヒストグラム計算
	// 画像（複数可），画像枚数，計算するチャンネル，マスク，ヒストグラム（出力），
	// ヒストグラムの次元，ヒストグラムビンの下限上限
	cv::calcHist(&src, 1, 0, cv::Mat(), hist, 1, hdims, ranges);

	// 最大値の計算
	cv::minMaxLoc(hist, 0, &max_val);

	// ヒストグラムのスケーリングと描画
	cv::Scalar color = cv::Scalar::all(100);
	// スケーリング
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