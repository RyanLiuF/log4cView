// GotoLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "log4cView.h"
#include "GotoLineDlg.h"
#include "afxdialogex.h"


// CGotoLineDlg 对话框

IMPLEMENT_DYNAMIC(CGotoLineDlg, CDialogEx)

CGotoLineDlg::CGotoLineDlg(UINT maxLineNo, CWnd* pParent /*=NULL*/)
	: CDialogEx(CGotoLineDlg::IDD, pParent)
	, m_uiLineNo(1)
	, m_maxLineNo(maxLineNo)
{

}

CGotoLineDlg::~CGotoLineDlg()
{
}

void CGotoLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LINENO, m_uiLineNo);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_ctrText);
}


BEGIN_MESSAGE_MAP(CGotoLineDlg, CDialogEx)
END_MESSAGE_MAP()


// CGotoLineDlg 消息处理程序



BOOL CGotoLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString info;
	info.Format("行号(1-%d)(L):", m_maxLineNo);
	m_ctrText.SetWindowText(info);
	GetDlgItem(IDC_EDIT_LINENO)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
