// LogKeyFindDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "log4cView.h"
#include "LogKeyFindDlg.h"
#include "afxdialogex.h"


// CLogKeyFindDlg 对话框

IMPLEMENT_DYNAMIC(CLogKeyFindDlg, CDialogEx)

CLogKeyFindDlg::CLogKeyFindDlg(std::map<int, Record> logMessage, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogKeyFindDlg::IDD, pParent)
	, m_mapLogAll(logMessage)
	, m_strKey(_T(""))
{

}

CLogKeyFindDlg::~CLogKeyFindDlg()
{
}

void CLogKeyFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strKey);
}


BEGIN_MESSAGE_MAP(CLogKeyFindDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogKeyFindDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogKeyFindDlg 消息处理程序


void CLogKeyFindDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(TRUE);
	if (m_strKey.IsEmpty())
	{
		m_mapKeyFind = m_mapLogAll;
		return;
	}
	typedef std::map<int, Record>::iterator Itor;
	for (Itor it  = m_mapLogAll.begin(); 
			  it != m_mapLogAll.end(); it++)
	{
		if (it->second.content.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.layer.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.type.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.file.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.func.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.time.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.lineNo.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.threadId.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
		if (it->second.id.find(m_strKey.GetBuffer(0))!=std::string::npos)
		{
			m_mapKeyFind[it->first] = it->second;
		}
	}
}
