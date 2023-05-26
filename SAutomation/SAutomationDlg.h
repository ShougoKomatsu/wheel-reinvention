
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

#define HOTKEY_ENABLE (20)

#define HOTKEY_ID_ESCAPE (100)

struct OperationInfo
{
	BOOL bLoop;
	
	CString sHotkey;
	BOOL bUseCtrl;
	BOOL bUseShift;
	DWORD dwHotKey;
	BOOL m_bRunning;
	CString sFileName;
};

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
	BOOL ChangeIcon(int iIcon);

	void Operate0();
	void Operate1();
	void Operate2();
	void Operate3();
	void Operate4();
	void Operate5();

	void ResetHotkey(int iID);

	void ToggleEnable();

	OperationInfo m_OpeInfo[MAX_THREAD];

	BOOL m_bEnableHotkey;
	CString m_sHotkeyEnable;

	
	DWORD m_dwHotKeyEnable;

	CString m_sDir;
	void FileSelect(CString *sFileName);
	void SaveSettings();
	void ReadSettings();
	BOOL m_bRunningAny;
	BOOL MouseMoveAndDisp(DWORD dwMoveDirection, int iDistance);
	// 実装
protected:
	HICON m_hIconStandby;
	HICON m_hIconRunning;

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
	virtual BOOL DestroyWindow();

	CString m_sEditFileName[MAX_THREAD];
	CString m_sEditStatus[MAX_THREAD];
	CComboBox m_combo[MAX_THREAD];
	CComboBox m_comboUseCtrl[MAX_THREAD];
	CComboBox m_comboUseShift[MAX_THREAD];
	CComboBox m_comboEnable;


	
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnDispStandby(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnSelchangeCombo5();

	afx_msg void OnSelchangeComboCtrl0();
	afx_msg void OnSelchangeComboCtrl1();
	afx_msg void OnSelchangeComboCtrl2();
	afx_msg void OnSelchangeComboCtrl3();
	afx_msg void OnSelchangeComboCtrl4();
	afx_msg void OnSelchangeComboCtrl5();

	afx_msg void OnSelchangeComboShift0();
	afx_msg void OnSelchangeComboShift1();
	afx_msg void OnSelchangeComboShift2();
	afx_msg void OnSelchangeComboShift3();
	afx_msg void OnSelchangeComboShift4();
	afx_msg void OnSelchangeComboShift5();

	afx_msg void OnSelchangeComboEnable();

	afx_msg void OnBnClickedButtonOperate0();
	afx_msg void OnBnClickedButtonOperate1();
	afx_msg void OnBnClickedButtonOperate2();
	afx_msg void OnBnClickedButtonOperate3();
	afx_msg void OnBnClickedButtonOperate4();
	afx_msg void OnBnClickedButtonOperate5();
	afx_msg void OnBnClickedCheckEnableHotkey();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonOpenFolder();
};
