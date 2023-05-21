#pragma once
#include "DBEditForm.h"
namespace LabawithGUICLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ настройкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ базаДанныхToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ загрузитьБазуToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьБазуToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ToolStripMenuItem^ редактироватьБазуДанныхToolStripMenuItem;
	private: System::Windows::Forms::Button^ button3;




	private: System::ComponentModel::IContainer^ components;

	protected:



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->базаДанныхToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьБазуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьБазуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->редактироватьБазуДанныхToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem,
					this->настройкиToolStripMenuItem, this->базаДанныхToolStripMenuItem, this->редактироватьБазуДанныхToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1478, 33);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem
			// 
			this->спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem->Name = L"спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem";
			this->спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem->Size = System::Drawing::Size(368, 29);
			this->спаситеПамагитеЯНихренаНеПонимаюToolStripMenuItem->Text = L"Спасите памагите, я нихрена не понимаю";
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(116, 29);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// базаДанныхToolStripMenuItem
			// 
			this->базаДанныхToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->загрузитьБазуToolStripMenuItem,
					this->сохранитьБазуToolStripMenuItem
			});
			this->базаДанныхToolStripMenuItem->Name = L"базаДанныхToolStripMenuItem";
			this->базаДанныхToolStripMenuItem->Size = System::Drawing::Size(129, 29);
			this->базаДанныхToolStripMenuItem->Text = L"База данных";
			// 
			// загрузитьБазуToolStripMenuItem
			// 
			this->загрузитьБазуToolStripMenuItem->Name = L"загрузитьБазуToolStripMenuItem";
			this->загрузитьБазуToolStripMenuItem->Size = System::Drawing::Size(241, 34);
			this->загрузитьБазуToolStripMenuItem->Text = L"Загрузить базу";
			// 
			// сохранитьБазуToolStripMenuItem
			// 
			this->сохранитьБазуToolStripMenuItem->Name = L"сохранитьБазуToolStripMenuItem";
			this->сохранитьБазуToolStripMenuItem->Size = System::Drawing::Size(241, 34);
			this->сохранитьБазуToolStripMenuItem->Text = L"Сохранить базу";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->listBox2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->listBox1);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Location = System::Drawing::Point(12, 36);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(360, 779);
			this->panel1->TabIndex = 1;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->panel2->Location = System::Drawing::Point(378, 36);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1088, 779);
			this->panel2->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(7, 333);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(350, 55);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Добавить в список запросов";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 20;
			this->listBox1->Location = System::Drawing::Point(7, 103);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(350, 224);
			this->listBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(148, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Редактор запроса";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(164, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Возможные запросы";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 395);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(137, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Список запросов";
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 20;
			this->listBox2->Location = System::Drawing::Point(11, 418);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(346, 304);
			this->listBox2->TabIndex = 5;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(11, 728);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(140, 48);
			this->button2->TabIndex = 6;
			this->button2->Text = L"удалть запрос";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(157, 728);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(200, 48);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Очистить список запросов";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// редактироватьБазуДанныхToolStripMenuItem
			// 
			this->редактироватьБазуДанныхToolStripMenuItem->Name = L"редактироватьБазуДанныхToolStripMenuItem";
			this->редактироватьБазуДанныхToolStripMenuItem->Size = System::Drawing::Size(255, 29);
			this->редактироватьБазуДанныхToolStripMenuItem->Text = L"Редактировать базу данных";
			this->редактироватьБазуДанныхToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::редактироватьБазуДанныхToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1478, 844);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximumSize = System::Drawing::Size(1500, 900);
			this->MinimumSize = System::Drawing::Size(1500, 900);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void редактироватьБазуДанныхToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	DBEditForm^ f2 = gcnew DBEditForm();
	f2->Show();
}
};
};
