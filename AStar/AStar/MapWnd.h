#pragma once


// CMapWnd �Ի���

class CMapWnd : public CDialog
{
	DECLARE_DYNAMIC(CMapWnd)

public:
	CMapWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMapWnd();

// �Ի�������
	enum { IDD = IDD_ASTAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	bool InitMap(CWnd* pmap);
};
