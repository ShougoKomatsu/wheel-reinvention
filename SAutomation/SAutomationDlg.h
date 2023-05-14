
// SAutomationDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"
#include "thread.h"


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
	void Operate4();
	void Operate5();
	void Operate6();
	DWORD m_dwHotKey[MAX_THREAD];

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();

	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sEditMousePosC;
	CString m_sEditMousePosR;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	UINT m_uiEditLoop;
	virtual BOOL DestroyWindow();
	CString m_sEditFileName[MAX_THREAD];

	afx_msg LRESULT OnOperate(WPARAM wParam, LPARAM lParam);
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	CComboBox m_combo4;
	CComboBox m_combo5;
	CComboBox m_combo6;
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnSelchangeCombo6();
};
