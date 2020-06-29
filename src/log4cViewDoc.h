
// log4cViewDoc.h : Clog4cViewDoc 类的接口
//


#pragma once

#include "CLog4cView.h"

class Clog4cViewDoc : public CDocument
{
protected: // 仅从序列化创建
	Clog4cViewDoc();
	DECLARE_DYNCREATE(Clog4cViewDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~Clog4cViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	class CLog4cView* GetLogView();
	afx_msg void OnFileOpen();
	afx_msg void OnFileExit();
	CString m_strLogFile;
	std::map<int, Record> m_mapLogInfo;
	std::list<int> m_WarningList;
	std::list<int> m_ErrorList;
	void ReadLogMessage(const std::string& file, std::map<int, Record>& logInfo);
	afx_msg void OnGoLine();
	afx_msg void OnFileter();
};
