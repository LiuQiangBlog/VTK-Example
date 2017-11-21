/**********************************************************************

  文件名: vtkSDIView.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkSDIView.cpp : implementation of the CvtkSDIView class
//

#include "stdafx.h"
#include "vtkSDI.h"

#include "vtkSDIDoc.h"
#include "vtkSDIView.h"

#include "vtkRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkSDIView

IMPLEMENT_DYNCREATE(CvtkSDIView, CView)

BEGIN_MESSAGE_MAP(CvtkSDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CvtkSDIView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkSDIView construction/destruction

CvtkSDIView::CvtkSDIView()
{
	// TODO: add construction code here

	

}

CvtkSDIView::~CvtkSDIView()
{
	m_pImageViewer = NULL;
	m_pRenderWindowInteractor = NULL;
}

BOOL CvtkSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CvtkSDIView drawing

void CvtkSDIView::OnDraw(CDC* /*pDC*/)
{
	CvtkSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_pImageViewer->SetInput(pDoc->m_pImageData);
	m_pImageViewer->Render();
}


// CvtkSDIView printing


void CvtkSDIView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CvtkSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CvtkSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CvtkSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CvtkSDIView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CvtkSDIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CvtkSDIView diagnostics

#ifdef _DEBUG
void CvtkSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkSDIDoc* CvtkSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkSDIDoc)));
	return (CvtkSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkSDIView message handlers

int CvtkSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pImageViewer->SetParentId(GetSafeHwnd());
	m_pImageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

	m_pRenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	m_pImageViewer->SetupInteractor(m_pRenderWindowInteractor);
	m_pRenderWindowInteractor->Start();

	return 0;
}

void CvtkSDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	CRect rect;
	GetClientRect(rect);

	m_pImageViewer->SetSize(rect.Width(), rect.Height());

}
