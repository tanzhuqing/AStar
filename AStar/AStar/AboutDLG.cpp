// AboutDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AStar.h"
#include "AboutDLG.h"


// CAboutDLG �Ի���

IMPLEMENT_DYNAMIC(CAboutDLG, CDialog)
CAboutDLG::CAboutDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDLG::IDD, pParent)
{
}

CAboutDLG::~CAboutDLG()
{
}

void CAboutDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDLG, CDialog)
END_MESSAGE_MAP()


// CAboutDLG ��Ϣ�������
