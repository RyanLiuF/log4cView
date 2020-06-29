#pragma once
#include "afxcmn.h"
#include "log4cViewDoc.h"

// CLog4cView 窗体视图

class CLog4cView : public CFormView
{
	DECLARE_DYNCREATE(CLog4cView)

protected:
	CLog4cView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLog4cView();

public:
	enum { IDD = IDD_LOG4CVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	class Clog4cViewDoc* GetDocument();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_ctrLogList;
	virtual void OnInitialUpdate();
	void showLogMessage(std::map<int, Record> info);
	void insertLogMessage(int pos, const Record& record);
	afx_msg void OnNMCustomdrawListLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListLog(NMHDR *pNMHDR, LRESULT *pResult);
	void GotoLine();
	void GotoFilter();
	void ShowTopItem(int nSelectItem);
	std::list<std::string> m_boldRowlist;
	std::map<int, Record> m_mapCurrentLog;
	afx_msg void OnNMRClickListLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBoldRow();
	CFont	m_BoldFont;
	HFONT   m_hOldFont;
	afx_msg void OnKeyBatFind();
};


