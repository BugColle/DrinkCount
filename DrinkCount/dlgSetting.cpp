// dlgSetting.cpp : 実装ファイル
//

#include "pch.h"
#include "DrinkCount.h"
#include "afxdialogex.h"
#include "dlgSetting.h"


// dlgSetting ダイアログ

IMPLEMENT_DYNAMIC(dlgSetting, CDialogEx)

dlgSetting::dlgSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{
	mbWinPos = 0;
}

dlgSetting::~dlgSetting()
{
}

void dlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit1);
	DDX_Control(pDX, IDC_EDIT2, mEdit2);
	DDX_Control(pDX, IDC_EDIT3, mEdit3);
	DDX_Control(pDX, IDC_EDIT4, mEdit4);
	DDX_Control(pDX, IDC_CHECK1, mCheck1);
}


BEGIN_MESSAGE_MAP(dlgSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &dlgSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &dlgSetting::OnBnClickedButton1)
END_MESSAGE_MAP()


// dlgSetting メッセージ ハンドラー

BOOL dlgSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	mEdit1.SetWindowTextW(mstrButton1);
	mEdit2.SetWindowTextW(mstrButton2);
	mEdit3.SetWindowTextW(mstrButton3);
	mEdit4.SetWindowTextW(mstrDataPath);
	if (mbWinPos) { mCheck1.SetCheck(1); }

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void dlgSetting::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_EDIT4)->SetWindowTextW(dlg.GetPathName());
	}
}

void dlgSetting::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	mEdit1.GetWindowText(mstrButton1);
	mEdit2.GetWindowText(mstrButton2);
	mEdit3.GetWindowText(mstrButton3);
	mEdit4.GetWindowText(mstrDataPath);
	mbWinPos = mCheck1.GetCheck();
	CDialogEx::OnOK();
}


