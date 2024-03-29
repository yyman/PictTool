#include "PictTool.h"

using namespace PictTool;
using namespace System::Runtime::InteropServices;
//String型をchar型へキャストする場合、Marshalクラス-StringToHGlobalAnsiメソッドを使用

IplImage *inputImage;//入力画像
IplImage *resizetemp;//リサイズ用
IplImage *tempImage;//作業領域
IplImage *tempImage2;//作業領域
IplImage *tempImage3;//作業領域




//==============================================================================================
//メニューストリップの「開く」が選択された時
System::Void picttoolForm::開くToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{

	//flags=1は画像サイズに合わせてウィンドウが作られるので、ウィンドウ固定。
	//ウィンドウ可変にしたい場合はflags=0にしておく
	cvNamedWindow("INPUT", 1);   
	char *filename;

	//openFileDialogの使用
	//===フィルタプロパティ：拡張子制限
	openFileDialog->Filter = "JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|PPM(*.ppm)|*.ppm";

	//ディレクトリ一覧でOKが押されなかった場合は読み込み失敗
	if(openFileDialog->ShowDialog() != Windows::Forms::DialogResult::OK)
	{
		MessageBox::Show("openFileDialogで落ちました");
		return;
	}

	//=FileNameプロパティでファイル名を得る。
	//===String型になっているため、char*へキャストします
	filename = (char*)Marshal::StringToHGlobalAnsi(openFileDialog->FileName).ToPointer();

	//入力画像確保
	inputImage = cvLoadImage(filename);
	//編集しやすいように一定のサイズに画像を変更
	int inputw = inputImage->width;
	int inputh = inputImage->height;
	int M = max(inputw, inputh);//縦横の大きい方を取得
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw) resizetemp = cvCreateImage( cvSize(600,o),IPL_DEPTH_8U, 3);
	else  resizetemp = cvCreateImage( cvSize(o,600),IPL_DEPTH_8U, 3);
	cvResize(inputImage,resizetemp,CV_INTER_CUBIC);
	inputImage = cvCloneImage(resizetemp);
	cvShowImage("INPUT", inputImage);


	//==============================チェックボックスによる条件分岐=============================//
	//チェックボックスの「グレースケール化」＝(オブジェクト名：checkBox_gray)
	//===チェックが入っている場合に処理を実行する
	if(checkBox_gray->CheckState == System::Windows::Forms::CheckState::Checked)
	{
		cvNamedWindow("GRAY", 1);
		tempImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

		//cvCvtColor(IplImage* input, IplImage* output, flag)
		//===BGR画像を濃淡画像へ変化させる場合はCV_BGR2GRAYを使用
		cvCvtColor(inputImage, tempImage, CV_BGR2GRAY);
		cvShowImage("GRAY", tempImage);
	}

	//チェックボックスの「2値化」＝(オブジェクト名：checkBox_binary)
	//===２値化かつ、グレースケール化にチェックが入っている場合のみ処理を実行
	if((checkBox_gray->CheckState == System::Windows::Forms::CheckState::Checked) 
		&&(checkBox_binary->CheckState == System::Windows::Forms::CheckState::Checked))
	{

		//MessageBox::Show("メッセージ内容","メッセージボックス名","メッセージボックスのボタンの種類")
		MessageBox::Show(
			"2値化の閾値をトラックバーで決定します。テキストボックスの値が閾値です。\nトラックバーを動かさないと2値化は開始されません",
			"使用上の注意",
			MessageBoxButtons::OK);

		cvNamedWindow("BINARY", 1);
		tempImage2 = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U,1);
	}

	//チェックボックスの「回転」＝(オブジェクト名：checkBox_rotate)
	//===２値化かつ、回転にチェックが入っている場合のみ処理を実行
	if((checkBox_rotate->CheckState == System::Windows::Forms::CheckState::Checked))
	{
		//MessageBox::Show("メッセージ内容","メッセージボックス名","メッセージボックスのボタンの種類")
		MessageBox::Show(
			"画像の回転の角度をトラックバーで決定します。テキストボックスの値が閾値です。\nトラックバーを動かさないと回転は開始されません",
			"使用上の注意",
			MessageBoxButtons::OK);

		cvNamedWindow("ROTATE", 1);
		// マウスコールバック関数の設定
		cvSetMouseCallback("ROTATE", onMouse, "ROTATE");
		tempImage3 = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U,3);
	}

	//メモリの解放
	Marshal::FreeHGlobal(IntPtr(filename));
}




//==============================================================================================
//メニューストリップの「セーブ」が選択された時
System::Void picttoolForm::セーブToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{
	char* filename;
	saveFileDialog->Filter = "JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|PPM(*.ppm)|*.ppm";
	//saveFileDialogの使用
	if(saveFileDialog->ShowDialog() != Windows::Forms::DialogResult::OK)
	{
		MessageBox::Show("saveFileDialogで落ちました");
		return;
	}

	//openFileDialog同様に、Stringをchar*へキャストしてcvSaveImageで保存
	filename = (char*)Marshal::StringToHGlobalAnsi(saveFileDialog->FileName).ToPointer();
	cvSaveImage(filename, tempImage);   
	//グレースケールならtempImage, ２値化画像ならtempImage2

	//メモリの解放
	Marshal::FreeHGlobal(IntPtr(filename));
}


//==============================================================================================
//トラックバー動作時に呼び出す２値化関数
System::Void picttoolForm::binary(IplImage *input, IplImage *output)
{
	//テキストボックスの値をint型にキャストにして取りだす
	int levels = int::Parse(textBox_bin_value->Text);

	//２値化処理
	//===cvThreshold(入力、出力、閾値、最大値、フラグ)
	cvThreshold(input, output, levels, 255, CV_THRESH_BINARY);
	cvShowImage("BINARY", tempImage2);
}


//==============================================================================================
//トラックバー動作時に呼び出す回転関数
System::Void picttoolForm::rotate(IplImage *input, IplImage *output)
{
	//テキストボックスの値をint型にキャストにして取りだす
	int r = int::Parse(textBox_rot_value->Text);

	//回転処理
	CvMat M;
	float m[6];
	double rad = r * PI / 180.0;

	m[0] = (float) (cos(rad));
	m[1] = (float) (-sin(rad));
	m[2] = inputImage->width * 0.5;
	m[3] = -m[1];
	m[4] = m[0];
	m[5] = inputImage->height * 0.5;
	cvInitMatHeader (&M, 2, 3, CV_32FC1, m, CV_AUTOSTEP);
	cvGetQuadrangleSubPix (inputImage, tempImage3, &M);
	cvShowImage("ROTATE", tempImage3);
}


//==============================================================================================
//バイナリトラックバー動作時の処理
System::Void picttoolForm::trackBar_binary_Scroll(System::Object ^sender, System::EventArgs ^e)
{
	//テキストボックスにスクロールバーの値を記述する
	textBox_bin_value->Text = System::String::Concat("", trackBar_binary->Value);
	binary(tempImage, tempImage2);
}

//==============================================================================================
//ローテートトラックバー動作時の処理
System::Void picttoolForm::trackBar_rotate_Scroll(System::Object ^sender, System::EventArgs ^e)
{
	//テキストボックスにスクロールバーの値を記述する
	textBox_rot_value->Text = System::String::Concat("", trackBar_rotate->Value);
	rotate(inputImage, tempImage3);
}

//メニューストリップの「終了」が選択されたらメモリ解放とウィンドウ破棄
System::Void picttoolForm::終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	cvReleaseImage(&inputImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&tempImage2);
	cvDestroyAllWindows();
}

// コールバック関数
void onMouse(int event, int x, int y, int flags, void* param){
	// eventに起きたイベントの種類が格納される
	// flagsに共起したイベントが含まれている
	if(event == CV_EVENT_LBUTTONDOWN && !strcmp((char*)param, "ROTATE")){
		printf("x:%03d y:%03d\n", x, y);
	}
}

[STAThreadAttribute]
int main( array<System::String ^> ^args )
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault( false );
	Application::Run( gcnew picttoolForm() );
	return 0;
}