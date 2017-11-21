/**********************************************************************

  文件名: MainFrm.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "VRToolBar.h"
#include "VRAppDoc.h"
#include "VRAppView.h"
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	CVRToolBar m_ToolBar;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnUpdateColorInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateColorView(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateOpacityInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateOpacityView(WPARAM wParam, LPARAM lParam);

};


