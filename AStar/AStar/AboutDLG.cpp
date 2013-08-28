// AboutDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "AStar.h"
#include "AboutDLG.h"


// CAboutDLG 对话框

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


// CAboutDLG 消息处理程序
