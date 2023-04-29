// MouseHook.h : MouseHook.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMouseHookApp
// このクラスの実装に関しては MouseHook.cpp を参照してください。
//

class CMouseHookApp : public CWinApp
{
public:
	CMouseHookApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
