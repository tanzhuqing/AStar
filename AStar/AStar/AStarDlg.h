// AStarDlg.h : ͷ�ļ�
//

#pragma once
#include "atltypes.h"


// CAStarDlg �Ի���
class CAStarDlg : public CDialog
{
// ����
public:
	CAStarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ASTAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int fState[8][8];
    bool m_isReady;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedHelp1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	int m_iCountRed;
	CPoint m_Spoint;
	CPoint m_Dpoint;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedButton2();
};
