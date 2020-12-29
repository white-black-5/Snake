
// Test 2Dlg.cpp: 实现文件
//


#include "pch.h"
#include "framework.h"
#include "Test 2.h"
#include "Test 2Dlg.h"
#include "afxdialogex.h"
#include "snake.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define length 20 //定义每个小方格的长度
#define horizontal 30 //定义水平方向方格总数
#define vertical 30 //定义垂直方向方格总数


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest2Dlg 对话框



CTest2Dlg::CTest2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCORE, Myscore);
}

BEGIN_MESSAGE_MAP(CTest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CTest2Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CTest2Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CTest2Dlg::OnBnClickedButtonExit)
	ON_EN_CHANGE(IDC_SCORE, &CTest2Dlg::OnEnChangeScore)
END_MESSAGE_MAP()


// CTest2Dlg 消息处理程序

BOOL CTest2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//修改界面大小
	//m_score = 0;
	//CRect window;
	//CRect client;
	//GetWindowRect(window);
	//GetClientRect(client);
//	int width = window.Width() - client.Width() + length * horizontal;
	//int height = window.Height() - client.Height() + length * vertical;
	//MoveWindow(0, 0, width, height);
	GameStart();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
		CClientDC dc(this);
		dc.Rectangle(0, 0, length * horizontal, length * vertical);
		DrawSnake();
		DrawBean();
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CTest2Dlg::random()
{
	// TODO: 在此处添加实现代码.
	srand(time(NULL));//程序每次运行产生不同的随机数序列
	long x = rand() % 20;//随机生成坐标x
	long y = rand() % 20;//随机生成坐标y	
	return x;
	return y;
}


void CTest2Dlg::SetBean()
{
	// TODO: 在此处添加实现代码.
	s_bean.x = random();//随机生成坐标x
	s_bean.y = random();//随机生成坐标y	
	while (s_snake.onself(s_bean))
	{
		s_bean.x = random();
		s_bean.y = random();
	}
}


void CTest2Dlg::DrawBean()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush red(RGB(255, 0, 0));//红色标识食物
	dc.SelectObject(red);
	dc.Rectangle(s_bean.x * length, s_bean.y * length, (s_bean.x + 1) * length, (s_bean.y + 1) * length);//画出食物
}


void CTest2Dlg::GameStart()
{
	// TODO: 在此处添加实现代码.
	SetBean();
	//SetTimer(1, 500, NULL);//设置定时器使蛇每500毫秒运动一次
}


void CTest2Dlg::DrawSnake()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush green(RGB(0, 255, 0));//用绿色标识蛇身
	dc.SelectObject(green);
	CList<CPoint>* pSnake =s_snake.Getlength();//获取蛇身的位置
	//遍历并画出蛇
	POSITION p = pSnake->GetHeadPosition();
	while (p)
	{
		CPoint point = pSnake->GetNext(p);
		dc.Rectangle(point.x * length, point.y * length, (point.x + 1) * length, (point.y + 1) * length);//画出蛇

	}
}   


void CTest2Dlg::SnakeMove()
{
	CClientDC dc(this);
	CPoint tail = s_snake.Getlength()->GetTail();//获取移动前的蛇尾
	if (s_snake.Move(s_bean))//如果移动成功
	{
		CPoint head = s_snake.Getlength()->GetHead();
		CBrush green(RGB(0, 255, 0));
		CBrush* old = dc.SelectObject(&green);
		dc.Rectangle(head.x * length, head.y * length, (head.x + 1) * length, (head.y + 1) * length);
		dc.SelectObject(old);
		if (head == s_bean)//如果吃掉食物则产生新的食物
		{
			SetBean();
			DrawBean();
			my_score= my_score +1;
			//SetTimer(1, 500, NULL);
			CString s;
			s.Format(_T("%d"), my_score);//显示得分
			Myscore.SetWindowText(s);
		}
		else
		{   //删掉原来的蛇尾
			CPen white(PS_SOLID, 1, RGB(255, 255, 255));
			dc.SelectObject(&white);
			dc.Rectangle(tail.x * length, tail.y * length, (tail.x + 1) * length, (tail.y + 1) * length);

		}
	}
	else
	{
		KillTimer(1);
	//	ShowScores();
		MessageBox(_T("Game over!"));
		exit(0);		
	}
}

void CTest2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SnakeMove();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CTest2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			s_snake.Direction(CPoint(0, -1));
			break;
		case VK_DOWN:
			s_snake.Direction(CPoint(0, 1));
			break;
		case VK_LEFT:
			s_snake.Direction(CPoint(-1, 0));
			break;
		case VK_RIGHT:
			s_snake.Direction(CPoint(1, 0));
			break;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTest2Dlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("Game start！"));
	SetTimer(1, 300, NULL);//定时
	
}


void CTest2Dlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	AfxMessageBox(_T("Game pause!"));
}


void CTest2Dlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("Exit!"));
	exit(0);
}






void CTest2Dlg::ShowScores()
{
	//CString s;
	//s.Format(_T("%d"), my_score);//显示得分
	//Myscore.SetWindowText(s);
	//MessageBox(s);
}


void CTest2Dlg::OnEnChangeScore()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}
