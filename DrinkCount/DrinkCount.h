
// DrinkCount.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CDrinkCountApp:
// このクラスの実装については、DrinkCount.cpp を参照してください
//

class CDrinkCountApp : public CWinApp
{
public:
	CDrinkCountApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()

	CString mBtn1, mBtn2, mBtn3;
	CString mDataPath;
};

extern CDrinkCountApp theApp;
