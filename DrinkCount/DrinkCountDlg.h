
// DrinkCountDlg.h : ヘッダー ファイル
//

#pragma once

#include "resource.h"		// メイン シンボル

// CDrinkCountDlg ダイアログ
class CDrinkCountDlg : public CDialogEx
{
// コンストラクション
public:
	CDrinkCountDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRINKCOUNT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	CStatic mStatic1;
	CStatic mStatic2;
	CStatic mStatic3;
	int mInt1 = 0;
	int mInt2 = 0;
	int mInt3 = 0;
	CFont mFont;
	CString mConfIni;	// 設定ファイル
	CString mLogIni;	// 回数記録用
	CString mSettingIni;	// ボタン名記録用
	CString mScreenIni;	// 画面位置の記録用
	CString mNowKey;	// Log.ini読み込みに利用
	BOOL GetFindIni(CString strIniFile);
	CString GetStringIni(LPCWSTR lpwAppName, LPCWSTR lpwKeyName, CString strIniFile);
	CString SetInt2Str(int nInt);
	CString SetLoadString(UINT nUint);

	CString mstrButton1, mstrButton2, mstrButton3;
	CString mstrConfPath;
	BOOL mWinPointSave = 0;
};
