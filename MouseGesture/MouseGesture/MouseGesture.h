
// MouseGesture.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMouseGestureApp:
// このクラスの実装については、MouseGesture.cpp を参照してください。
//

class CMouseGestureApp : public CWinApp
{
public:
	CMouseGestureApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMouseGestureApp theApp;