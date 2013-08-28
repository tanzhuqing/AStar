#pragma once


// CMapWnd 对话框

class CMapWnd : public CDialog
{
	DECLARE_DYNAMIC(CMapWnd)

public:
	CMapWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMapWnd();

// 对话框数据
	enum { IDD = IDD_ASTAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	bool InitMap(CWnd* pmap);
};
