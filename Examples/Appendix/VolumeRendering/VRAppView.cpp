/**********************************************************************

  文件名: VRAppView.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// VRAppView.cpp : implementation of the CVRAppView class
//

#include "stdafx.h"
#include "VRApp.h"

#include "VRAppDoc.h"
#include "VRAppView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include <vector>
using namespace std;

// CVRAppView

IMPLEMENT_DYNCREATE(CVRAppView, CView)

BEGIN_MESSAGE_MAP(CVRAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()

END_MESSAGE_MAP()

// CVRAppView construction/destruction

CVRAppView::CVRAppView()
{
	// TODO: add construction code here

	rayCastFun = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	ren = vtkSmartPointer<vtkRenderer>::New();
	volume = vtkSmartPointer<vtkVolume>::New();
	renWin = vtkSmartPointer<vtkRenderWindow>::New();
	iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

}

CVRAppView::~CVRAppView()
{
}

BOOL CVRAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVRAppView drawing

void CVRAppView::OnDraw(CDC* /*pDC*/)
{
	CVRAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	renWin->Render();
}


// CVRAppView printing

BOOL CVRAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVRAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVRAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVRAppView diagnostics

#ifdef _DEBUG
void CVRAppView::AssertValid() const
{
	CView::AssertValid();
}

void CVRAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVRAppDoc* CVRAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVRAppDoc)));
	return (CVRAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CVRAppView message handlers

int CVRAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	volumeMapper->SetVolumeRayCastFunction(rayCastFun);
	volume->SetMapper(volumeMapper);

	ren->SetBackground(0.5f,0.5f,1.0f);
	ren->AddVolume( volume ); 

	renWin->AddRenderer(ren);
	renWin->SetParentId(this->GetSafeHwnd());

	iren->SetRenderWindow(renWin);
	
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);
	
	iren->Start();

	return 0;
}

void CVRAppView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(rect);

	renWin->SetSize(rect.Width(), rect.Height());

}

void CVRAppView::SetInput()
{
	CVRAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)	return;

	volumeMapper->SetInputConnection(pDoc->m_pImageData->GetProducerPort());
	ren->ResetCamera();
	renWin->Render();
}

void CVRAppView::OnUpdateOpacity()
{
	vtkSmartPointer<vtkPiecewiseFunction> opacityfunction = 
		vtkSmartPointer<vtkPiecewiseFunction>::New();

	std::vector<std::pair<double, double>> OpacityKeyPoints;
	((CMainFrame*)AfxGetMainWnd())->m_ToolBar.m_VolumeOpacity.GetKeyPointPair(OpacityKeyPoints);

	for (int i=0; i<OpacityKeyPoints.size(); i++)
	{
		opacityfunction->AddPoint(OpacityKeyPoints[i].first, OpacityKeyPoints[i].second);
	}
	opacityfunction->SetClamping(1);
	volume->GetProperty()->SetScalarOpacity(opacityfunction);
	renWin->Render();
}

void CVRAppView::OnUpdateColor()
{
	vtkSmartPointer<vtkColorTransferFunction> color = 
		vtkSmartPointer<vtkColorTransferFunction>::New();

	std::vector<std::vector<double>> table;
	((CMainFrame*)AfxGetMainWnd())->m_ToolBar.m_VolumeColor.GetValueColorTable(table);

	int segNum = table.size();
	for (int n = 0; n <segNum; n++)
	{
		color->AddRGBPoint( table[n][0], table[n][1],table[n][2],table[n][3]);
	}

	volume->GetProperty()->SetColor(color);
	renWin->Render();

}
