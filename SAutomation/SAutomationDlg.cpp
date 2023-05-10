
// SAutomationDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "SAutomationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "Automation.h"
#define TIMER_DISP_MOUSPOS (100)
HANDLE g_hThread1;
HANDLE g_hThread2;
HANDLE g_hThread3;

CString g_sFilePath1;
CString g_sFilePath2;
CString g_sFilePath3;
BOOL g_bHalt = FALSE;
BOOL g_bSuspend = FALSE;
LONGLONG g_llStepIn = 0;
LONGLONG g_llStepOut = 1;

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
	, m_sEditFileName1(_T(""))
	, m_sEditFileName2(_T(""))
	, m_sEditFileName3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSAutomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_C, m_sEditMousePosC);
	DDX_Text(pDX, IDC_EDIT_MOUSEPOS_R, m_sEditMousePosR);
	DDX_Text(pDX, IDC_EDIT2, m_uiEditLoop);
	DDX_Text(pDX, IDC_EDIT_FILE_1, m_sEditFileName1);
	DDX_Text(pDX, IDC_EDIT_FILE_2, m_sEditFileName2);
	DDX_Text(pDX, IDC_EDIT_FILE_3, m_sEditFileName3);
}

BEGIN_MESSAGE_MAP(CSAutomationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSAutomationDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CSAutomationDlg::OnEnChangeEdit1)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CSAutomationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSAutomationDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSAutomationDlg メッセージ ハンドラー
HHOOK g_hhook=NULL;
int g_iR=0;
int g_iC=0;
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

	g_hhook=SetWindowsHookEx(WH_MOUSE_LL,(HOOKPROC)MouseHookProc,NULL ,0);


	m_lMouseX=0;
	m_lMouseY=0;
	g_hThread1 = NULL;
	g_hThread2 = NULL;
	SetTimer(TIMER_DISP_MOUSPOS,100, NULL);
	RegisterHotKey(NULL, 1, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, (0x42));
	RegisterHotKey(NULL, 1, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, (0x43));
	RegisterHotKey(NULL, 1, MOD_SHIFT | MOD_CONTROL | MOD_NOREPEAT, (0x44));

	RegisterHotKey(NULL, 1, MOD_NOREPEAT, VK_ESCAPE);
	m_uiEditLoop=1;
	TCHAR szData[MAX_PATH];
	GetCurrentDirectory(sizeof(szData)/sizeof(TCHAR),szData);
	m_sDir.Format(_T("%s"),szData);

	CFileFind cf;
	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	if(cf.FindFile(sMacroFolderPath) != TRUE)
	{
		_tmkdir(sMacroFolderPath);
	}


	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 
	GetPrivateProfileString(_T("FileName"),_T("1"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName1.Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("2"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName2.Format(_T("%s"),szData);
	GetPrivateProfileString(_T("FileName"),_T("3"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sEditFileName3.Format(_T("%s"),szData);

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


BOOL ReadUTFFile(CString sFilePath, CString* sData)
{
	CFileFind cFind;
	if(cFind.FindFile(sFilePath)==FALSE){return FALSE;}

	FILE* f;
	CString sBuf;
	CString sDocBuf;

	_tfopen_s(&f, sFilePath,_T("r, ccs=UTF-8"));
	CStdioFile cstdioF(f);
	while(cstdioF.ReadString(sBuf)!= NULL){sDocBuf = sDocBuf + sBuf+_T("\x0d\x0a");}
	cstdioF.Close();
	fclose(f);

	sData->Format(_T("%s"), sDocBuf);
	return TRUE;
}


BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands)
{

	saCommands->RemoveAll();
	BOOL bRet;
	CString sFileDataRaw;
	bRet = ReadUTFFile(sFilePath, &sFileDataRaw);
	if(bRet != TRUE){return FALSE;}

	unsigned long ulFileDataLength;
	long lCR1;
	long lCR2;

	lCR1 = 0;
	ulFileDataLength = sFileDataRaw.GetLength();
	for(unsigned long ulPointer = 0; ulPointer<=ulFileDataLength; ulPointer++)
	{
		lCR2 = sFileDataRaw.Find(_T("\r"),lCR1);
		if(lCR2<=0)
		{
			lCR2 = sFileDataRaw.Find(_T("\n"),lCR1);
			if(lCR2<=0)
			{
				CString sBufTemp;
				sBufTemp.Trim(_T("\r"));
				sBufTemp.Trim(_T("\n"));
				sBufTemp.Format(_T("%s"), sFileDataRaw.Mid(lCR1, sFileDataRaw.GetLength()-lCR1));
				if(sBufTemp.GetLength()>0)
				{
					if(sBufTemp.GetLength()>0){saCommands->Add(sBufTemp);}
				}
				return TRUE;
			}
		}

		CString sLineData;
		sLineData.Format(_T("%s"), sFileDataRaw.Mid(lCR1, lCR2-lCR1));
		sLineData.Trim(_T("\r"));
		sLineData.Trim(_T("\n"));
		if(sLineData.GetLength()>0)
		{
			if(sLineData.GetLength()>0){saCommands->Add(sLineData);}
		}
		lCR1=lCR2+1;
	}

	//ここには来ない
	return FALSE;
}

void CSAutomationDlg::OnEnChangeEdit1()
{
}
BOOL WaitUntilCtrlShiftReleased()
{
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_LSHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		if((shShift>=0)&&(shCtrl>=0)) 
		{
			return TRUE;
		}

		Sleep(1);
	}
	return FALSE;
}
BOOL CSAutomationDlg::MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance)
{
	if(dwMoveDirection == VK_LEFT){m_lMouseX -= iDistance;}
	if(dwMoveDirection == VK_RIGHT){m_lMouseX += iDistance;}
	if(dwMoveDirection == VK_UP){m_lMouseY -= iDistance;}
	if(dwMoveDirection == VK_DOWN){m_lMouseY += iDistance;}

	if(m_lMouseX<0){m_lMouseX=0;}
	if(m_lMouseY<0){m_lMouseY=0;}
	if(m_lMouseX>=::GetSystemMetrics(SM_CXSCREEN)){m_lMouseX = ::GetSystemMetrics(SM_CXSCREEN)-1;}
	if(m_lMouseY>=::GetSystemMetrics(SM_CXSCREEN)){m_lMouseY = ::GetSystemMetrics(SM_CYSCREEN)-1;}

	DWORD dwX, dwY;
	dwX = m_lMouseX * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = m_lMouseY * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);

	return TRUE;
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
		if(iKey == 0x42){Operate1();return TRUE;}
		if(iKey == 0x43){Operate2();return TRUE;}
		if(iKey == 0x44){Operate3();return TRUE;}
		if(iKey == VK_ESCAPE){g_bHalt = TRUE;}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSAutomationDlg::OnTimer(UINT_PTR nIDEvent)
{

	if(nIDEvent == TIMER_DISP_MOUSPOS)
	{
		UpdateData(TRUE);
		m_sEditMousePosR.Format(_T("%d"),g_iR);
		m_sEditMousePosC.Format(_T("%d"),g_iC);
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSAutomationDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	CDialogEx::OnMouseMove(nFlags, point);
}

DWORD WINAPI GetKeyThread(LPVOID arg)
{
	short shSpace;
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shSpace = GetKeyState(VK_SPACE);
		if((shSpace<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			g_bSuspend = TRUE;  
		}
		else        	
		{
			g_bSuspend = FALSE;
		}
		Sleep(1);
	}

	return 0;
} 
DWORD WINAPI GetStepKeyThread(LPVOID arg)
{
	short shStep;
	short shCtrl;
	short shShift;
	while(1)
	{

		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shStep = GetKeyState(0x53);
		if((shStep<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			if(g_llStepOut==1){g_llStepIn=1;}
		}

		Sleep(1);
	}
	return 0;
} 

int g_iSceneData1;
int g_iSceneData2;
int g_iSceneData3;
DWORD WINAPI CommandThread(LPVOID arg)
{
	HANDLE hGetKey;
	HANDLE hGetStepKey;
	DWORD dwThreadID;
	int* iSceneData;
	hGetKey = CreateThread(NULL, 0, GetKeyThread, NULL, 0, &dwThreadID);
	hGetStepKey = CreateThread(NULL, 0, GetStepKeyThread, NULL, 0, &dwThreadID);
	CStringArray saCommands;
	if(((*(int*)arg)&0x03) ==1)
	{
		ReadTextFile(g_sFilePath1,&saCommands);
		g_iSceneData1=0;
		iSceneData=&g_iSceneData1;
	} 
	if(((*(int*)arg)&0x03) ==2)
	{
		ReadTextFile(g_sFilePath2,&saCommands);
		g_iSceneData2=2;
		iSceneData=&g_iSceneData2;
	}
	if(((*(int*)arg)&0x03) ==3)
	{
		ReadTextFile(g_sFilePath3,&saCommands);
		g_iSceneData3=3;
		iSceneData=&g_iSceneData3;
	}


	int iLoop;
	iLoop = (*(int*)arg)>>4;
	(*(int*)arg) = 0;  

	int iListLength;
	int iRet;
	for(int j=0; j<iLoop; j++)
	{
		iListLength =(int) saCommands.GetCount();
		for(int i=0; i<iListLength; i++)
		{
			if(g_bHalt == TRUE){g_bHalt = FALSE;return 0;}
			iRet = OperateCommand(iSceneData, &g_bHalt, &g_bSuspend, &g_llStepIn, saCommands.GetAt(i));
			if(iRet != 0){g_bHalt = FALSE; return 0;}
			g_llStepOut=1;
			g_llStepIn=0;
		}
	}
	TerminateThread(hGetKey, 0);
	TerminateThread(hGetStepKey, 0);
	return 0;
}

void CSAutomationDlg::Operate1()
{

	UpdateData(TRUE);
	DWORD dwThreadID;
	if(g_hThread1 != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread1,0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath1.Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName1);
	int iParam;
	iParam=(m_uiEditLoop<<4)+1;
	g_hThread1 = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}

}
void CSAutomationDlg::Operate2()
{
	UpdateData(TRUE);
	DWORD dwThreadID;

	if(g_hThread2 != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread2,0);
		if(dwResult != STATUS_WAIT_0){return;}
	}

	g_sFilePath2.Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName2);
	int iParam;
	iParam=(m_uiEditLoop<<4)+2;
	g_hThread2 = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}
}


void CSAutomationDlg::Operate3()
{
	UpdateData(TRUE);
	DWORD dwThreadID;

	if(g_hThread2 != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread3,0);
		if(dwResult != STATUS_WAIT_0){return;}
	}

	g_sFilePath3.Format(_T("%s\\Macro\\%s"),m_sDir, m_sEditFileName3);
	int iParam;
	iParam=(m_uiEditLoop<<4)+3;
	g_hThread2 = CreateThread(NULL, 0, CommandThread, (LPVOID)(&iParam), 0, &dwThreadID);
	while(iParam!=0){Sleep(10);}
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

void CSAutomationDlg::OnBnClickedButton1()
{
	FileSelect(&m_sEditFileName1);
	UpdateData(FALSE);

}
void CSAutomationDlg::OnBnClickedButton2()
{
	FileSelect(&m_sEditFileName2);
	UpdateData(FALSE);
}


void CSAutomationDlg::OnBnClickedButton3()
{
	FileSelect(&m_sEditFileName3);
	UpdateData(FALSE);
}

BOOL CSAutomationDlg::DestroyWindow()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if(g_hhook != NULL){UnhookWindowsHookEx(g_hhook);}
	UpdateData(TRUE);
	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	WritePrivateProfileString(_T("FileName"),_T("1"),m_sEditFileName1,sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("2"),m_sEditFileName2,sFilePath);
	WritePrivateProfileString(_T("FileName"),_T("3"),m_sEditFileName3,sFilePath);
	return CDialogEx::DestroyWindow();
}
