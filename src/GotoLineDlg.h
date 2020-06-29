#pragma once
#include "afxwin.h"


// CGotoLineDlg 对话框

class CGotoLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGotoLineDlg)

public:
	CGotoLineDlg(UINT maxLineNo, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGotoLineDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_GOTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_uiLineNo;
	UINT m_maxLineNo;
	CStatic m_ctrText;
	virtual BOOL OnInitDialog();
};
