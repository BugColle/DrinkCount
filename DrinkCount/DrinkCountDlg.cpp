
// DrinkCountDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "DrinkCount.h"
#include "DrinkCountDlg.h"
#include "afxdialogex.h"

#include "dlgSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CString mPrButton1, mPrButton2, mPrButton3;
	CString mPrDataPath;
	BOOL mPrWinPos;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	mPrWinPos = 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	dlgSetting dlg;
	dlg.mstrButton1 = mPrButton1;
	dlg.mstrButton2 = mPrButton2;
	dlg.mstrButton3 = mPrButton3;
	dlg.mstrDataPath = mPrDataPath;
	dlg.mbWinPos = mPrWinPos;
	dlg.DoModal();
	{
		mPrButton1 = dlg.mstrButton1;
		mPrButton2 = dlg.mstrButton2;
		mPrButton3 = dlg.mstrButton3;
		mPrDataPath = dlg.mstrDataPath;
		mPrWinPos = dlg.mbWinPos;
	}
}


// CDrinkCountDlg ダイアログ



CDrinkCountDlg::CDrinkCountDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRINKCOUNT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mFont.CreatePointFont(200, _T("MS ゴシック"));	//フォントサイズ変更
}

void CDrinkCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, mStatic1);
	DDX_Control(pDX, IDC_STATIC2, mStatic2);
	DDX_Control(pDX, IDC_STATIC3, mStatic3);
}

BEGIN_MESSAGE_MAP(CDrinkCountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrinkCountDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDrinkCountDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDrinkCountDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CDrinkCountDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDrinkCountDlg メッセージ ハンドラー

BOOL CDrinkCountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	// 実行パスを取得
	CString strCurrentPath;
	strCurrentPath.GetBufferSetLength(MAX_PATH);
	GetCurrentDirectory(MAX_PATH, (LPWSTR)(LPCWSTR)strCurrentPath);
	strCurrentPath.ReleaseBuffer();

	// 同じ階層の「DATA」フォルダを探して設定ファイルを見つける
	CString strConfPath = strCurrentPath + _T("\\Data");
	if (!PathFileExists(strConfPath))
	{
		CreateDirectory(strConfPath, NULL);
	}
	mConfIni    = strConfPath + _T("\\Conf.ini");
	mSettingIni = strConfPath + _T("\\Settingf.ini");
	mLogIni     = strConfPath + _T("\\Log.ini");
	mScreenIni = strConfPath + _T("\\Screen.ini");

	//Dataパスが変わってるかどうか
	CString strDataPath;
	if (GetFindIni(mConfIni))
	{
		strDataPath = GetStringIni(mConfIni, _T("DATA"), _T("PATH"));
	}
	if (!strDataPath.IsEmpty())
	{
		if (!PathFileExists(strDataPath))
		{
			BOOL bNameValid = CreateDirectory(strDataPath, NULL);
			ASSERT(bNameValid);
		}
		mSettingIni = strDataPath + _T("\\Seting.ini");
		mLogIni     = strDataPath + _T("\\Log.ini");
		mScreenIni  = strDataPath + _T("\\Screen.ini");
	}

	//ボタン名設定
	CString strBtn1, strBtn2, strBtn3;
	if (GetFindIni(mSettingIni))
	{
		mstrButton1 = GetStringIni(_T("BUTTON"), _T("1"), mSettingIni);
		mstrButton2 = GetStringIni(_T("BUTTON"), _T("2"), mSettingIni);
		mstrButton3 = GetStringIni(_T("BUTTON"), _T("3"), mSettingIni);
		mWinPointSave = GetPrivateProfileInt(_T("POSITION"), _T("SAVE"), 0, mSettingIni);		//Windows位置覚える

	}
	if (mstrButton1.IsEmpty()) { strBtn1 = SetLoadString(IDS_DEFAULT_BUTTON_1); } else { strBtn1 = mstrButton1; }
	if (mstrButton2.IsEmpty()) { strBtn2 = SetLoadString(IDS_DEFAULT_BUTTON_2); } else { strBtn2 = mstrButton2; }
	if (mstrButton3.IsEmpty()) { strBtn3 = SetLoadString(IDS_DEFAULT_BUTTON_3); } else { strBtn3 = mstrButton3; }
	GetDlgItem(IDC_BUTTON1)->SetWindowTextW(strBtn1);
	GetDlgItem(IDC_BUTTON2)->SetWindowTextW(strBtn2);
	GetDlgItem(IDC_BUTTON3)->SetWindowTextW(strBtn3);

	//OKボタン
	GetDlgItem(IDOK)->SetWindowTextW(SetLoadString(IDS_DEFAULT_OK));

	// カウンターの文字を大きく
	GetDlgItem(IDC_STATIC1)->SetFont(&mFont);
	GetDlgItem(IDC_STATIC2)->SetFont(&mFont);
	GetDlgItem(IDC_STATIC3)->SetFont(&mFont);

	//カウンター記録
	CTime cTime = CTime::GetCurrentTime();
	mNowKey = cTime.Format("%Y%m%d");
	if (GetFindIni(mLogIni))
	{
		// ファイルが存在する場合
		mInt1 = GetPrivateProfileInt(mNowKey, _T("COUNT1"), 0, mLogIni);
		mInt2 = GetPrivateProfileInt(mNowKey, _T("COUNT2"), 0, mLogIni);
		mInt3 = GetPrivateProfileInt(mNowKey, _T("COUNT3"), 0, mLogIni);
	}
	mStatic1.SetWindowText(SetInt2Str(mInt1));
	mStatic2.SetWindowText(SetInt2Str(mInt2));
	mStatic3.SetWindowText(SetInt2Str(mInt3));

	// タイトル
	CString strTitle = SetLoadString(IDS_DEFAULT_TITLE);
	strTitle += cTime.Format(" [ %Y-%m-%d ]");
	SetWindowText(strTitle);

	// Window位置情報取得
	if (GetFindIni(mScreenIni))
	{
		if (mWinPointSave)
		{
			int nLeft = GetPrivateProfileInt(_T("POSITION"), _T("X"), -1, mScreenIni);
			int nTop = GetPrivateProfileInt(_T("POSITION"), _T("Y"), -1, mScreenIni);
			SetWindowPos(NULL, nLeft, nTop, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		else
		{
			BOOL bNameValid = DeleteFile(mScreenIni);
			ASSERT(bNameValid);
		}
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CDrinkCountDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		{
			//必要データー送る
			dlgAbout.mPrButton1 = mstrButton1;
			dlgAbout.mPrButton2 = mstrButton2;
			dlgAbout.mPrButton3 = mstrButton3;
			dlgAbout.mPrDataPath = mstrConfPath;
			dlgAbout.mPrWinPos = mWinPointSave;
		}
		dlgAbout.DoModal();
		{
			//データーパスが変わってる場合
			if (mstrConfPath != dlgAbout.mPrDataPath)
			{
				CString strTemp = dlgAbout.mPrDataPath;
				if (!PathFileExists(strTemp))
				{
					BOOL bNameValid = CreateDirectory(strTemp, NULL);
					ASSERT(bNameValid);
				}
				WritePrivateProfileString(_T("DATA"), _T("PATH"), strTemp, mConfIni);
				WritePrivateProfileString(NULL, NULL, NULL, mConfIni);
				mSettingIni = strTemp + _T("\\Seting.ini");
				mLogIni     = strTemp + _T("\\Log.ini");
				mScreenIni  = strTemp + _T("\\Screen.ini");
			}
			//ボタン名変更
			if (mstrButton1 != dlgAbout.mPrButton1)
			{
				CString strTemp1 = dlgAbout.mPrButton1;
				WritePrivateProfileString(_T("BUTTON"), _T("1"), strTemp1, mSettingIni);
				WritePrivateProfileString(NULL, NULL, NULL, mSettingIni);
				mstrButton1 = strTemp1;
				if (strTemp1.IsEmpty()) { strTemp1 = SetLoadString(IDS_DEFAULT_BUTTON_1); }
				GetDlgItem(IDC_BUTTON1)->SetWindowTextW(strTemp1);
			}
			if (mstrButton2 != dlgAbout.mPrButton2)
			{
				CString strTemp2 = dlgAbout.mPrButton2;
				WritePrivateProfileString(_T("BUTTON"), _T("2"), strTemp2, mSettingIni);
				WritePrivateProfileString(NULL, NULL, NULL, mSettingIni);
				mstrButton2 = strTemp2;
				if (strTemp2.IsEmpty()) { strTemp2 = SetLoadString(IDS_DEFAULT_BUTTON_2); }
				GetDlgItem(IDC_BUTTON2)->SetWindowTextW(strTemp2);
			}
			if (mstrButton3 != dlgAbout.mPrButton3)
			{
				CString strTemp3 = dlgAbout.mPrButton3;
				WritePrivateProfileString(_T("BUTTON"), _T("3"), strTemp3, mSettingIni);
				WritePrivateProfileString(NULL, NULL, NULL, mSettingIni);
				mstrButton3 = strTemp3;
				if (strTemp3.IsEmpty()) { strTemp3 = SetLoadString(IDS_DEFAULT_BUTTON_3); }
				GetDlgItem(IDC_BUTTON3)->SetWindowTextW(strTemp3);
			}
			//位置覚えるかどうか
			if (mWinPointSave != dlgAbout.mPrWinPos)
			{
				mWinPointSave = dlgAbout.mPrWinPos;
				if (mWinPointSave)
				{
					WritePrivateProfileString(_T("POSITION"), _T("SAVE"), _T("1"), mSettingIni);
				}
				else {
					WritePrivateProfileString(_T("POSITION"), _T("SAVE"), _T("0"), mSettingIni);
				}
				WritePrivateProfileString(NULL, NULL, NULL, mSettingIni);
			}
		}
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CDrinkCountDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CDrinkCountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDrinkCountDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	++mInt1;
	mStatic1.SetWindowText(SetInt2Str(mInt1));
}

void CDrinkCountDlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	++mInt2;
	mStatic2.SetWindowText(SetInt2Str(mInt2));
}

void CDrinkCountDlg::OnBnClickedButton3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	++mInt3;
	mStatic3.SetWindowText(SetInt2Str(mInt3));
}

void CDrinkCountDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// カウントを記録
	WritePrivateProfileString(mNowKey, _T("COUNT1"), SetInt2Str(mInt1), mLogIni);
	WritePrivateProfileString(mNowKey, _T("COUNT2"), SetInt2Str(mInt2), mLogIni);
	WritePrivateProfileString(mNowKey, _T("COUNT3"), SetInt2Str(mInt3), mLogIni);
	WritePrivateProfileString(NULL, NULL, NULL, mLogIni);

	// ウィンドウ位置記録
	if (mWinPointSave)
	{
		RECT rc;
		GetWindowRect(&rc);
		WritePrivateProfileString(_T("POSITION"), _T("X"), SetInt2Str(rc.left), mScreenIni);
		WritePrivateProfileString(_T("POSITION"), _T("Y"), SetInt2Str(rc.top), mScreenIni);
		WritePrivateProfileString(NULL, NULL, NULL, mScreenIni);
	}

	CDialogEx::OnOK();
}

// Iniファイル存在確認
BOOL CDrinkCountDlg::GetFindIni(CString strIniFile)
{
	CFileFind find;
	return find.FindFile(strIniFile);
}

// Iniファイル文字列取得
CString CDrinkCountDlg::GetStringIni(LPCWSTR lpwAppName, LPCWSTR lpwKeyName, CString strIniFile)
{
	CString strTemp;
	DWORD	dwSize = MAX_PATH;
	TCHAR	szString[MAX_PATH] = { 0 };
	GetPrivateProfileString(lpwAppName, lpwKeyName, _T(""), szString, dwSize, strIniFile);
	strTemp = szString;
	return strTemp;
}

// 数字を文字に
CString CDrinkCountDlg::SetInt2Str(int nInt)
{
	CString strTemp;
	strTemp.Format(_T("%d"), nInt);
	return strTemp;
}

// 文字列取得
CString CDrinkCountDlg::SetLoadString(UINT nUint)
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(nUint);
	ASSERT(bNameValid);
	return strTemp;
}
