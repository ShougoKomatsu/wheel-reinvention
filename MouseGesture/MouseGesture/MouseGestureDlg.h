
// MouseGestureDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CMouseGestureDlg �_�C�A���O
class CMouseGestureDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CMouseGestureDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[
	
	virtual BOOL DestroyWindow();
// �_�C�A���O �f�[�^
	enum { IDD = IDD_MOUSEGESTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g
	BOOL TrayNotifyIconMessage(DWORD dwMessage);

	
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
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
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
