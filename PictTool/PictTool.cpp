#include "PictTool.h"

using namespace PictTool;
using namespace System::Runtime::InteropServices;
//String�^��char�^�փL���X�g����ꍇ�AMarshal�N���X-StringToHGlobalAnsi���\�b�h���g�p


IplImage *inputImage;//���͉摜
IplImage *resizetemp;//���T�C�Y�p
IplImage *tempImage;//��Ɨ̈�
IplImage *tempImage2;//��Ɨ̈�
IplImage *tempImage3;//��Ɨ̈�

string cascadeName = "data\\haarcascade_frontalface_alt.xml";//�w�K�ς݌��o��
CascadeClassifier cascade;

//==============================================================================================
//���j���[�X�g���b�v�́u�J���v���I�����ꂽ��
System::Void picttoolForm::�J��ToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{
	//�����ǂݍ���
	// �w�K�ς݌��o��̓ǂݍ���
    if(!cascade.load(cascadeName)){
		cout<<"���o�킪�ǂݍ��߂܂���ł���"<<endl;
	}

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
	resizetemp = resizeImage(inputImage);
	cvShowImage("INPUT", resizetemp);


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

	//�`�F�b�N�{�b�N�X�́u��]�v��(�I�u�W�F�N�g���FcheckBox_rotate)
	//===�Q�l�����A��]�Ƀ`�F�b�N�������Ă���ꍇ�̂ݏ��������s
	if((checkBox_rotate->CheckState == System::Windows::Forms::CheckState::Checked))
	{
		//MessageBox::Show("���b�Z�[�W���e","���b�Z�[�W�{�b�N�X��","���b�Z�[�W�{�b�N�X�̃{�^���̎��")
		MessageBox::Show(
			"�摜�̉�]�̊p�x���g���b�N�o�[�Ō��肵�܂��B�e�L�X�g�{�b�N�X�̒l��臒l�ł��B\n�g���b�N�o�[�𓮂����Ȃ��Ɖ�]�͊J�n����܂���",
			"�g�p��̒���",
			MessageBoxButtons::OK);

		cvNamedWindow("ROTATE", 1);
		// �}�E�X�R�[���o�b�N�֐��̐ݒ�
		cvSetMouseCallback("ROTATE", onMouse, "ROTATE");
		tempImage3 = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U,3);
	}

	//�������̉��
	Marshal::FreeHGlobal(IntPtr(filename));
}

//==============================================================================================
//���j���[�X�g���b�v�́u�J���v���I�����ꂽ��
System::Void picttoolForm::�t�H���_�I��ToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
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
	//�ҏW���₷���悤�Ɉ��̃T�C�Y�ɉ摜��ύX
	int inputw = inputImage->width;
	int inputh = inputImage->height;
	int M = max(inputw, inputh);//�c���̑傫�������擾
	int m = min(inputw, inputh);
	int o = 600 * m / M;
	if(M == inputw) resizetemp = cvCreateImage( cvSize(600,o),IPL_DEPTH_8U, 3);
	else  resizetemp = cvCreateImage( cvSize(o,600),IPL_DEPTH_8U, 3);
	cvResize(inputImage,resizetemp,CV_INTER_CUBIC);
	inputImage = cvCloneImage(resizetemp);
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

	//�`�F�b�N�{�b�N�X�́u��]�v��(�I�u�W�F�N�g���FcheckBox_rotate)
	//===�Q�l�����A��]�Ƀ`�F�b�N�������Ă���ꍇ�̂ݏ��������s
	if((checkBox_rotate->CheckState == System::Windows::Forms::CheckState::Checked))
	{
		//MessageBox::Show("���b�Z�[�W���e","���b�Z�[�W�{�b�N�X��","���b�Z�[�W�{�b�N�X�̃{�^���̎��")
		MessageBox::Show(
			"�摜�̉�]�̊p�x���g���b�N�o�[�Ō��肵�܂��B�e�L�X�g�{�b�N�X�̒l��臒l�ł��B\n�g���b�N�o�[�𓮂����Ȃ��Ɖ�]�͊J�n����܂���",
			"�g�p��̒���",
			MessageBoxButtons::OK);

		cvNamedWindow("ROTATE", 1);
		// �}�E�X�R�[���o�b�N�֐��̐ݒ�
		cvSetMouseCallback("ROTATE", onMouse, "ROTATE");
		tempImage3 = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U,3);
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
//�g���b�N�o�[���쎞�ɌĂяo����]�֐�
System::Void picttoolForm::rotate(IplImage *input, IplImage *output)
{
	//�e�L�X�g�{�b�N�X�̒l��int�^�ɃL���X�g�ɂ��Ď�肾��
	int r = int::Parse(textBox_rot_value->Text);

	//��]����
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
	

	//�猟�o�e�X�g
	Mat temp3(tempImage3);
	// �P�x�摜�ɕϊ�
    Mat grayImage;
    cvtColor(temp3, grayImage, CV_RGB2GRAY);
	// �猟�o�����s
    vector<Rect> faces;
    cascade.detectMultiScale(
        grayImage,   // �摜
        faces,       // �o�͂�����`
        1.1,         // �k���p�̃X�P�[��
        2,           // �ŏ��̓��[��
        CV_HAAR_SCALE_IMAGE,  // �t���O
		cv::Size(30, 30) // �ŏ��̋�`
    );
    // ��`��`��
    for (vector<Rect>::iterator iter = faces.begin(); iter != faces.end(); iter ++) {
        rectangle(temp3, *iter, Scalar(255, 0, 0), 5);
    }
	
	imshow("ROTATE", resizeImage(temp3));
}


//==============================================================================================
//�o�C�i���g���b�N�o�[���쎞�̏���
System::Void picttoolForm::trackBar_binary_Scroll(System::Object ^sender, System::EventArgs ^e)
{
	//�e�L�X�g�{�b�N�X�ɃX�N���[���o�[�̒l���L�q����
	textBox_bin_value->Text = System::String::Concat("", trackBar_binary->Value);
	binary(tempImage, tempImage2);
}

//==============================================================================================
//���[�e�[�g�g���b�N�o�[���쎞�̏���
System::Void picttoolForm::trackBar_rotate_Scroll(System::Object ^sender, System::EventArgs ^e)
{
	//�e�L�X�g�{�b�N�X�ɃX�N���[���o�[�̒l���L�q����
	textBox_rot_value->Text = System::String::Concat("", trackBar_rotate->Value);
	rotate(inputImage, tempImage3);
}

//���j���[�X�g���b�v�́u�I���v���I�����ꂽ�烁��������ƃE�B���h�E�j��
System::Void picttoolForm::�I��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	cvReleaseImage(&inputImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&tempImage2);
	cvDestroyAllWindows();
}

// �R�[���o�b�N�֐�
void onMouse(int event, int x, int y, int flags, void* param){
	// event�ɋN�����C�x���g�̎�ނ��i�[�����
	// flags�ɋ��N�����C�x���g���܂܂�Ă���
	if(event == CV_EVENT_LBUTTONDOWN && !strcmp((char*)param, "ROTATE")){
		printf("x:%03d y:%03d\n", x, y);
	}
	char str[64];
	static int line = 0;
	const int max_line = 15, w = 15, h = 30;

	//�}�E�X�C�x���g���擾
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MOUSE_MOVE");
		break;
	case CV_EVENT_LBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOWN");
		break;
	case CV_EVENT_RBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOWN");
		break;
	case CV_EVENT_MBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOWN");
		break;
	case CV_EVENT_LBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_UP");
		break;
	case CV_EVENT_RBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_UP");
		break;
	case CV_EVENT_MBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_UP");
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOUBLE_CLICK");
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOUBLE_CLICK");
		break;
	case CV_EVENT_MBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOUBLE_CLICK");
		break;
	}
	// (5)�}�E�X�{�^���C�C���L�[���擾
	if (flags & CV_EVENT_FLAG_LBUTTON)
		strncat (str, " + LBUTTON", 64);
	if (flags & CV_EVENT_FLAG_RBUTTON)
		strncat (str, " + RBUTTON", 64);
	if (flags & CV_EVENT_FLAG_MBUTTON)
		strncat (str, " + MBUTTON", 64);
	if (flags & CV_EVENT_FLAG_CTRLKEY)
		strncat (str, " + CTRL", 64);
	if (flags & CV_EVENT_FLAG_SHIFTKEY)
		strncat (str, " + SHIFT", 64);
	if (flags & CV_EVENT_FLAG_ALTKEY)
		strncat (str, " + ALT", 64);

	cout<< str << endl;

	//�l�p�̕`��
	// Green�C����5�C8�ߖT�A��
    cvRectangle(tempImage3, cv::Point(x-200,y-200), cv::Point(x+200, y+200), cv::Scalar(0,200,0), 5, 8);
	//cvShowImage("ROTATE", tempImage3);
}

[STAThreadAttribute]
int main( array<System::String ^> ^args )
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault( false );
	Application::Run( gcnew picttoolForm() );
	return 0;
}