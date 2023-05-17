
// SAutomationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "SAutomationDlg.h"
#include "afxdialogex.h"
#include "Thread.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "Automation.h"
#define TIMER_DISP_MOUSPOS (100)
#define TIMER_THREAD_WATCH (101)

HWND g_hWnd;

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


// CSAutomationDlg ダイアログ  




CSAutomationDlg::CSAutomationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSAutomationDlg::IDD, pParent)
	, m_sEditMousePosC(_T(""))
	, m_sEditMousePosR(_T(""))
	, m_uiEditLoop(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSAutomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_C, m_sEditMousePosC);
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_R, m_sEditMousePosR);
	DDX_Text(pDX, IDC_EDIT2, m_uiEditLoop);
	DDX_Text(pDX, IDC_EDIT_FILE_0, (m_sEditFileName[0]));
	DDX_Text(pDX, IDC_EDIT_FILE_1, (m_sEditFileName[1]));
	DDX_Text(pDX, IDC_EDIT_FILE_2, (m_sEditFileName[2]));
	DDX_Text(pDX, IDC_EDIT_FILE_3, (m_sEditFileName[3]));
	DDX_Text(pDX, IDC_EDIT_FILE_4, (m_sEditFileName[4]));
	DDX_Text(pDX, IDC_EDIT_FILE_5, (m_sEditFileName[5]));

	DDX_Text(pDX, IDC_EDIT_STATUS_0, (m_sEditStatus[0]));
	DDX_Text(pDX, IDC_EDIT_STATUS_1, (m_sEditStatus[1]));
	DDX_Text(pDX, IDC_EDIT_STATUS_2, (m_sEditStatus[2]));
	DDX_Text(pDX, IDC_EDIT_STATUS_3, (m_sEditStatus[3]));
	DDX_Text(pDX, IDC_EDIT_STATUS_4, (m_sEditStatus[4]));
	DDX_Text(pDX, IDC_EDIT_STATUS_5, (m_sEditStatus[5]));

	DDX_Control(pDX, IDC_COMBO0, (m_combo[0]));
	DDX_Control(pDX, IDC_COMBO1, (m_combo[1]));
	DDX_Control(pDX, IDC_COMBO2, (m_combo[2]));
	DDX_Control(pDX, IDC_COMBO3, (m_combo[3]));
	DDX_Control(pDX, IDC_COMBO4, (m_combo[4]));
	DDX_Control(pDX, IDC_COMBO5, (m_combo[5]));
}

BEGIN_MESSAGE_MAP(CSAutomationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON0, &CSAutomationDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON1, &CSAutomationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSAutomationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSAutomationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSAutomationDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSAutomationDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &CSAutomationDlg::OnEnChangeEdit1)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO0, &CSAutomationDlg::OnSelchangeCombo0)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSAutomationDlg::OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSAutomationDlg::OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSAutomationDlg::OnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CSAutomationDlg::OnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CSAutomationDlg::OnSelchangeCombo5)
	ON_MESSAGE(WM_DISP_STANDBY, &CSAutomationDlg::OnDispStandby)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_0, &CSAutomationDlg::OnBnClickedButtonOperate0)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_1, &CSAutomationDlg::OnBnClickedButtonOperate1)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_2, &CSAutomationDlg::OnBnClickedButtonOperate2)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_3, &CSAutomationDlg::OnBnClickedButtonOperate3)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_4, &CSAutomationDlg::OnBnClickedButtonOperate4)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_5, &CSAutomationDlg::OnBnClickedButtonOperate5)
END_MESSAGE_MAP()


// CSAutomationDlg メッセージ ハンドラー
HHOOK g_hhook=NULL;
int g_iR=0;
int g_iC=0;

HANDLE g_hHotkey[MAX_THREAD];

LRESULT CALLBACK MouseHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WM_MOUSEMOVE:
		{
			g_iR = ((LPMSLLHOOKSTRUCT)lParam)->pt.y;
			g_iC = ((LPMSLLHOOKSTRUCT)lParam)->pt.x;
			break;
		}
	default: break;
	}
	return CallNextHookEx(g_hhook, code, wParam, lParam);
}


void SetComboItem(CComboBox* combo, CString m_sHotkey, int iDefault)
{
	combo->ResetContent();
	combo->AddString(_T("a"));
	combo->AddString(_T("b"));
	combo->AddString(_T("c"));
	combo->AddString(_T("d"));
	combo->AddString(_T("e"));
	combo->AddString(_T("f"));
	combo->AddString(_T("g"));
	combo->AddString(_T("h"));
	combo->AddString(_T("i"));
	combo->AddString(_T("j"));
	combo->AddString(_T("k"));
	combo->AddString(_T("l"));
	combo->AddString(_T("m"));
	combo->AddString(_T("n"));
	combo->AddString(_T("o"));
	combo->AddString(_T("p"));
	combo->AddString(_T("q"));
	combo->AddString(_T("r"));
	combo->AddString(_T("s"));
	combo->AddString(_T("t"));
	combo->AddString(_T("u"));
	combo->AddString(_T("v"));
	combo->AddString(_T("w"));
	combo->AddString(_T("x"));
	combo->AddString(_T("y"));
	combo->AddString(_T("z"));


	BOOL bFound;
	bFound = FALSE;
	for(int i=0; i<combo->GetCount(); i++)
	{
		TCHAR tch[8];
		combo->GetLBText(i, tch);
		if(m_sHotkey.Compare(tch)==0){combo->SetCurSel(i); bFound = TRUE;break;}
	}
	if(bFound != TRUE){combo->SetCurSel(iDefault);}
}

LRESULT CSAutomationDlg::OnDispStandby(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	if(wParam<0){return 0;}
	if(wParam>=MAX_THREAD){return 0;}
	g_hThread[wParam]=0;
	m_sEditStatus[wParam].Format(_T("Stand by"));
	UpdateData(FALSE);
	return 0;
}

void CSAutomationDlg::ReadSettings()
{
	
	TCHAR szData[MAX_PATH];
	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 
	GetPrivateProfileString(_T("FileName"),_T("1"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[0].Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("2"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[1].Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("3"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[2].Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("4"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[3].Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("5"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[4].Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("6"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName[5].Format(_T("%s"),szData);

	GetPrivateProfileString(_T("Mouse"),_T("ClickDulation"),_T("50"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_iClickDulation = _ttoi(szData);


	GetPrivateProfileString(_T("Hotkey"),_T("1"),_T("b"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[0].Format(_T("%s"), szData);
	GetPrivateProfileString(_T("Hotkey"),_T("2"),_T("c"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[1].Format(_T("%s"), szData);
	GetPrivateProfileString(_T("Hotkey"),_T("3"),_T("d"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[2].Format(_T("%s"), szData);
	GetPrivateProfileString(_T("Hotkey"),_T("4"),_T("e"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[3].Format(_T("%s"), szData);
	GetPrivateProfileString(_T("Hotkey"),_T("5"),_T("f"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[4].Format(_T("%s"), szData);
	GetPrivateProfileString(_T("Hotkey"),_T("6"),_T("g"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkey[5].Format(_T("%s"), szData);
}

BOOL CSAutomationDlg::OnInitDialog()
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

	g_hWnd = this->m_hWnd;

	POINT p;
	GetCursorPos(&p);
	g_iR=p.y;
	g_iC=p.x;
	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);


	SetTimer(TIMER_DISP_MOUSPOS,200, NULL);
	SetTimer(TIMER_THREAD_WATCH,200, NULL);

	m_uiEditLoop=1;
	TCHAR szData[MAX_PATH];
	GetCurrentDirectory(sizeof(szData)/sizeof(TCHAR),szData);
	m_sDir.Format(_T("%s"),szData);

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	CFileFind cf;
	if(cf.FindFile(sMacroFolderPath) != TRUE){_tmkdir(sMacroFolderPath);}

	ReadSettings();

	for(int iID= 0 ; iID<MAX_THREAD; iID++)
	{
		SetComboItem(&m_combo[iID],m_sHotkey[iID], iID+2);
		g_hThread[iID] = NULL;
		m_dwHotKey[iID] = char(m_sHotkey[iID].GetAt(0))-'a'+0x41;
		m_sEditStatus[iID].Format(_T("Stand by"));
	}

	g_bHalt = FALSE;


	RegisterHotKey(NULL, HOTKEY_ID_0, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[0]);
	RegisterHotKey(NULL, HOTKEY_ID_1, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[1]);
	RegisterHotKey(NULL, HOTKEY_ID_2, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[2]);
	RegisterHotKey(NULL, HOTKEY_ID_3, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[3]);
	RegisterHotKey(NULL, HOTKEY_ID_4, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[4]);
	RegisterHotKey(NULL, HOTKEY_ID_5, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[5]);


	UpdateData(FALSE);


	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSAutomationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSAutomationDlg::OnPaint()
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
HCURSOR CSAutomationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSAutomationDlg::OnEnChangeEdit1()
{
}

BOOL CSAutomationDlg::MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance)
{
	long lMouseX;
	long lMouseY;
	lMouseX = g_iC;
	lMouseY = g_iR;
	if(dwMoveDirection == VK_LEFT){lMouseX -= iDistance;}
	if(dwMoveDirection == VK_RIGHT){lMouseX += iDistance;}
	if(dwMoveDirection == VK_UP){lMouseY -= iDistance;}
	if(dwMoveDirection == VK_DOWN){lMouseY += iDistance;}

	if(lMouseX<0){lMouseX=0;}
	if(lMouseY<0){lMouseY=0;}
	if(lMouseX>=::GetSystemMetrics(SM_CXSCREEN)){lMouseX = ::GetSystemMetrics(SM_CXSCREEN)-1;}
	if(lMouseY>=::GetSystemMetrics(SM_CXSCREEN)){lMouseY = ::GetSystemMetrics(SM_CYSCREEN)-1;}

	DWORD dwX, dwY;
	dwX = (lMouseX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (lMouseY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);

	return TRUE;
}

BOOL WaitUntilCtrlShiftReleased()
{
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetAsyncKeyState (VK_LSHIFT);
		shCtrl = GetAsyncKeyState (VK_CONTROL);
		if((shShift>=0)&&(shCtrl>=0)) 
		{
			return TRUE;
		}

		Sleep(1);
	}
	return FALSE;
}

BOOL CSAutomationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN){return TRUE;}
		if(pMsg->wParam == VK_ESCAPE){return TRUE;}
		if(pMsg->wParam == VK_SPACE){return TRUE;}
		if(pMsg->wParam == VK_LEFT){return MouseMoveAndDisp(VK_LEFT,10);}
		if(pMsg->wParam == VK_RIGHT){return MouseMoveAndDisp(VK_RIGHT,10);}
		if(pMsg->wParam == VK_UP){return MouseMoveAndDisp(VK_UP,10);}
		if(pMsg->wParam == VK_DOWN){return MouseMoveAndDisp(VK_DOWN,10);}
	}
	if(pMsg->message == WM_HOTKEY)
	{
		int iKey;
		iKey = (pMsg->lParam)>>16;
		if(iKey == m_dwHotKey[0]){Operate0();return TRUE;}
		if(iKey == m_dwHotKey[1]){Operate1();return TRUE;}
		if(iKey == m_dwHotKey[2]){Operate2();return TRUE;}
		if(iKey == m_dwHotKey[3]){Operate3();return TRUE;}
		if(iKey == m_dwHotKey[4]){Operate4();return TRUE;}
		if(iKey == m_dwHotKey[5]){Operate5();return TRUE;}
		if(iKey == VK_ESCAPE){g_bHalt = TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

int g_iWatching=0;
void CSAutomationDlg::OnTimer(UINT_PTR nIDEvent)
{

	if(nIDEvent == TIMER_DISP_MOUSPOS)
	{
		UpdateData(TRUE);
		m_sEditMousePosR.Format(_T("%d"),g_iR);
		m_sEditMousePosC.Format(_T("%d"),g_iC);
		UpdateData(FALSE);
	}
	if(nIDEvent == TIMER_THREAD_WATCH)
	{
		BOOL bAnyArrive = FALSE;
		for(int iID = 0; iID< MAX_THREAD; iID++)
		{
			if(g_hThread[iID] != NULL)
			{
				if(g_iWatching==0)
				{
					RegisterHotKey(NULL, HOTKEY_ID_ESCAPE, MOD_NOREPEAT, VK_ESCAPE);
					g_iWatching=1;
				}
				return;
			}
		}
		if(g_iWatching==1){
			UnregisterHotKey(NULL, HOTKEY_ID_ESCAPE); g_iWatching=0;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CSAutomationDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	CDialogEx::OnMouseMove(nFlags, point);
}


void CSAutomationDlg::Operate0()
{
	int iID = 0;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}

void CSAutomationDlg::Operate1()
{
	int iID = 1;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}


void CSAutomationDlg::Operate2()
{
	int iID = 2;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}



void CSAutomationDlg::Operate3()
{
	int iID = 3;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}




void CSAutomationDlg::Operate4()
{
	int iID = 4;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}




void CSAutomationDlg::Operate5()
{
	int iID = 5;
	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread[iID] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iID], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iID].Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName[iID]);
	int iParam;
	iParam=(m_uiEditLoop<<4)+iID;
	g_hThread[iID] = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

	m_sEditStatus[iID].Format(_T("Running"));
	UpdateData(FALSE);
}





void CSAutomationDlg::FileSelect(CString *sFileName)
{

	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	CFileDialog cf(TRUE);
	cf.m_ofn.lpstrInitialDir = sMacroFolderPath;
	if(cf.DoModal()!=IDOK){sFileName->Format(_T("")); return;}
	sFileName->Format(_T("%s"), cf.GetFileName());
}

void CSAutomationDlg::OnBnClickedButton0()
{
	FileSelect(&m_sEditFileName[0]);
	UpdateData(FALSE);
	SaveSettings();
}
void CSAutomationDlg::OnBnClickedButton1()
{
	FileSelect(&m_sEditFileName[1]);
	UpdateData(FALSE);
	SaveSettings();
}


void CSAutomationDlg::OnBnClickedButton2()
{
	FileSelect(&m_sEditFileName[2]);
	UpdateData(FALSE);
	SaveSettings();
}

void CSAutomationDlg::OnBnClickedButton3()
{
	FileSelect(&m_sEditFileName[3]);
	UpdateData(FALSE);
	SaveSettings();
}

void CSAutomationDlg::OnBnClickedButton4()
{
	FileSelect(&m_sEditFileName[4]);
	UpdateData(FALSE);
	SaveSettings();
}

void CSAutomationDlg::OnBnClickedButton5()
{
	FileSelect(&m_sEditFileName[5]);
	UpdateData(FALSE);
	SaveSettings();
}

void CSAutomationDlg::SaveSettings()
{
	UpdateData(TRUE);
	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	WritePrivateProfileString(_T("FileName"),_T("1"),m_sEditFileName[0],sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("2"),m_sEditFileName[1],sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("3"),m_sEditFileName[2],sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("4"),m_sEditFileName[3],sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("5"),m_sEditFileName[4],sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("6"),m_sEditFileName[5],sFilePath);

	CString sData;
	TCHAR tch[8];
	if(m_combo[0].GetCurSel()<0){sData.Format(_T("b"));}
	else{m_combo[0].GetLBText(m_combo[0].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("1"),sData,sFilePath);

	if(m_combo[1].GetCurSel()<0){sData.Format(_T("c"));}
	else{m_combo[1].GetLBText(m_combo[1].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("2"),sData,sFilePath);

	if(m_combo[2].GetCurSel()<0){sData.Format(_T("d"));}
	else{m_combo[2].GetLBText(m_combo[2].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("3"),sData,sFilePath);

	if(m_combo[3].GetCurSel()<0){sData.Format(_T("e"));}
	else{m_combo[3].GetLBText(m_combo[3].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("4"),sData,sFilePath);

	if(m_combo[4].GetCurSel()<0){sData.Format(_T("f"));}
	else{m_combo[4].GetLBText(m_combo[4].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("5"),sData,sFilePath);

	int i;
	i=m_combo[5].GetCurSel();
	if(m_combo[5].GetCurSel()<0){sData.Format(_T("g"));}
	else{m_combo[5].GetLBText(m_combo[5].GetCurSel(),tch); sData.Format(_T("%s"), tch);}
	WritePrivateProfileString(_T("Hotkey"),_T("6"),sData,sFilePath);

}

BOOL CSAutomationDlg::DestroyWindow()
{
	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	SaveSettings();
	return CDialogEx::DestroyWindow();
}




void CSAutomationDlg::OnSelchangeCombo0()
{
	UnregisterHotKey(NULL, HOTKEY_ID_0);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[0].GetCurSel()<0){return;}
	m_combo[0].GetLBText(m_combo[0].GetCurSel(),tch);

	m_dwHotKey[0] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_0, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[0]);
}


void CSAutomationDlg::OnSelchangeCombo1()
{
	UnregisterHotKey(NULL, HOTKEY_ID_1);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[1].GetCurSel()<0){return;}
	m_combo[1].GetLBText(m_combo[1].GetCurSel(),tch);

	m_dwHotKey[1] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_1, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[1]);
}


void CSAutomationDlg::OnSelchangeCombo2()
{
	UnregisterHotKey(NULL, HOTKEY_ID_2);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[2].GetCurSel()<0){return;}
	m_combo[2].GetLBText(m_combo[2].GetCurSel(),tch);

	m_dwHotKey[2] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_2, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[2]);
}


void CSAutomationDlg::OnSelchangeCombo3()
{
	UnregisterHotKey(NULL, HOTKEY_ID_3);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[3].GetCurSel()<0){return;}
	m_combo[3].GetLBText(m_combo[3].GetCurSel(),tch);

	m_dwHotKey[3] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_3, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[3]);
}


void CSAutomationDlg::OnSelchangeCombo4()
{
	UnregisterHotKey(NULL, HOTKEY_ID_4);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[4].GetCurSel()<0){return;}
	m_combo[4].GetLBText(m_combo[4].GetCurSel(),tch);

	m_dwHotKey[4] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_4, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[4]);
}


void CSAutomationDlg::OnSelchangeCombo5()
{
	UnregisterHotKey(NULL, HOTKEY_ID_5);

	UpdateData(TRUE);
	TCHAR tch[8];
	if(m_combo[5].GetCurSel()<0){return;}
	m_combo[5].GetLBText(m_combo[5].GetCurSel(),tch);

	m_dwHotKey[5] = char(tch[0])-'a'+0x41;
	RegisterHotKey(NULL, HOTKEY_ID_5, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, m_dwHotKey[5]);
}


void CSAutomationDlg::OnBnClickedButtonOperate0(){Operate0();}
void CSAutomationDlg::OnBnClickedButtonOperate1(){Operate1();}
void CSAutomationDlg::OnBnClickedButtonOperate2(){Operate2();}
void CSAutomationDlg::OnBnClickedButtonOperate3(){Operate3();}
void CSAutomationDlg::OnBnClickedButtonOperate4(){Operate4();}
void CSAutomationDlg::OnBnClickedButtonOperate5(){Operate5();}
