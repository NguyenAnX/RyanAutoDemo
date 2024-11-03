#pragma once

#include <unordered_map>
#include <windows.system.threading.h>
#include "GameWnd.h"
#include "Npc.h"
#include <iostream>
#include "RLogger.h"
#include "GameWndManager.h"


namespace RyanJxUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace std;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	protected:

	private: System::Windows::Forms::CheckBox^ chboxNotifyDeath;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::ComponentModel::IContainer^ components;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ListView^ lvPlayers;
	private: System::Windows::Forms::ColumnHeader^ pName;
	private: System::Windows::Forms::ColumnHeader^ pHP;
	private: System::Windows::Forms::ColumnHeader^ pMP;
	private: System::Windows::Forms::ColumnHeader^ pFightState;
	private: System::Windows::Forms::ColumnHeader^ pId;
	private: System::Windows::Forms::ColumnHeader^ pThreadId;
	private: System::Windows::Forms::ColumnHeader^ hwnd;
	private: System::Windows::Forms::Button^ button2;






	private: System::Threading::Timer^ myTimer;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(5) {
				L"",
					L"Z", L"A", L"B", L"C"
			}, -1));
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->chboxNotifyDeath = (gcnew System::Windows::Forms::CheckBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lvPlayers = (gcnew System::Windows::Forms::ListView());
			this->pName = (gcnew System::Windows::Forms::ColumnHeader());
			this->pHP = (gcnew System::Windows::Forms::ColumnHeader());
			this->pMP = (gcnew System::Windows::Forms::ColumnHeader());
			this->pFightState = (gcnew System::Windows::Forms::ColumnHeader());
			this->pId = (gcnew System::Windows::Forms::ColumnHeader());
			this->pThreadId = (gcnew System::Windows::Forms::ColumnHeader());
			this->hwnd = (gcnew System::Windows::Forms::ColumnHeader());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// chboxNotifyDeath
			// 
			this->chboxNotifyDeath->AutoSize = true;
			this->chboxNotifyDeath->Location = System::Drawing::Point(12, 174);
			this->chboxNotifyDeath->Name = L"chboxNotifyDeath";
			this->chboxNotifyDeath->Size = System::Drawing::Size(85, 17);
			this->chboxNotifyDeath->TabIndex = 2;
			this->chboxNotifyDeath->Text = L"Notify Death";
			this->chboxNotifyDeath->UseVisualStyleBackColor = true;
			this->chboxNotifyDeath->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chboxNotifyDeath_CheckedChanged);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 60000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MainForm::timer2_Tick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(103, 170);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(126, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Send Message 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::buttonTrySomething_Click);
			// 
			// lvPlayers
			// 
			this->lvPlayers->CheckBoxes = true;
			this->lvPlayers->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(7) {
				this->pName, this->pHP,
					this->pMP, this->pFightState, this->pId, this->pThreadId, this->hwnd
			});
			this->lvPlayers->FullRowSelect = true;
			this->lvPlayers->HideSelection = false;
			listViewItem1->StateImageIndex = 0;
			this->lvPlayers->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) { listViewItem1 });
			this->lvPlayers->Location = System::Drawing::Point(12, 12);
			this->lvPlayers->MultiSelect = false;
			this->lvPlayers->Name = L"lvPlayers";
			this->lvPlayers->Size = System::Drawing::Size(544, 146);
			this->lvPlayers->TabIndex = 6;
			this->lvPlayers->UseCompatibleStateImageBehavior = false;
			this->lvPlayers->View = System::Windows::Forms::View::Details;
			this->lvPlayers->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &MainForm::lvPlayers_ItemChecked);
			this->lvPlayers->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &MainForm::lvPlayers_ItemSelectionChanged);
			// 
			// pName
			// 
			this->pName->Text = L"Name";
			this->pName->Width = 89;
			// 
			// pHP
			// 
			this->pHP->Text = L"HP";
			this->pHP->Width = 68;
			// 
			// pMP
			// 
			this->pMP->Text = L"MP";
			this->pMP->Width = 67;
			// 
			// pFightState
			// 
			this->pFightState->Text = L"FightState";
			this->pFightState->Width = 70;
			// 
			// pId
			// 
			this->pId->Text = L"ProcessID";
			this->pId->Width = 75;
			// 
			// pThreadId
			// 
			this->pThreadId->Text = L"ThreadID";
			this->pThreadId->Width = 81;
			// 
			// hwnd
			// 
			this->hwnd->Text = L"hwnd";
			this->hwnd->Width = 89;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(235, 170);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(113, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Send Message 2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(568, 218);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->lvPlayers);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chboxNotifyDeath);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"RyanJx";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		GameWndManager* wndManager;
		RLogger* logger;
		

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void applyConfigState(ConfigState* cfgState);
	private: GameWnd* selectedWnd();
	private: System::Void chboxNotifyDeath_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void RyanJxUI::MainForm::OnTimerTick(Object^ state);
	private: System::Void RyanJxUI::MainForm::updatePlayerListView();
	private: System::Void buttonTrySomething_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void lvPlayers_ItemChecked(System::Object^ sender, System::Windows::Forms::ItemCheckedEventArgs^ e);
	private: System::Void lvPlayers_ItemSelectionChanged(System::Object^ sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^ e);
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
};
}
