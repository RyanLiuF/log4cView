// LogFilterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "log4cView.h"
#include "LogFilterDlg.h"
#include "afxdialogex.h"


// CLogFilterDlg 对话框

IMPLEMENT_DYNAMIC(CLogFilterDlg, CDialogEx)

CLogFilterDlg::CLogFilterDlg(std::map<int, Record> logMessage, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogFilterDlg::IDD, pParent)
	, m_mapLogAll(logMessage)
	, m_logLevel(0x1111)
{

}

CLogFilterDlg::~CLogFilterDlg()
{
}

void CLogFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DEBUG, m_ctrDebug);
	DDX_Control(pDX, IDC_CHECK_INFOR, m_ctrInfor);
	DDX_Control(pDX, IDC_CHECK_WARNING, m_ctrWarning);
	DDX_Control(pDX, IDC_CHECK_ERROR, m_ctrError);
	DDX_Control(pDX, IDC_COMBO_LAYER, m_ctrLayer);
	DDX_Control(pDX, IDC_COMBO_FILE, m_ctrFile);
	DDX_Control(pDX, IDC_COMBO_THREADID, m_ctrThreadID);
}


BEGIN_MESSAGE_MAP(CLogFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogFilterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogFilterDlg 消息处理程序


BOOL CLogFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrDebug.SetCheck(TRUE);
	m_ctrError.SetCheck(TRUE);
	m_ctrInfor.SetCheck(TRUE);
	m_ctrWarning.SetCheck(TRUE);

	typedef std::map<int, Record>::iterator LogIter;
	for (LogIter it  = m_mapLogAll.begin(); 
		it != m_mapLogAll.end(); it++)
	{
		std::list<std::string>::iterator layerIt = std::find(m_layerList.begin(), m_layerList.end(), it->second.layer);
		if (layerIt == m_layerList.end())
		{
			m_layerList.push_back(it->second.layer);
		}
		std::list<std::string>::iterator fileIt = std::find(m_FileList.begin(), m_FileList.end(), it->second.file);
		if (fileIt == m_FileList.end())
		{
			m_FileList.push_back(it->second.file);
		}
		std::list<std::string>::iterator ThreadIt = std::find(m_ThreadList.begin(), m_ThreadList.end(), it->second.threadId);
		if (ThreadIt == m_ThreadList.end())
		{
			m_ThreadList.push_back(it->second.threadId);
		}
	}

	m_ctrLayer.ResetContent();
	m_ctrLayer.AddString("All");
	for (std::list<std::string>::iterator
		 layerIt  = m_layerList.begin(); 
		 layerIt != m_layerList.end(); layerIt++)
	{
		m_ctrLayer.AddString((*layerIt).c_str());
	}
	m_ctrLayer.SetCurSel(0);

	m_ctrFile.ResetContent();
	m_ctrFile.AddString("All");
	for (std::list<std::string>::iterator
		fileIt  = m_FileList.begin(); 
		fileIt != m_FileList.end(); fileIt++)
	{
		m_ctrFile.AddString((*fileIt).c_str());
	}
	m_ctrFile.SetCurSel(0);

	m_ctrThreadID.ResetContent();
	m_ctrThreadID.AddString("All");
	for (std::list<std::string>::iterator
		threadIt  = m_ThreadList.begin(); 
		threadIt != m_ThreadList.end(); threadIt++)
	{
		m_ctrThreadID.AddString((*threadIt).c_str());
	}
	m_ctrThreadID.SetCurSel(0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLogFilterDlg::filterLogMessage(CString layer, CString file, CString threadId, Record record)
{
	if ( (layer.Find("All")!= -1 || record.layer.find(layer.GetBuffer(0))!=std::string::npos) &&
		 (file.Find("All")!= -1  || record.file.find(file.GetBuffer(0))!=std::string::npos) &&
		 (threadId.Find("All")!= -1 || record.threadId.find(threadId.GetBuffer(0))!=std::string::npos) )
	{
		return TRUE;
	}
	return FALSE;
}

void CLogFilterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(TRUE);

	CString file;
	m_ctrFile.GetWindowText(file);
	CString layer;
	m_ctrLayer.GetWindowText(layer);
	CString threadId;
	m_ctrThreadID.GetWindowText(threadId);

	typedef std::map<int, Record>::iterator LogIter;
	for (LogIter it  = m_mapLogAll.begin(); 
		it != m_mapLogAll.end(); it++)
	{
		if (m_ctrDebug.GetCheck() && it->second.type.find("DEBUG")!=std::string::npos)
		{
			if (filterLogMessage(layer, file, threadId, it->second))
			{
				m_mapLogFilter[it->first] = it->second;
			}
		}

		if (m_ctrInfor.GetCheck() && it->second.type.find("INFOR")!=std::string::npos)
		{
			if (filterLogMessage(layer, file, threadId, it->second))
			{
				m_mapLogFilter[it->first] = it->second;
			}
		}

		if (m_ctrWarning.GetCheck() && it->second.type.find("WAR")!=std::string::npos)
		{
			if (filterLogMessage(layer, file, threadId, it->second))
			{
				m_mapLogFilter[it->first] = it->second;
			}
		}

		if (m_ctrError.GetCheck() && it->second.type.find("ERR")!=std::string::npos)
		{
			if (filterLogMessage(layer, file, threadId, it->second))
			{
				m_mapLogFilter[it->first] = it->second;
			}
		}
	}
}
