// AStar.cpp : ����Ӧ�ó��������Ϊ��
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
// CAStarApp ����

CAStarApp::CAStarApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAStarApp ����

CAStarApp theApp;


// CAStarApp ��ʼ��

BOOL CAStarApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
