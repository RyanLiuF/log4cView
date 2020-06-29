
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









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