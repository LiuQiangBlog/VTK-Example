/**********************************************************************

  文件名: VRApp.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// VRApp.h : main header file for the VRApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVRAppApp:
// See VRApp.cpp for the implementation of this class
//

class CVRAppApp : public CWinApp
{
public:
	CVRAppApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	// -------------------GDI+---------------------------
protected:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
public:
	virtual int ExitInstance();
	// -------------------GDI+---------------------------
};

extern CVRAppApp theApp;
