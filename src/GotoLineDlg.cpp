// GotoLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "log4cView.h"
#include "GotoLineDlg.h"
#include "afxdialogex.h"


// CGotoLineDlg �Ի���

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


// CGotoLineDlg ��Ϣ�������



BOOL CGotoLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString info;
	info.Format("�к�(1-%d)(L):", m_maxLineNo);
	m_ctrText.SetWindowText(info);
	GetDlgItem(IDC_EDIT_LINENO)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
