// AStar.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AStar.h"
#include "AStarDlg.h"
#include "AstarPathfinder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAStarApp

BEGIN_MESSAGE_MAP(CAStarApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

//#include"MapWnd.h"
// CAStarApp 构造

CAStarApp::CAStarApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAStarApp 对象

CAStarApp theApp;


// CAStarApp 初始化

BOOL CAStarApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CAStarDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	/*CMapWnd mapWnd;
	CWnd* ptemp=NULL;
	ptemp=(CWnd*)(GetDlgItem(ptemp->m_hWnd,IDC_AMAP));
	//ptemp->FromHandle
	mapWnd.InitMap(ptemp);
	::SetFocus(ptemp->m_hWnd);*/
	return FALSE;
}
