#pragma once


// CAboutDLG �Ի���

class CAboutDLG : public CDialog
{
	DECLARE_DYNAMIC(CAboutDLG)

public:
	CAboutDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutDLG();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
