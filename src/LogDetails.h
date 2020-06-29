#pragma once


// CLogDetails 对话框

class CLogDetails : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDetails)

public:
	CLogDetails(const Record& record,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogDetails();

// 对话框数据
	enum { IDD = IDD_DIALOG_DETAILES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strLogId;
	CString m_strThreadId;
	CString m_strLayer;
	CString m_strTime;
	CString m_strType;
	CString m_strFile;
	CString m_strLineNo;
	CString m_strFunc;
	CString m_strContent;
	Record  m_record;
	virtual BOOL OnInitDialog();
};
