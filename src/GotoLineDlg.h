#pragma once
#include "afxwin.h"


// CGotoLineDlg �Ի���

class CGotoLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGotoLineDlg)

public:
	CGotoLineDlg(UINT maxLineNo, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGotoLineDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_GOTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_uiLineNo;
	UINT m_maxLineNo;
	CStatic m_ctrText;
	virtual BOOL OnInitDialog();
};
