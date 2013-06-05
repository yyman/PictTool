#include "PictTool.h"

using namespace PictTool;
using namespace System::Runtime::InteropServices;
//String型をchar型へキャストする場合、Marshalクラス-StringToHGlobalAnsiメソッドを使用

IplImage *inputImage;//入力画像
IplImage *tempImage;//作業領域
IplImage *tempImage2;//作業領域




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
//トラックバー動作時の処理
System::Void picttoolForm::trackBar_binary_Scroll(System::Object ^sender, System::EventArgs ^e)
{
//テキストボックスにスクロールバーの値を記述する
   textBox_bin_value->Text = System::String::Concat("", trackBar_binary->Value);
   binary(tempImage, tempImage2);
}

//メニューストリップの「終了」が選択されたらメモリ解放とウィンドウ破棄
System::Void picttoolForm::終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   cvReleaseImage(&inputImage);
   cvReleaseImage(&tempImage);
   cvReleaseImage(&tempImage2);
   cvDestroyAllWindows();
}

[STAThreadAttribute]
int main( array<System::String ^> ^args )
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault( false );
	Application::Run( gcnew picttoolForm() );
	return 0;
}