
// SAutomationDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"


// CSAutomationDlg �_�C�A���O
class CSAutomationDlg : public CDialogEx
{
	// �R���X�g���N�V����
public:
	CSAutomationDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_SAUTOMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

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
	// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
