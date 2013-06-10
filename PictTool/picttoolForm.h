#pragma once

#include <stdio.h>
#include <opencv\cv.h>
#include <opencv2\opencv.hpp>
#include <opencv2\calib3d\calib3d.hpp>

#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"opencv_core245d.lib")
#pragma comment(lib,"opencv_imgproc245d.lib")
#pragma comment(lib,"opencv_highgui245d.lib")
#pragma comment(lib,"opencv_objdetect245d.lib")
#pragma comment(lib,"opencv_contrib245d.lib")
#pragma comment(lib,"opencv_features2d245d.lib")
#pragma comment(lib,"opencv_flann245d.lib")
#pragma comment(lib,"opencv_gpu245d.lib")
#pragma comment(lib,"opencv_legacy245d.lib")
#pragma comment(lib,"opencv_ts245d.lib")
#pragma comment(lib,"opencv_video245d.lib")
#else
//Releaseモードの場合
#pragma comment(lib,"opencv_core245.lib")
#pragma comment(lib,"opencv_imgproc245.lib")
#pragma comment(lib,"opencv_highgui245.lib")
#pragma comment(lib,"opencv_objdetect245.lib")
#pragma comment(lib,"opencv_contrib245.lib")
#pragma comment(lib,"opencv_features2d245.lib")
#pragma comment(lib,"opencv_flann245.lib")
#pragma comment(lib,"opencv_gpu245.lib")
#pragma comment(lib,"opencv_legacy245.lib")
#pragma comment(lib,"opencv_ts245.lib")
#pragma comment(lib,"opencv_video245.lib")
#endif


using namespace cv;

namespace PictTool {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// picttoolForm の概要
	/// </summary>
	public ref class picttoolForm : public System::Windows::Forms::Form
	{
	public:
		picttoolForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~picttoolForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  ファイルToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  セーブToolStripMenuItem;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::CheckBox^  checkBox_gray;
	private: System::Windows::Forms::CheckBox^  checkBox_binary;
	private: System::Windows::Forms::TrackBar^  trackBar_binary;
	private: System::Windows::Forms::TextBox^  textBox_bin_value;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ファイルToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->セーブToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->checkBox_gray = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_binary = (gcnew System::Windows::Forms::CheckBox());
			this->trackBar_binary = (gcnew System::Windows::Forms::TrackBar());
			this->textBox_bin_value = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_binary))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ファイルToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(284, 26);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ファイルToolStripMenuItem
			// 
			this->ファイルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->開くToolStripMenuItem, 
				this->セーブToolStripMenuItem, this->終了ToolStripMenuItem});
			this->ファイルToolStripMenuItem->Name = L"ファイルToolStripMenuItem";
			this->ファイルToolStripMenuItem->Size = System::Drawing::Size(68, 22);
			this->ファイルToolStripMenuItem->Text = L"ファイル";
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->開くToolStripMenuItem->Text = L"開く";
			this->開くToolStripMenuItem->Click += gcnew System::EventHandler(this, &picttoolForm::開くToolStripMenuItem_Click);
			// 
			// セーブToolStripMenuItem
			// 
			this->セーブToolStripMenuItem->Name = L"セーブToolStripMenuItem";
			this->セーブToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->セーブToolStripMenuItem->Text = L"セーブ";
			this->セーブToolStripMenuItem->Click += gcnew System::EventHandler(this, &picttoolForm::セーブToolStripMenuItem_Click);
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->終了ToolStripMenuItem->Text = L"リセット";
			this->終了ToolStripMenuItem->Click += gcnew System::EventHandler(this, &picttoolForm::終了ToolStripMenuItem_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
			// 
			// checkBox_gray
			// 
			this->checkBox_gray->AutoSize = true;
			this->checkBox_gray->Location = System::Drawing::Point(8, 48);
			this->checkBox_gray->Name = L"checkBox_gray";
			this->checkBox_gray->Size = System::Drawing::Size(46, 16);
			this->checkBox_gray->TabIndex = 1;
			this->checkBox_gray->Text = L"gray";
			this->checkBox_gray->UseVisualStyleBackColor = true;
			// 
			// checkBox_binary
			// 
			this->checkBox_binary->AutoSize = true;
			this->checkBox_binary->Location = System::Drawing::Point(8, 80);
			this->checkBox_binary->Name = L"checkBox_binary";
			this->checkBox_binary->Size = System::Drawing::Size(55, 16);
			this->checkBox_binary->TabIndex = 2;
			this->checkBox_binary->Text = L"binary";
			this->checkBox_binary->UseVisualStyleBackColor = true;
			// 
			// trackBar_binary
			// 
			this->trackBar_binary->Location = System::Drawing::Point(8, 136);
			this->trackBar_binary->Maximum = 255;
			this->trackBar_binary->Name = L"trackBar_binary";
			this->trackBar_binary->Size = System::Drawing::Size(264, 45);
			this->trackBar_binary->SmallChange = 5;
			this->trackBar_binary->TabIndex = 3;
			this->trackBar_binary->TickFrequency = 5;
			this->trackBar_binary->Value = 1;
			this->trackBar_binary->ValueChanged += gcnew System::EventHandler(this, &picttoolForm::trackBar_binary_Scroll);
			// 
			// textBox_bin_value
			// 
			this->textBox_bin_value->Location = System::Drawing::Point(200, 112);
			this->textBox_bin_value->Name = L"textBox_bin_value";
			this->textBox_bin_value->Size = System::Drawing::Size(60, 19);
			this->textBox_bin_value->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 120);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(163, 12);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Binary_Threshold_Value(0-255)";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(8, 200);
			this->trackBar1->Maximum = 360;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(264, 45);
			this->trackBar1->SmallChange = 5;
			this->trackBar1->TabIndex = 3;
			this->trackBar1->TickFrequency = 5;
			this->trackBar1->Value = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &picttoolForm::trackBar_binary_Scroll);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(200, 176);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(60, 19);
			this->textBox1->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 184);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Image_Rotate(0-360)";
			// 
			// picttoolForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->textBox_bin_value);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->trackBar_binary);
			this->Controls->Add(this->checkBox_binary);
			this->Controls->Add(this->checkBox_gray);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"picttoolForm";
			this->Text = L"picttoolForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_binary))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	System::Void 開くToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void セーブToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void 終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void binary(IplImage* input, IplImage* output);
	System::Void trackBar_binary_Scroll(System::Object^  sender, System::EventArgs^  e);
};
}
