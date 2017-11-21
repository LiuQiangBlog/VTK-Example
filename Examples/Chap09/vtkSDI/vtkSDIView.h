/**********************************************************************

  文件名: vtkSDIView.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkSDIView.h : interface of the CvtkSDIView class
//


#pragma once

#include "vtkSmartPointer.h"
#include "vtkImageViewer2.h"
#include "vtkRenderWindowInteractor.h"

class CvtkSDIView : public CView
{
protected: // create from serialization only
	CvtkSDIView();
	DECLARE_DYNCREATE(CvtkSDIView)

// Attributes
public:
	CvtkSDIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CvtkSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


private:

	vtkSmartPointer<vtkImageViewer2>           m_pImageViewer;
	vtkSmartPointer<vtkRenderWindowInteractor> m_pRenderWindowInteractor;



public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in vtkSDIView.cpp
inline CvtkSDIDoc* CvtkSDIView::GetDocument() const
   { return reinterpret_cast<CvtkSDIDoc*>(m_pDocument); }
#endif

