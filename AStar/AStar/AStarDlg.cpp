// AStarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AStar.h"
#include "AStarDlg.h"
#include ".\astardlg.h"
#include "MapWnd.h"
#include "AstarPathFinder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAStarDlg 对话框



CAStarDlg::CAStarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAStarDlg::IDD, pParent)
	, m_iCountRed(0)
	, m_Spoint(0)
	, m_Dpoint(0)
	, m_isReady(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			fState[i][j]=0;
		}
	}
	
}

void CAStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAStarDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BEGIN, OnBnClickedBegin)
	ON_BN_CLICKED(IDC_HELP1, OnBnClickedHelp1)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESET, OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CAStarDlg 消息处理程序

BOOL CAStarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CAStarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAStarDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CWnd* pMap;
		pMap=GetDlgItem(IDC_AMAP);
		pMap->MoveWindow(32,32,256,256);
		CRect maprect;
		pMap->GetClientRect(&maprect);
		CClientDC dc(pMap);
		CBrush brush(RGB(255,255,255));
		CBrush* pOldBrush=dc.SelectObject(&brush);
		dc.Rectangle(&maprect);
		dc.SelectObject(pOldBrush);

		int dx=maprect.Width()/8;
		int dy=maprect.Height()/8;
		for(int i=1;i<=8;i++)
		{
		dc.MoveTo(0,dy*i);
		dc.LineTo(maprect.Width(),dy*i);
		dc.MoveTo(dx*i,0);
		dc.LineTo(dx*i,maprect.Height());
		}
		CPen pen(PS_SOLID,1,RGB(255,255,255));
		CPen* pOldPen=dc.SelectObject(&pen);

		dc.SelectObject(&brush);
		for(int x=0;x<8;x++)
		{
			for(int y=0;y<8;y++)
			{
				if(fState[x][y]==1)
				{
					CBrush brush(RGB(0,0,255));
					CBrush* pOldBrush=dc.SelectObject(&brush);
					dc.Rectangle(x*32+2,y*32+2,(x+1)*32-2,(y+1)*32-2);	
				    dc.SelectObject(pOldBrush);					
				}
				else if(fState[x][y]==2)
				{
					CBrush brush(RGB(255,0,0));
					CBrush* pOldBrush=dc.SelectObject(&brush);
					dc.Rectangle(x*32+5,y*32+5,(x+1)*32-5,(y+1)*32-5);	
				    dc.SelectObject(pOldBrush);					
				}
				else if(fState[x][y]==3)
				{
					CBrush brush(RGB(255,0,0));
					CBrush* pOldBrush=dc.SelectObject(&brush);
					dc.Rectangle(x*32+10,y*32+10,(x+1)*32-10,(y+1)*32-10);	
				    dc.SelectObject(pOldBrush);					
				}
			}
		}     
	    dc.SelectObject(pOldPen);
		pMap->UpdateWindow();
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAStarDlg::OnBnClickedBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_isReady)
		return;
	BYTE temp[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
   BYTE map[8];
   int x=0;
   int y=0;
   ::ZeroMemory(map,8);
   for(y=0;y<8;y++)
   for(x=0;x<8;x++)
   {
	   if(fState[x][y]==1)
	   map[(y*8+x)/8]^=temp[(y*8+x)%8];
   }
   AstarPathfinder findpath;
   findpath.InitAstarTileMap(map,8,8);
   if(findpath.NewPath(m_Spoint.x/32-1,m_Spoint.y/32-1,m_Dpoint.x/32-1,m_Dpoint.y/32-1))
   {
   CString str;

   do{
		findpath.PathNextNode();
		x=findpath.NodeGetX();
		y=findpath.NodeGetY();
		fState[x][y]=3;
			//str.Format("x= %d,y= %d",x,y);
	       //AfxMessageBox(str);
     }while(findpath.ReachedGoal());
   }
   fState[x][y]=2;   
   Invalidate();
}

void CAStarDlg::OnBnClickedHelp1()
{
	::MessageBox(this->m_hWnd,"Press left mouse to set/cancel road-block,press right mouse to set/cancel begin or end node,then press <begin> to find the nearest path!","Help",MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}

void CAStarDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(WM_QUIT); 
}

void CAStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CPen* pOldPen=dc.SelectObject(&pen);
	if((point.x<32)||(point.y<32))
	return;
	int x=(point.x-32)/32;
	int y=(point.y-32)/32;
	CString str;
	//str.Format("x= %d,y= %d",x,y);
	//AfxMessageBox(str);
    if(x<8&&y<8)
	{
		if(fState[x][y]==0)
		{
			fState[x][y]=1;
			CBrush brush(RGB(0,0,255));
			CBrush* pOldBrush=dc.SelectObject(&brush);
		    dc.Rectangle(x*32+32+2,y*32+32+2,(x+1)*32+32-2,(y+1)*32+32-2);
			dc.SelectObject(pOldBrush);
		}
		else if(fState[x][y]==1)
		{
			fState[x][y]=0;
		    dc.Rectangle(x*32+32+2,y*32+32+2,(x+1)*32+32-2,(y+1)*32+32-2);
		}

	}
    dc.SelectObject(pOldPen);
	CDialog::OnLButtonDown(nFlags, point);
}


void CAStarDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CPen* pOldPen=dc.SelectObject(&pen);
	if((point.x<32)||(point.y<32))
	return;
	int x=(point.x-32)/32;
	int y=(point.y-32)/32;
	CString str;
	//str.Format("x= %d,y= %d",x,y);
	//AfxMessageBox(str);
    if(x<8&&y<8)
	{
		if(fState[x][y]==0)
		{
			if(m_iCountRed==0)
			{
			m_isReady=false;
			m_iCountRed++;
			fState[x][y]=2;
			CBrush brush(RGB(255,0,0));
			CBrush* pOldBrush=dc.SelectObject(&brush);
		    dc.Rectangle(x*32+32+5,y*32+32+5,(x+1)*32+32-5,(y+1)*32+32-5);
			dc.SelectObject(pOldBrush);
			m_Spoint.x=point.x;
			m_Spoint.y=point.y;
			}
			else if(m_iCountRed==1)
			{
			m_isReady=true;
			m_iCountRed++;
			fState[x][y]=2;
			CBrush brush(RGB(255,0,0));
			CBrush* pOldBrush=dc.SelectObject(&brush);
		    dc.Rectangle(x*32+32+5,y*32+32+5,(x+1)*32+32-5,(y+1)*32+32-5);
			dc.SelectObject(pOldBrush);
			m_Dpoint.x=point.x;
			m_Dpoint.y=point.y;
			}
		}
		else if(fState[x][y]==2)
		{
			m_isReady=false;
			m_iCountRed--;
			fState[x][y]=0;
		    dc.Rectangle(x*32+32+2,y*32+32+2,(x+1)*32+32-2,(y+1)*32+32-2);
		}

	}
    dc.SelectObject(pOldPen);
	CDialog::OnRButtonDown(nFlags, point);
}
void CAStarDlg::OnBnClickedReset()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			fState[i][j]=0;
		}
	}
	m_iCountRed=0;
			m_isReady=false;
	Invalidate();
}


void CAStarDlg::OnBnClickedButton2()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
