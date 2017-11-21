/**********************************************************************

  文件名: MainFrm.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VRApp.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WM_UPDATE_COLOR_INFO_MSG,   OnUpdateColorInfo)
	ON_MESSAGE(WM_UPDATE_COLOR_VIEW_MSG,   OnUpdateColorView)
	ON_MESSAGE(WM_UPDATE_OPACITY_INFO_MSG, OnUpdateOpacityInfo)
	ON_MESSAGE(WM_UPDATE_OPACITY_VIEW_MSG, OnUpdateOpacityView)

END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//m_strTitle = " "; 

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!m_ToolBar.Create(this, IDD_VR_TOOLBAR,   CBRS_LEFT
		, IDD_VR_TOOLBAR))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}

	//m_ToolBar.EnableDocking(CBRS_ALIGN_BOTTOM );
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_ToolBar, AFX_IDW_DOCKBAR_BOTTOM);

	return 0;
}

afx_msg LRESULT CMainFrame::OnUpdateColorInfo(WPARAM wParam, LPARAM lParam)
{
	double v, r, g, b;
	if( m_ToolBar.m_VolumeColor.GetCurrentValueColor(v, r, g, b) )
	{
		m_ToolBar.UpdateColorInfo(v);
	}

	return 1;
}

afx_msg LRESULT CMainFrame::OnUpdateColorView(WPARAM wParam, LPARAM lParam)
{
	((CVRAppView*)GetActiveView())->OnUpdateColor();
	return 1;
}
afx_msg LRESULT CMainFrame::OnUpdateOpacityInfo(WPARAM wParam, LPARAM lParam)
{
	double gray, opacity;
	if(m_ToolBar.m_VolumeOpacity.GetCurrentKeyPoint(gray, opacity))
	{
		m_ToolBar.UpdateOpacityInfo(gray, opacity);
	}

	return 1;
}

afx_msg LRESULT CMainFrame::OnUpdateOpacityView(WPARAM wParam, LPARAM lParam)
{
	((CVRAppView*)GetActiveView())->OnUpdateOpacity();
	return 1;
}