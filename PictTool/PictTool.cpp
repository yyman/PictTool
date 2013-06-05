#include "PictTool.h"

using namespace PictTool;
using namespace System::Runtime::InteropServices;
//String�^��char�^�փL���X�g����ꍇ�AMarshal�N���X-StringToHGlobalAnsi���\�b�h���g�p

IplImage *inputImage;//���͉摜
IplImage *tempImage;//��Ɨ̈�
IplImage *tempImage2;//��Ɨ̈�




//==============================================================================================
//���j���[�X�g���b�v�́u�J���v���I�����ꂽ��
System::Void picttoolForm::�J��ToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{

//flags=1�͉摜�T�C�Y�ɍ��킹�ăE�B���h�E�������̂ŁA�E�B���h�E�Œ�B
//�E�B���h�E�ςɂ������ꍇ��flags=0�ɂ��Ă���
	  cvNamedWindow("INPUT", 1);   
	  char *filename;

//openFileDialog�̎g�p
//===�t�B���^�v���p�e�B�F�g���q����
   openFileDialog->Filter = "JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|PPM(*.ppm)|*.ppm";

//�f�B���N�g���ꗗ��OK��������Ȃ������ꍇ�͓ǂݍ��ݎ��s
   if(openFileDialog->ShowDialog() != Windows::Forms::DialogResult::OK)
   {
      MessageBox::Show("openFileDialog�ŗ����܂���");
      return;
   }

//=FileName�v���p�e�B�Ńt�@�C�����𓾂�B
//===String�^�ɂȂ��Ă��邽�߁Achar*�փL���X�g���܂�
   filename = (char*)Marshal::StringToHGlobalAnsi(openFileDialog->FileName).ToPointer();

//���͉摜�m��
   inputImage = cvLoadImage(filename);
   cvShowImage("INPUT", inputImage);


//==============================�`�F�b�N�{�b�N�X�ɂ���������=============================//
//�`�F�b�N�{�b�N�X�́u�O���[�X�P�[�����v��(�I�u�W�F�N�g���FcheckBox_gray)
//===�`�F�b�N�������Ă���ꍇ�ɏ��������s����
   if(checkBox_gray->CheckState == System::Windows::Forms::CheckState::Checked)
   {
      cvNamedWindow("GRAY", 1);
      tempImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

      //cvCvtColor(IplImage* input, IplImage* output, flag)
      //===BGR�摜��Z�W�摜�֕ω�������ꍇ��CV_BGR2GRAY���g�p
      cvCvtColor(inputImage, tempImage, CV_BGR2GRAY);
      cvShowImage("GRAY", tempImage);
   }

//�`�F�b�N�{�b�N�X�́u2�l���v��(�I�u�W�F�N�g���FcheckBox_binary)
//===�Q�l�����A�O���[�X�P�[�����Ƀ`�F�b�N�������Ă���ꍇ�̂ݏ��������s
   if((checkBox_gray->CheckState == System::Windows::Forms::CheckState::Checked) 
      &&(checkBox_binary->CheckState == System::Windows::Forms::CheckState::Checked))
   {

//MessageBox::Show("���b�Z�[�W���e","���b�Z�[�W�{�b�N�X��","���b�Z�[�W�{�b�N�X�̃{�^���̎��")
     MessageBox::Show(
     "2�l����臒l���g���b�N�o�[�Ō��肵�܂��B�e�L�X�g�{�b�N�X�̒l��臒l�ł��B\n�g���b�N�o�[�𓮂����Ȃ���2�l���͊J�n����܂���",
     "�g�p��̒���",
     MessageBoxButtons::OK);

         cvNamedWindow("BINARY", 1);
         tempImage2 = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U,1);
    }

//�������̉��
     Marshal::FreeHGlobal(IntPtr(filename));
}




//==============================================================================================
//���j���[�X�g���b�v�́u�Z�[�u�v���I�����ꂽ��
System::Void picttoolForm::�Z�[�uToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{
   char* filename;
   saveFileDialog->Filter = "JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|PPM(*.ppm)|*.ppm";
//saveFileDialog�̎g�p
   if(saveFileDialog->ShowDialog() != Windows::Forms::DialogResult::OK)
   {
   MessageBox::Show("saveFileDialog�ŗ����܂���");
   return;
   }

//openFileDialog���l�ɁAString��char*�փL���X�g����cvSaveImage�ŕۑ�
   filename = (char*)Marshal::StringToHGlobalAnsi(saveFileDialog->FileName).ToPointer();
   cvSaveImage(filename, tempImage);   
//�O���[�X�P�[���Ȃ�tempImage, �Q�l���摜�Ȃ�tempImage2

//�������̉��
   Marshal::FreeHGlobal(IntPtr(filename));
}


//==============================================================================================
//�g���b�N�o�[���쎞�ɌĂяo���Q�l���֐�
System::Void picttoolForm::binary(IplImage *input, IplImage *output)
{
//�e�L�X�g�{�b�N�X�̒l��int�^�ɃL���X�g�ɂ��Ď�肾��
   int levels = int::Parse(textBox_bin_value->Text);

//�Q�l������
//===cvThreshold(���́A�o�́A臒l�A�ő�l�A�t���O)
   cvThreshold(input, output, levels, 255, CV_THRESH_BINARY);
   cvShowImage("BINARY", tempImage2);
}


//==============================================================================================
//�g���b�N�o�[���쎞�̏���
System::Void picttoolForm::trackBar_binary_Scroll(System::Object ^sender, System::EventArgs ^e)
{
//�e�L�X�g�{�b�N�X�ɃX�N���[���o�[�̒l���L�q����
   textBox_bin_value->Text = System::String::Concat("", trackBar_binary->Value);
   binary(tempImage, tempImage2);
}

//���j���[�X�g���b�v�́u�I���v���I�����ꂽ�烁��������ƃE�B���h�E�j��
System::Void picttoolForm::�I��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
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