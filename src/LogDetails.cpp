// LogDetails.cpp : 实现文件
//

#include "stdafx.h"
#include "log4cView.h"
#include "LogDetails.h"
#include "afxdialogex.h"


// CLogDetails 对话框

IMPLEMENT_DYNAMIC(CLogDetails, CDialogEx)

CLogDetails::CLogDetails(const Record& record, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogDetails::IDD, pParent)
	, m_record(record)
	, m_strLogId(_T(""))
	, m_strThreadId(_T(""))
	, m_strLayer(_T(""))
	, m_strTime(_T(""))
	, m_strType(_T(""))
	, m_strFile(_T(""))
	, m_strLineNo(_T(""))
	, m_strFunc(_T(""))
	, m_strContent(_T(""))
{

}

CLogDetails::~CLogDetails()
{
}

void CLogDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOG_ID, m_strLogId);
	DDX_Text(pDX, IDC_EDIT_THREADID, m_strThreadId);
	DDX_Text(pDX, IDC_EDIT_LAYER, m_strLayer);
	DDX_Text(pDX, IDC_EDIT_TIME, m_strTime);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDIT_FILE, m_strFile);
	DDX_Text(pDX, IDC_EDIT_LINENO, m_strLineNo);
	DDX_Text(pDX, IDC_EDIT_FUNC, m_strFunc);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
}


BEGIN_MESSAGE_MAP(CLogDetails, CDialogEx)
END_MESSAGE_MAP()


// CLogDetails 消息处理程序


BOOL CLogDetails::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strLogId		= m_record.id.c_str();
	m_strTime		= m_record.time.c_str();
	m_strType		= m_record.type.c_str();
	m_strLayer		= m_record.layer.c_str();
	m_strFunc		= m_record.func.c_str();
	m_strThreadId	= m_record.threadId.c_str();
	m_strContent	= m_record.content.c_str();
	m_strFile		= m_record.file.c_str();
	m_strLineNo		= m_record.lineNo.c_str();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
