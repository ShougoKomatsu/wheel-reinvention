
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "thread.h"

#define HOTKEY_ID_0 (10)
#define HOTKEY_ID_1 (11)
#define HOTKEY_ID_2 (12)
#define HOTKEY_ID_3 (13)
#define HOTKEY_ID_4 (14)
#define HOTKEY_ID_5 (15)

#define HOTKEY_ID_ESCAPE (100)

// CSAutomationDlg ダイアログ
class CSAutomationDlg : public CDialogEx
{
	// コンストラクション
public:
	CSAutomationDlg(CWnd* pParent = NULL);	// 標準コンストラクター

	// ダイアログ データ
	enum { IDD = IDD_SAUTOMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL TrayNotifyIconMessage(DWORD dwMessage);
	void Operate0();
	void Operate1();
	void Operate2();
	void Operate3();
	void Operate4();
	void Operate5();
	BOOL m_bLoop[MAX_THREAD];
	
	CString m_sHotkey[MAX_THREAD];

	DWORD m_dwHotKey[MAX_THREAD];

	CString m_sDir;
	void FileSelect(CString *sFileName);
	void SaveSettings();
	void ReadSettings();
	BOOL MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance);
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
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	UINT m_uiEditLoop;
	virtual BOOL DestroyWindow();

	CString m_sEditFileName[MAX_THREAD];
	CString m_sEditStatus[MAX_THREAD];
	CComboBox m_combo[MAX_THREAD];


	


	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnSelchangeCombo5();

	afx_msg void OnBnClickedButtonOperate0();
	afx_msg void OnBnClickedButtonOperate1();
	afx_msg void OnBnClickedButtonOperate2();
	afx_msg void OnBnClickedButtonOperate3();
	afx_msg void OnBnClickedButtonOperate4();
	afx_msg void OnBnClickedButtonOperate5();
	afx_msg void OnBnClickedCheckEnableHotkey();
};
