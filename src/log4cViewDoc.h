
// log4cViewDoc.h : Clog4cViewDoc ��Ľӿ�
//


#pragma once

#include "CLog4cView.h"

class Clog4cViewDoc : public CDocument
{
protected: // �������л�����
	Clog4cViewDoc();
	DECLARE_DYNCREATE(Clog4cViewDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~Clog4cViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
