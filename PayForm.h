#pragma once
#include "Error_Report.h"
#include "main.h"

#include "Error_Report.h"

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <vcclr.h> //System::String * 轉換為 TCHAR*

using namespace sql;

namespace 印表機付費管理 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// PayForm 的摘要
	/// </summary>
	public ref class PayForm : public System::Windows::Forms::Form
	{
	private:
		short dmcopies = 0;
		DWORD TotalPages = 0;
		JOB_INFO_2* pJob;
	private: System::Windows::Forms::Button^  Pay_Butt;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  L_DOCNAME;
	private: System::Windows::Forms::Label^  L_PNTERNAME;
	private: System::Windows::Forms::Label^  L_TOTALPAGES;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  RFID_TextBox;

	private: System::Windows::Forms::Button^  cancel_Butt;

	private: System::Windows::Forms::Label^  L_DMDUPLEX;
	private: System::Windows::Forms::Label^  label6;
			 payarg* payinfo;
	public:
		PayForm(payarg* Jinfo)
		{
			payinfo = Jinfo;
			LPBYTE p = nullptr;
			DWORD cbBuf = 0, ccbBuf = 0;

			if (!GetJob(
				Jinfo->hPrinter,
				payinfo->Jstat->_JobId,
				2,
				p,
				0,
				&cbBuf
			) || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				p = (LPBYTE)malloc(cbBuf);
				GetJob(
					Jinfo->hPrinter,
					Jinfo->Jstat->_JobId,
					2,
					p,
					cbBuf,
					&ccbBuf
				);
				if (p == nullptr) {
					Error_Report(L"Error",L"PayForm can't get job!");
					ExitThread(0);
				}
				pJob = (JOB_INFO_2*)p;
				dmcopies = pJob->pDevMode->dmCopies;
				TotalPages = pJob->TotalPages;
			}

			InitializeComponent();
			if (p) {
				this->L_DOCNAME->Text = gcnew String(pJob->pDocument);
				this->L_TOTALPAGES->Text = gcnew String(int2LPTSTR_10(TotalPages));
				LPTSTR dmduplex_str;
				switch (pJob->pDevMode->dmDuplex) {
				case DMDUP_SIMPLEX:
					dmduplex_str = L"單面列印";
					break;
				case DMDUP_HORIZONTAL:
					dmduplex_str = L"雙面列印短邊翻頁";
					break;
				case DMDUP_VERTICAL:
					dmduplex_str = L"雙面列印長邊翻頁";
					break;
				}
				this->L_DMDUPLEX->Text = gcnew String(dmduplex_str);
				this->L_PNTERNAME->Text = gcnew String(pJob->pPrinterName);
				this->L_DMCOPIES->Text = gcnew String(int2LPTSTR_10(dmcopies));
				this->L_JOBID->Text = gcnew String(int2LPTSTR_10(Jinfo->Jstat->_JobId));
				this->L_JOBSTAT->Text = gcnew String(int2LPTSTR_10(Jinfo->Jstat->_signal));
			
			}
			
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~PayForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  L_1;
	protected:
	private: System::Windows::Forms::Label^  L_JOBID;
	private: System::Windows::Forms::Label^  L_2;
	private: System::Windows::Forms::Label^  L_JOBSTAT;
	private: System::Windows::Forms::Label^  L_DMCOPIES;



	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PayForm::typeid));
			this->L_1 = (gcnew System::Windows::Forms::Label());
			this->L_JOBID = (gcnew System::Windows::Forms::Label());
			this->L_2 = (gcnew System::Windows::Forms::Label());
			this->L_JOBSTAT = (gcnew System::Windows::Forms::Label());
			this->L_DMCOPIES = (gcnew System::Windows::Forms::Label());
			this->Pay_Butt = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->L_DOCNAME = (gcnew System::Windows::Forms::Label());
			this->L_PNTERNAME = (gcnew System::Windows::Forms::Label());
			this->L_TOTALPAGES = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->RFID_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->cancel_Butt = (gcnew System::Windows::Forms::Button());
			this->L_DMDUPLEX = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->SuspendLayout();
			// 
			// L_1
			// 
			this->L_1->AutoSize = true;
			this->L_1->Location = System::Drawing::Point(83, 195);
			this->L_1->Name = L"L_1";
			this->L_1->Size = System::Drawing::Size(39, 12);
			this->L_1->TabIndex = 0;
			this->L_1->Text = L"Job ID:";
			// 
			// L_JOBID
			// 
			this->L_JOBID->AutoSize = true;
			this->L_JOBID->Location = System::Drawing::Point(128, 195);
			this->L_JOBID->Name = L"L_JOBID";
			this->L_JOBID->Size = System::Drawing::Size(75, 12);
			this->L_JOBID->TabIndex = 1;
			this->L_JOBID->Text = L"2000 Mädchen";
			// 
			// L_2
			// 
			this->L_2->AutoSize = true;
			this->L_2->Location = System::Drawing::Point(81, 219);
			this->L_2->Name = L"L_2";
			this->L_2->Size = System::Drawing::Size(54, 12);
			this->L_2->TabIndex = 2;
			this->L_2->Text = L"Job Status:";
			// 
			// L_JOBSTAT
			// 
			this->L_JOBSTAT->AutoSize = true;
			this->L_JOBSTAT->Location = System::Drawing::Point(141, 219);
			this->L_JOBSTAT->Name = L"L_JOBSTAT";
			this->L_JOBSTAT->Size = System::Drawing::Size(75, 12);
			this->L_JOBSTAT->TabIndex = 3;
			this->L_JOBSTAT->Text = L"8000 Mädchen";
			// 
			// L_DMCOPIES
			// 
			this->L_DMCOPIES->AutoSize = true;
			this->L_DMCOPIES->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->L_DMCOPIES->Location = System::Drawing::Point(178, 163);
			this->L_DMCOPIES->Name = L"L_DMCOPIES";
			this->L_DMCOPIES->Size = System::Drawing::Size(129, 19);
			this->L_DMCOPIES->TabIndex = 5;
			this->L_DMCOPIES->Text = L"4000 Mädchen";
			// 
			// Pay_Butt
			// 
			this->Pay_Butt->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Pay_Butt->Location = System::Drawing::Point(534, 272);
			this->Pay_Butt->Name = L"Pay_Butt";
			this->Pay_Butt->Size = System::Drawing::Size(70, 42);
			this->Pay_Butt->TabIndex = 6;
			this->Pay_Butt->Text = L"付費";
			this->Pay_Butt->UseVisualStyleBackColor = true;
			this->Pay_Butt->Click += gcnew System::EventHandler(this, &PayForm::Pay_Butt_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(61, 61);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(380, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(61, 61);
			this->pictureBox2->TabIndex = 8;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(12, 104);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(61, 61);
			this->pictureBox3->TabIndex = 9;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(380, 104);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(61, 61);
			this->pictureBox4->TabIndex = 10;
			this->pictureBox4->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(78, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(99, 19);
			this->label1->TabIndex = 11;
			this->label1->Text = L"文件名稱:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(447, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 19);
			this->label2->TabIndex = 12;
			this->label2->Text = L"印表機 :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(79, 135);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 19);
			this->label3->TabIndex = 13;
			this->label3->Text = L"列印面數:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(79, 163);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(99, 19);
			this->label4->TabIndex = 14;
			this->label4->Text = L"列印份數:";
			// 
			// L_DOCNAME
			// 
			this->L_DOCNAME->AutoSize = true;
			this->L_DOCNAME->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->L_DOCNAME->Location = System::Drawing::Point(78, 54);
			this->L_DOCNAME->Name = L"L_DOCNAME";
			this->L_DOCNAME->Size = System::Drawing::Size(229, 19);
			this->L_DOCNAME->TabIndex = 15;
			this->L_DOCNAME->Text = L"葛雷夫的第八十七道陰影";
			// 
			// L_PNTERNAME
			// 
			this->L_PNTERNAME->AutoSize = true;
			this->L_PNTERNAME->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->L_PNTERNAME->Location = System::Drawing::Point(446, 54);
			this->L_PNTERNAME->Name = L"L_PNTERNAME";
			this->L_PNTERNAME->Size = System::Drawing::Size(149, 19);
			this->L_PNTERNAME->TabIndex = 16;
			this->L_PNTERNAME->Text = L"佛朗明哥的問候";
			// 
			// L_TOTALPAGES
			// 
			this->L_TOTALPAGES->AutoSize = true;
			this->L_TOTALPAGES->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->L_TOTALPAGES->Location = System::Drawing::Point(178, 135);
			this->L_TOTALPAGES->Name = L"L_TOTALPAGES";
			this->L_TOTALPAGES->Size = System::Drawing::Size(69, 19);
			this->L_TOTALPAGES->TabIndex = 17;
			this->L_TOTALPAGES->Text = L"949487";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label5->Location = System::Drawing::Point(447, 126);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(119, 19);
			this->label5->TabIndex = 18;
			this->label5->Text = L"學生證認證:";
			// 
			// RFID_TextBox
			// 
			this->RFID_TextBox->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->RFID_TextBox->Location = System::Drawing::Point(380, 195);
			this->RFID_TextBox->Name = L"RFID_TextBox";
			this->RFID_TextBox->PasswordChar = '*';
			this->RFID_TextBox->Size = System::Drawing::Size(224, 30);
			this->RFID_TextBox->TabIndex = 19;
			// 
			// cancel_Butt
			// 
			this->cancel_Butt->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->cancel_Butt->Location = System::Drawing::Point(12, 272);
			this->cancel_Butt->Name = L"cancel_Butt";
			this->cancel_Butt->Size = System::Drawing::Size(70, 42);
			this->cancel_Butt->TabIndex = 20;
			this->cancel_Butt->Text = L"取消";
			this->cancel_Butt->UseVisualStyleBackColor = true;
			this->cancel_Butt->Click += gcnew System::EventHandler(this, &PayForm::cancel_Butt_Click);
			// 
			// L_DMDUPLEX
			// 
			this->L_DMDUPLEX->AutoSize = true;
			this->L_DMDUPLEX->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->L_DMDUPLEX->Location = System::Drawing::Point(79, 104);
			this->L_DMDUPLEX->Name = L"L_DMDUPLEX";
			this->L_DMDUPLEX->Size = System::Drawing::Size(189, 19);
			this->L_DMDUPLEX->TabIndex = 22;
			this->L_DMDUPLEX->Text = L"雙面列印從長邊翻頁";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"標楷體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label6->ForeColor = System::Drawing::Color::Red;
			this->label6->Location = System::Drawing::Point(12, 250);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(259, 19);
			this->label6->TabIndex = 23;
			this->label6->Text = L"黑白一張NT$1 彩色一面NT$2";
			// 
			// PayForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(616, 336);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->L_DMDUPLEX);
			this->Controls->Add(this->cancel_Butt);
			this->Controls->Add(this->RFID_TextBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->L_TOTALPAGES);
			this->Controls->Add(this->L_PNTERNAME);
			this->Controls->Add(this->L_DOCNAME);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->Pay_Butt);
			this->Controls->Add(this->L_DMCOPIES);
			this->Controls->Add(this->L_JOBSTAT);
			this->Controls->Add(this->L_2);
			this->Controls->Add(this->L_JOBID);
			this->Controls->Add(this->L_1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"PayForm";
			this->Text = L"印表機付費";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &PayForm::PayForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		bool Cancel_Job() {
			if (MessageBoxQ(
				static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE
				L"確定取消列印工作?",
				L"警告",
				MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
			) == IDYES) {
				if (!SetJob(
					payinfo->hPrinter,
					payinfo->Jstat->_JobId,
					0,
					NULL,//iflevel = 0, pJob should be NULL
					JOB_CONTROL_DELETE
				)) {
					Error_Report(L"Error", L"Fail to delete paying job!");
					ExitThread(0);
				}
				return true;
			}else{
				return false;
			}
		}
	private: System::Void PayForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (!Cancel_Job()) {
		e->Cancel = true;
	}
	}
private: System::Void Pay_Butt_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->RFID_TextBox->Text->Length > 10) {
		MessageBoxW(
			static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE,
			L"請確認學生證認證碼是否正確!",
			L"警告",
			MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
		);
		return;
	}
	if (payinfo->Jstat->_signal == JOB_UNEXDEL) {
		MessageBoxW(
			static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE,
			L"列印工作遭刪除!付費視窗即將關閉!",
			L"警告",
			MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
			);
		Jfree(payinfo->Jstat);
		ExitThread(0);
	}
	try {
		int Money = 0;
		int Black = 0;
		int Color = 0;

		Driver *driver;
		Connection *con;
		Statement *stmt;
		ResultSet *res;
		__const_Char_ptr sRFID = PtrToStringChars(this->RFID_TextBox->Text);
		LPTSTR RFID = (LPTSTR)malloc(sizeof(TCHAR)* (RFID_TextBox->Text->Length + 1));
		wsprintf(RFID, L"%ws\0", sRFID);



		char RFID_query_command[44];
		if (sprintf(RFID_query_command, "SELECT * FROM money WHERE RFID=\"%ws\"", RFID) == -1) {
			Error_Report(L"Error",L"sprintf_s fails to get query command!");
		}

		driver = get_driver_instance();
		con = driver->connect("tcp://140.116.25.50:3306", "Client", "WE3I6A");
		/* Connect to the MySQL test database */
		con->setSchema("print_management");

		stmt = con->createStatement();

		res = stmt->executeQuery(RFID_query_command);

		int res_count = 0;

		while (res->next()) {
			if (res_count < 1) {
				Money = res->getInt("Money");
				Black = res->getInt("Black");
				Color = res->getInt("Color");
				res_count++;
			}
			else {
				MessageBoxQ(
					static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE
					L"這個學生證有重複用戶!",
					L"錯誤",
					MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
				);
				return;
			}
		}
		if (res_count == 0) {
			MessageBoxQ(
				static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE
				L"這個學生證沒有註冊喔!",
				L"訊息",
				MB_OK | MB_ICONASTERISK | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
				);
			return;
		}

		char ltstr[50];
		char log_update_command[200];
		char money_update_command[200];
		DWORD cMoney = 0;

		if (wcscmp(pJob->pPrinterName, L"我是黑白") == 0) {
			cMoney = dmcopies * (TotalPages / 2 + TotalPages % 2);//一張一塊
		}
		if (wcscmp(pJob->pPrinterName, L"我是彩雷") == 0) {
			cMoney = dmcopies * TotalPages * 2;//一面兩塊
		}

		if (Money < cMoney) {
			wchar_t momeymsg[50];
			wsprintf(momeymsg, L"需要NT$%d，餘額只有NT$%d!\0", cMoney, Money);
			MessageBoxQ(
				static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE
				momeymsg,
				L"餘額不足",
				MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
				);
			return;
		}
		else {
			SYSTEMTIME lt = { 0 };
			GetLocalTime(&lt);
			

			if (sprintf(ltstr, "%d/%d/%d %d:%02d\0", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute) == -1) {
				Error_Report(L"Error", L"sprintf_s fails to get time!");
				return;
			}



			if (wcscmp(pJob->pPrinterName, L"我是黑白") == 0) {

				if (sprintf(money_update_command, "UPDATE money SET Money = %d, Black = %d WHERE RFID = \"%s\"\0", Money - cMoney, Black + dmcopies * (TotalPages / 2 + TotalPages % 2), wstr2cstr(RFID, 950)) == -1) {
					Error_Report(L"Error", L"sprintf_s fails to get update command!");
				}

				if (sprintf(log_update_command, "INSERT INTO black_log(RFID, Doc, Time, Copy, TotalPages) VALUES(\"%s\",  \"%s\", \"%s\", %u, %d)\0", wstr2cstr(RFID, 950), wstr2cstr(pJob->pDocument,950), ltstr, dmcopies, TotalPages) == -1) {
					Error_Report(L"Error", L"sprintf_s fails to get black_log upade command!");
				}
			}
			if (wcscmp(pJob->pPrinterName, L"我是彩雷") == 0) {

				if (sprintf(money_update_command, "UPDATE money SET Money = %d, Color = %d WHERE RFID = \"%s\"\0", Money - cMoney, Color + dmcopies * TotalPages, wstr2cstr(RFID, 950)) == -1) {
					Error_Report(L"Error", L"sprintf_s fails to get update command!");
				}

				if (sprintf(log_update_command, "INSERT INTO color_log(RFID, Doc, Time, Copy, TotalPages) VALUES(\"%s\",  \"%s\", \"%s\", %u, %d)\0", wstr2cstr(RFID, 950), wstr2cstr(pJob->pDocument, 950), ltstr, dmcopies, TotalPages) == -1) {
					Error_Report(L"Error", L"sprintf_s fails to get color_log upade command!");
				}
			}



			stmt->execute("SET NAMES big5");
			stmt->execute(log_update_command);

			this->payinfo->Jstat->_signal = JOB_PRINTING;

			if (payinfo->Jstat->_signal == JOB_UNEXDEL) {
				MessageBoxW(
					static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE,
					L"列印工作遭刪除!付費視窗即將關閉!",
					L"警告",
					MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
					);
				Jfree(payinfo->Jstat);
				ExitThread(0);
			}

			if (!SetJob(
				this->payinfo->hPrinter,
				this->payinfo->Jstat->_JobId,
				0,
				NULL,//iflevel = 0, pJob should be NULL
				JOB_CONTROL_RESUME
			)) {
				Error_Report(L"Error", L"Fail to resume paying job!");
				payinfo->Jstat->_signal = JOB_UNDEF;
				ExitThread(0);
			}
			else {
				payinfo->Jstat->_signal = JOB_PRINTING;
				stmt->execute(money_update_command);
				wchar_t succmsg[50];
				wsprintf(succmsg, L"餘額%d", Money -cMoney);
				MessageBoxQ(
					NULL,
					succmsg,
					L"付費完成",
					MB_OK | MB_ICONASTERISK | MB_DEFBUTTON1
				);
				
				ExitThread(0);
			}
			
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		wchar_t errormsg[100];
		wsprintf(errormsg, L"#ERR:%ws\nCode:%d\0",cstr2wstr(e.what(), CP_ACP), e.getErrorCode());
		MessageBoxQ(
			static_cast<HWND>(this->Handle.ToPointer()),//主視窗的HANDLE
			errormsg,
			L"SQL exception",
			MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL //MB_APPLMODAL確保使用者必須回應詢問
		);
	}
}
private: System::Void cancel_Butt_Click(System::Object^  sender, System::EventArgs^  e) {
	if (Cancel_Job()) {
		ExitThread(0);
	}
}
};
}
