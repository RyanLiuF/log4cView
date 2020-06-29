
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <string>
#include <list>
#include <map>
#include <algorithm>

#define MAX_BUFFER_SIZE		8196
#define MAX_FUNC_NAME_LEN	64
#define MAX_LAYER_NAME_LEN	32
#define MAX_FILE_NAME_LEN	32
#define MAX_RECORD_NO_LEN	4
#define MAX_THREAD_ID_LEN	8
#define MAX_TYPE_LEN		8

#define RGB_TEXT_COLOR		RGB(0x00, 0x00, 0x00)
#define RGB_DEBUG_COLOR		RGB(0x00, 0x00, 0x00)
#define RGB_WARING_COLOR	RGB(0xFF, 0xFF, 0x00)
#define RGB_INFOR_COLOR		RGB(0x00, 0x00, 0x00)
#define RGB_ERROR_COLOR		RGB(0xFF, 0x78, 0x00)

typedef struct
{
	std::string layer;
	std::string type;
	std::string file;
	std::string func;
	std::string root;
	std::string content;
	std::string	time;
	std::string lineNo;
	std::string cryptMode;
	std::string threadId;
	std::string id;
}Record, *LPRecord;