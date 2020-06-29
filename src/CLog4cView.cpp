// CLog4cView.cpp : 实现文件
//

#include "stdafx.h"
#include "log4cView.h"
#include "CLog4cView.h"


// CLog4cView

IMPLEMENT_DYNCREATE(CLog4cView, CFormView)

CLog4cView::CLog4cView()
	: CFormView(CLog4cView::IDD)
	, m_hOldFont(NULL)
{

}

CLog4cView::~CLog4cView()
{
}

void CLog4cView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrLogList);
}

BEGIN_MESSAGE_MAP(CLog4cView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_LOG, &CLog4cView::OnNMCustomdrawListLog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOG, &CLog4cView::OnNMDblclkListLog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOG, &CLog4cView::OnNMRClickListLog)
	ON_COMMAND(ID__BOLD_ROW, &CLog4cView::OnBoldRow)
	ON_COMMAND(ID__KEY_BAT_FIND, &CLog4cView::OnKeyBatFind)
END_MESSAGE_MAP()


// CLog4cView 诊断

#ifdef _DEBUG
void CLog4cView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLog4cView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLog4cView 消息处理程序
Clog4cViewDoc* CLog4cView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clog4cViewDoc)));
	return (Clog4cViewDoc*)m_pDocument;
}

void CLog4cView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_ctrLogList.GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);
		rc.top += 5;
		rc.left += 5;
		rc.right -= 5;
		rc.bottom -= 5; 
		m_ctrLogList.MoveWindow(rc); //也可GetDlgItem(IDC_LISTCTRL)->MoveWindow(rc);
	}	
}

void CLog4cView::insertLogMessage(int pos, const Record& record)
{
	m_ctrLogList.InsertItem(pos,	 record.id.c_str());
	m_ctrLogList.SetItemText(pos, 1, record.layer.c_str());
	m_ctrLogList.SetItemText(pos, 2, record.time.c_str());
	m_ctrLogList.SetItemText(pos, 3, record.type.c_str());
	m_ctrLogList.SetItemText(pos, 4, record.file.c_str());
	m_ctrLogList.SetItemText(pos, 5, record.lineNo.c_str());
	m_ctrLogList.SetItemText(pos, 6, record.func.c_str());
	m_ctrLogList.SetItemText(pos, 7, record.threadId.c_str());
	m_ctrLogList.SetItemText(pos, 8, record.content.c_str());
}

void CLog4cView::showLogMessage(std::map<int, Record> info)
{
	m_ctrLogList.DeleteAllItems();
	m_ctrLogList.SetRedraw(FALSE);
	typedef std::map<int, Record>::iterator Itor;
	int pos = 0;
	for (Itor it  = info.begin(); 
		it != info.end(); it++, pos++)
	{
		insertLogMessage(pos, it->second);
	}
	m_ctrLogList.SetRedraw(TRUE);
	m_ctrLogList.Invalidate();
	m_ctrLogList.UpdateWindow();
}

void CLog4cView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	LONG lStyle;
	lStyle = GetWindowLong(m_ctrLogList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_ctrLogList.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_ctrLogList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_HEADERDRAGDROP;
	m_ctrLogList.SetExtendedStyle(dwStyle); //设置扩展风格	

	m_ctrLogList.InsertColumn(0, _T("序号"), LVCFMT_RIGHT, 50, 0);
	m_ctrLogList.InsertColumn(1, _T("层次名"), LVCFMT_LEFT, 100, 1);
	m_ctrLogList.InsertColumn(2, _T("时间"), LVCFMT_LEFT, 150, 2);
	m_ctrLogList.InsertColumn(3, _T("日志类型"), LVCFMT_LEFT, 60, 3);	
	m_ctrLogList.InsertColumn(4, _T("文件名"), LVCFMT_LEFT, 140, 4);	
	m_ctrLogList.InsertColumn(5, _T("行号"), LVCFMT_RIGHT, 40, 5);
	m_ctrLogList.InsertColumn(6, _T("函数名"), LVCFMT_LEFT, 110, 6);
	m_ctrLogList.InsertColumn(7, _T("线程号"), LVCFMT_RIGHT, 50, 7);
	m_ctrLogList.InsertColumn(8, _T("详细情况"), LVCFMT_LEFT, 614, 8);
	m_ctrLogList.DeleteAllItems();

	CFont* pFont = GetFont();
	ASSERT_VALID (pFont);

	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));
	pFont->GetLogFont (&lf);
	lf.lfWeight = FW_BOLD;
	m_BoldFont.CreateFontIndirect(&lf);
}


void CLog4cView::OnNMCustomdrawListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW lpcustomDraw = (LPNMLVCUSTOMDRAW)pNMHDR;
	switch(lpcustomDraw->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		{
			*pResult = CDRF_DODEFAULT;
			int nItem = static_cast<int>( lpcustomDraw->nmcd.dwItemSpec );

			std::string logId = m_ctrLogList.GetItemText(nItem, 0).GetBuffer(0);
			std::list<std::string>::iterator LogIdIt;
			LogIdIt = std::find(m_boldRowlist.begin(), m_boldRowlist.end(), logId);
			if (LogIdIt != m_boldRowlist.end())
			{
				m_hOldFont = (HFONT)SelectObject(lpcustomDraw->nmcd.hdc, m_BoldFont.GetSafeHandle());
				ASSERT (m_hOldFont != NULL);
				*pResult = CDRF_NEWFONT | CDRF_NOTIFYPOSTPAINT;
			}

			std::list<int> warningList = GetDocument()->m_WarningList;
			std::list<int>::iterator it=std::find(warningList.begin(), warningList.end(), nItem);
			if (it != warningList.end())
			{
				lpcustomDraw->clrText = RGB_TEXT_COLOR;
				lpcustomDraw->clrTextBk = RGB_WARING_COLOR;
				return;
			}
			std::list<int> errorList = GetDocument()->m_ErrorList;
			std::list<int>::iterator errIt=std::find(errorList.begin(), errorList.end(), nItem);
			if (errIt != errorList.end())
			{
				lpcustomDraw->clrText = RGB_TEXT_COLOR;
				lpcustomDraw->clrTextBk = RGB_ERROR_COLOR;
			}
		}
		break;
	case CDDS_ITEMPOSTPAINT:
		{
			if (m_hOldFont != NULL)
			{
				SelectObject (lpcustomDraw->nmcd.hdc, m_hOldFont);
				m_hOldFont = NULL;
			}
			*pResult = CDRF_DODEFAULT;
			break;
		}
	}
}

#include "LogDetails.h"
void CLog4cView::OnNMDblclkListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)
	{
		std::unique_ptr<char[]> logId(new char[128]());
		m_ctrLogList.GetItemText(pNMListView->iItem, 0, &logId[0], 128);
		typedef std::map<int, Record>::iterator LogIter;
		for (LogIter it  = m_mapCurrentLog.begin();
			         it != m_mapCurrentLog.end();
					 it++)
		{
			if (it->second.id.find(&logId[0]) != std::string::npos)
			{
				CLogDetails details(it->second);
				details.DoModal();
				break;
			}
		}

	}
}
#include "GotoLineDlg.h"
void CLog4cView::GotoLine()
{
	CGotoLineDlg lineDlg(GetDocument()->m_mapLogInfo.size());

	if (IDOK == lineDlg.DoModal())
	{
		ShowTopItem(lineDlg.m_uiLineNo-1);
	}
}

#include "LogFilterDlg.h"
void CLog4cView::GotoFilter()
{
	CLogFilterDlg dlg(GetDocument()->m_mapLogInfo);
	if (IDOK == dlg.DoModal())
	{
		GetDocument()->m_WarningList.clear();
		GetDocument()->m_ErrorList.clear();
		int pos = 0;
		typedef std::map<int, Record>::iterator Itor;
		for (Itor it  = dlg.m_mapLogFilter.begin();
				  it != dlg.m_mapLogFilter.end(); it++, pos++)
		{
			if (it->second.type.find("WAR")!=std::string::npos)
			{
				GetDocument()->m_WarningList.push_back(pos);
			}
			if (it->second.type.find("ERR")!=std::string::npos)
			{
				GetDocument()->m_ErrorList.push_back(pos);
			}
		}
		m_mapCurrentLog = dlg.m_mapLogFilter;
		showLogMessage(dlg.m_mapLogFilter);
	}
}

void CLog4cView::ShowTopItem(int nSelectItem)
{
	m_ctrLogList.SetItemState(nSelectItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_ctrLogList.EnsureVisible(nSelectItem, TRUE);
}


void CLog4cView::OnNMRClickListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_FILTER ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	} 
	*pResult = 0;
}


void CLog4cView::OnBoldRow()
{
	// TODO: 在此添加命令处理程序代码
	std::string logId = m_ctrLogList.GetItemText(m_ctrLogList.GetSelectionMark(), 0).GetBuffer(0);
	std::list<std::string>::iterator it=std::find(m_boldRowlist.begin(), m_boldRowlist.end(), logId);
	if (it==m_boldRowlist.end())
	{
		m_boldRowlist.push_back(logId);
	}
	else
	{
		m_boldRowlist.erase(it);
	}
}

#include "LogKeyFindDlg.h"
void CLog4cView::OnKeyBatFind()
{
	// TODO: 在此添加命令处理程序代码
	CLogKeyFindDlg  dlg(m_mapCurrentLog);
	if (IDOK == dlg.DoModal())
	{
		showLogMessage(dlg.m_mapKeyFind);
		m_mapCurrentLog = dlg.m_mapKeyFind;
	}
}
