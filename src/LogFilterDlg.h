#pragma once
#include "afxwin.h"


// CLogFilterDlg �Ի���

class CLogFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogFilterDlg)

public:
	CLogFilterDlg(std::map<int, Record> logMessage, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogFilterDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	int m_logLevel;
public:
	virtual BOOL OnInitDialog();
	CButton m_ctrDebug;
	CButton m_ctrInfor;
	CButton m_ctrWarning;
	CButton m_ctrError;
	CComboBox m_ctrLayer;
	CComboBox m_ctrFile;
	std::map<int, Record> m_mapLogAll;
	std::map<int, Record> m_mapLogFilter;
	std::list<std::string> m_layerList;
	std::list<std::string> m_FileList;
	std::list<std::string> m_ThreadList;
	afx_msg void OnBnClickedOk();
	BOOL	filterLogMessage(CString layer, CString file, CString threadId, Record record);
	CComboBox m_ctrThreadID;
};
