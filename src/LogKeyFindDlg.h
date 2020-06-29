#pragma once


// CLogKeyFindDlg �Ի���

class CLogKeyFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogKeyFindDlg)

public:
	CLogKeyFindDlg(std::map<int, Record> logMessage, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogKeyFindDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_KEY_FIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strKey;
	afx_msg void OnBnClickedOk();
	std::map<int, Record> m_mapLogAll;
	std::map<int, Record> m_mapKeyFind;
};
