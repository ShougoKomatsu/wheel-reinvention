
// MouseGestureDlg.h : ヘッダー ファイル
//

#pragma once


// CMouseGestureDlg ダイアログ
class CMouseGestureDlg : public CDialogEx
{
// コンストラクション
public:
	CMouseGestureDlg(CWnd* pParent = NULL);	// 標準コンストラクター
	
	virtual BOOL DestroyWindow();
// ダイアログ データ
	enum { IDD = IDD_MOUSEGESTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL TrayNotifyIconMessage(DWORD dwMessage);

	
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
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
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
