
// log4cViewDoc.cpp : Clog4cViewDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "log4cView.h"
#endif

#include "log4cViewDoc.h"
#include "MainFrm.h"

#include <propkey.h>
#include <stl/define.hpp>
#include <stl/algorithm/base.hpp>
//#include <stl/os.hpp>
#include <stl/os/file.hpp>
//#include <stl/time.hpp>
#include <stl/lexical/as.hpp>

struct tmExtend: public std::tm
{
	int tm_mill;
};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Clog4cViewDoc

IMPLEMENT_DYNCREATE(Clog4cViewDoc, CDocument)

BEGIN_MESSAGE_MAP(Clog4cViewDoc, CDocument)
	ON_COMMAND(ID_APP_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_GO_LINE, &Clog4cViewDoc::OnGoLine)
	ON_COMMAND(ID_FILETER, &Clog4cViewDoc::OnFileter)
END_MESSAGE_MAP()


// Clog4cViewDoc 构造/析构

Clog4cViewDoc::Clog4cViewDoc()
{
	// TODO: 在此添加一次性构造代码

}

Clog4cViewDoc::~Clog4cViewDoc()
{
}

BOOL Clog4cViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// Clog4cViewDoc 序列化

void Clog4cViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void Clog4cViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void Clog4cViewDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void Clog4cViewDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Clog4cViewDoc 诊断

#ifdef _DEBUG
void Clog4cViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Clog4cViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Clog4cViewDoc 命令
CLog4cView* Clog4cViewDoc::GetLogView()
{
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (NULL != pMainFrm)
	{
		CLog4cView * plogview=(CLog4cView*)pMainFrm->GetActiveView();
		if (NULL != plogview)
		{
			return plogview;
		}
	}
	return NULL;
}

BOOL Clog4cViewDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// TODO:  在此添加您专用的创建代码
	ReadLogMessage(lpszPathName, m_mapLogInfo);

	CLog4cView* viewPtr = GetLogView();

	if (viewPtr != NULL)
	{
		viewPtr->m_mapCurrentLog = m_mapLogInfo;
		viewPtr->showLogMessage(m_mapLogInfo);
	}

	return FALSE;
}

void Clog4cViewDoc::OnFileExit()
{
	if(IDOK == AfxMessageBox(
							 _T("是否确认要退出日志系统?"), \
							 MB_OKCANCEL|MB_ICONEXCLAMATION|MB_DEFBUTTON2)
							)
	{
		this->OnCloseDocument();
	}
}

void Clog4cViewDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here

	CFileDialog pCFileDialog(TRUE, NULL, NULL, OFN_READONLY, "日志文件(*.log4c)|*.log4c|日志文件(*.log)|*.log");
	pCFileDialog.m_ofn.lpstrTitle = "打开文件"; 
	if(pCFileDialog.DoModal()!=IDOK)
	{
		return;
	}
	m_strLogFile = pCFileDialog.GetPathName();
	
	ReadLogMessage(m_strLogFile.GetBuffer(0), m_mapLogInfo);

	CLog4cView* viewPtr = GetLogView();

	if (viewPtr != NULL)
	{
		viewPtr->m_mapCurrentLog = m_mapLogInfo;
		viewPtr->showLogMessage(m_mapLogInfo);
	}
}

void Clog4cViewDoc::ReadLogMessage(const std::string& file, std::map<int, Record>& logInfo)
{
	if (file.find(".log4c") == file.npos)
	{
		return;
	}

	logInfo.clear();
	m_ErrorList.clear();
	m_WarningList.clear();

	std::shared_ptr<stl::os::io::CIO> filePtr_ = std::make_shared<stl::os::io::CIO>(file, _O_BINARY|_O_RDWR, 0);
	if (!filePtr_->Opened())
	{
		return;
	}

	int pos = 0, flag;

	while(1)
	{
		Record record;
		int log_id;
		flag = filePtr_->Read(&log_id, MAX_RECORD_NO_LEN);
		if (flag<=0)
		{
			break;
		}
		record.id = stl::lexical::as<std::string, int>(log_id);
		record.layer.resize(MAX_LAYER_NAME_LEN+1, 0);
		flag = filePtr_->Read((void*)record.layer.c_str(), MAX_LAYER_NAME_LEN);
		if (flag<=0)
		{
			break;
		}
		//SYSTEMTIME time;
		tmExtend time;
		filePtr_->Read(&time, sizeof(tmExtend));
		std::unique_ptr<char[]> buffer(new char[1024]());
		sprintf(&buffer[0], "%04d-%02d-%02d %02d:%02d:%02d.%03d", 
			time.tm_year, time.tm_mon, time.tm_mday, \
			time.tm_hour, time.tm_min, time.tm_sec, time.tm_mill);
		record.time = &buffer[0];
		//record.time = stl::time::GetLocalTime("%04d-%02d-%02d %02d:%02d:%02d.%03d", time);
		record.type.resize(MAX_TYPE_LEN+1, 0);
		filePtr_->Read((void*)record.type.c_str(), MAX_TYPE_LEN);
		record.file.resize(MAX_FILE_NAME_LEN+1, 0);
		filePtr_->Read((void*)record.file.c_str(), MAX_FILE_NAME_LEN);
		int lineNo;
		filePtr_->Read(&lineNo, sizeof(int));
		record.lineNo = stl::lexical::as<std::string, int>(lineNo);
		record.func.resize(MAX_FUNC_NAME_LEN+1, 0);
		filePtr_->Read((void*)record.func.c_str(), MAX_FUNC_NAME_LEN);
		record.cryptMode.resize(10, 0);
		filePtr_->Read((void*)record.cryptMode.c_str(), 1);
		//DWORD threadId;
		unsigned long long threadId;
		filePtr_->Read(&threadId, MAX_THREAD_ID_LEN);
		record.threadId = stl::lexical::as<std::string, unsigned long long>(threadId);
		int contentLen;
		filePtr_->Read(&contentLen, MAX_RECORD_NO_LEN);
		std::string content(contentLen+1, 0);
		filePtr_->Read((void*)content.c_str(), contentLen);
		stl::algorithm::base64::decode(record.content, content);

		if (record.type.find("WAR") != record.type.npos)
		{
			m_WarningList.push_back(pos);
		}
		if (record.type.find("ERROR") != record.type.npos)
		{
			m_ErrorList.push_back(pos);
		}

		logInfo[pos++] = record;
	}
}

void Clog4cViewDoc::OnGoLine()
{
	// TODO: 在此添加命令处理程序代码
	GetLogView()->GotoLine();
}


void Clog4cViewDoc::OnFileter()
{
	// TODO: 在此添加命令处理程序代码
	GetLogView()->GotoFilter();
}
