
// SAutomationDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


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

	void Operate1();
	void Operate2();
	void Operate3();
	DWORD m_dwHotKey1;
	DWORD m_dwHotKey2;
	DWORD m_dwHotKey3;
	CString m_sDir;
	void FileSelect(CString *sFileName);
	void SaveSettings();
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton2();
	UINT m_uiEditLoop;
	afx_msg void OnBnClickedButton3();
	virtual BOOL DestroyWindow();
	CString m_sEditFileName1;
	CString m_sEditFileName2;
	CString m_sEditFileName3;
};
