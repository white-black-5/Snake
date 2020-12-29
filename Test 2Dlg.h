
// Test 2Dlg.h: 头文件


#pragma once
#include "Resource.h"
#include "snake.h"


// CTest2Dlg 对话框
class CTest2Dlg : public CDialogEx
{
// 构造
public:
	CTest2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	snake s_snake;
	CPoint s_bean;
	int my_score=0;
	
public:
	int random();
	void SetBean();
	void DrawBean();
	void GameStart();
	void DrawSnake();
	void SnakeMove();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ShowScores();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnEnChangeScore();
	CEdit Myscore;
};
