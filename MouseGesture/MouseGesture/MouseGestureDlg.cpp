
// MouseGestureDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MouseGesture.h"
#include "MouseGestureDlg.h"
#include "afxdialogex.h"

#include "MouseHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define TIMER_WAKE_UP (102)
// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMouseGestureDlg ダイアログ




CMouseGestureDlg::CMouseGestureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMouseGestureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseGestureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseGestureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMouseGestureDlg::OnBnClickedOk)
	ON_WM_RBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGING()
    ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


HHOOK g_hhook;


BOOL CMouseGestureDlg::TrayNotifyIconMessage(DWORD dwMessage)
{
    CString sTip = _T("MouseGesture.exe");
    NOTIFYICONDATA nid;

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd   = GetSafeHwnd();
	nid.uID    = IDR_MAINFRAME;
    nid.uFlags = NIF_MESSAGE | NIF_ICON;
    nid.uCallbackMessage = WM_TRAYNOTIFY;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.hIcon  = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
    _tcscpy_s(nid.szTip, _countof(nid.szTip), (LPCTSTR)sTip);
    
    return Shell_NotifyIcon(dwMessage, &nid);

}
BOOL CMouseGestureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	
	SetTimer(TIMER_WAKE_UP, 100, NULL);
	TrayNotifyIconMessage(NIM_ADD);


	// TODO: 初期化をここに追加します。
	DWORD dwThreadID;

	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}      

LRESULT CMouseGestureDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    switch (lParam)
    {
	case WM_LBUTTONUP: 
		{
            ShowWindow(SW_NORMAL);
            SetForegroundWindow();
            SetFocus();
        break;
		}
    default:
		{
        break;
		}
    } 

    return 0;
}


void CMouseGestureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMouseGestureDlg::OnPaint()
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
HCURSOR CMouseGestureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseGestureDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CDialogEx::OnOK();
}


BOOL CMouseGestureDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE){return TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMouseGestureDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnRButtonDown(nFlags, point);
}


BOOL CMouseGestureDlg::DestroyWindow()
{
	UnhookWindowsHookEx(g_hhook);
    TrayNotifyIconMessage(NIM_DELETE);

	return CDialogEx::DestroyWindow();
}

void CMouseGestureDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_WAKE_UP)
	{

			ShowWindow( SW_MINIMIZE );

			if(IsIconic()==TRUE)
			{
				KillTimer(TIMER_WAKE_UP);
			}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMouseGestureDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
    if (nType == SIZE_MINIMIZED)
    {
        ShowWindow(SW_HIDE);
    }
}
