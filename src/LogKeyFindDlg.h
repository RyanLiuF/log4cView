#pragma once


// CLogKeyFindDlg 对话框

class CLogKeyFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogKeyFindDlg)

public:
	CLogKeyFindDlg(std::map<int, Record> logMessage, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogKeyFindDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_KEY_FIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strKey;
	afx_msg void OnBnClickedOk();
	std::map<int, Record> m_mapLogAll;
	std::map<int, Record> m_mapKeyFind;
};
