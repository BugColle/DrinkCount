#pragma once
#include "afxdialogex.h"


// dlgSetting ダイアログ

class dlgSetting : public CDialogEx
{
	DECLARE_DYNAMIC(dlgSetting)

public:
	dlgSetting(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~dlgSetting();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CEdit mEdit1;
	CEdit mEdit2;
	CEdit mEdit3;
	CEdit mEdit4;
	CButton mCheck1;
	CString mstrButton1, mstrButton2, mstrButton3;
	CString mstrDataPath;
	BOOL mbWinPos;
	virtual BOOL OnInitDialog();
};
