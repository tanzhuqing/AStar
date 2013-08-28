// MapWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AStar.h"
#include "MapWnd.h"
#include ".\mapwnd.h"


// CMapWnd �Ի���

IMPLEMENT_DYNAMIC(CMapWnd, CDialog)
CMapWnd::CMapWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMapWnd::IDD, pParent)
{

}

CMapWnd::~CMapWnd()
{
}

void CMapWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapWnd, CDialog)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
END_MESSAGE_MAP()


// CMapWnd ��Ϣ�������

void CMapWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    int x=point.x;
	int y=point.y;
	MessageBox("x,y");
	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CMapWnd::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnNcRButtonDown(nHitTest, point);
}

bool CMapWnd::InitMap(CWnd* pmap)
{		   
	CClientDC dc(pmap);
	CRect maprect;
	pmap->GetClientRect(&maprect);
	int dx=maprect.Width()/8;
	int dy=maprect.Height()/8;
	for(int i=1;i<=8;i++)
	{
		dc.MoveTo(0,dy*i);
		dc.LineTo(maprect.Width(),dy*i);
		dc.MoveTo(dx*i,0);
		dc.LineTo(dx*i,maprect.Height());
	}
	return false;
}
