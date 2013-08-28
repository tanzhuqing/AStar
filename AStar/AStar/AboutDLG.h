#pragma once


// CAboutDLG 对话框

class CAboutDLG : public CDialog
{
	DECLARE_DYNAMIC(CAboutDLG)

public:
	CAboutDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAboutDLG();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
