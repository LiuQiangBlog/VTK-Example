/**********************************************************************

  文件名: vtkView.cpp 
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkView.cpp : implementation file
//

#include "stdafx.h"
#include "vtkDialog.h"
#include "vtkView.h"

#include "vtkRenderWindowInteractor.h"

// CvtkView

IMPLEMENT_DYNAMIC(CvtkView, CStatic)

CvtkView::CvtkView()
{
	m_ImageData = NULL;
	m_Direction = 0;
}

CvtkView::~CvtkView()
{
}


BEGIN_MESSAGE_MAP(CvtkView, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CvtkView message handlers



void CvtkView::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	GetClientRect(rect);

	m_Renderer = vtkSmartPointer<vtkRenderer>::New();

	m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	m_RenderWindow->SetParentId(this->m_hWnd);
	m_RenderWindow->SetSize(rect.Width(), rect.Height());
	m_RenderWindow->AddRenderer(m_Renderer);

	if(m_RenderWindow->GetInteractor() == NULL)
	{
		vtkSmartPointer<vtkRenderWindowInteractor> RenderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
		RenderWindowInteractor->Initialize();
	}

	m_ImagePlaneWidget = vtkSmartPointer< vtkImagePlaneWidget >::New();

	m_ResliceCursor = vtkSmartPointer< vtkResliceCursor >::New();
	m_ResliceCursorRep = vtkSmartPointer< vtkResliceCursorThickLineRepresentation >::New();
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);

	m_ResliceCursorWidget = vtkSmartPointer< vtkResliceCursorWidget>::New();
	m_ResliceCursorWidget->SetInteractor(m_RenderWindow->GetInteractor());   
    m_ResliceCursorWidget->SetDefaultRenderer(m_Renderer);  
	m_ResliceCursorWidget->SetRepresentation(m_ResliceCursorRep);


	m_RenderWindow->Start();	
	CStatic::PreSubclassWindow();
}

void CvtkView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
}

void CvtkView::SetImageData(vtkSmartPointer<vtkImageData> ImageData)
{
	if (ImageData == NULL ) return;

	m_ImageData = ImageData;
	SetupReslice();
	Render();
}
void CvtkView::SetupReslice()
{
	if (m_ImageData == NULL) return;
	int dims[3];
	m_ImageData->GetDimensions(dims);

	//////////////////////////////////////////////////////////////////////////
	m_ImagePlaneWidget->SetInput(m_ImageData); 
	m_ImagePlaneWidget->SetPlaneOrientation(m_Direction); 
	m_ImagePlaneWidget->SetSliceIndex(dims[m_Direction]/2); 
	m_ImagePlaneWidget->On(); 
	m_ImagePlaneWidget->InteractionOn(); 

	//////////////////////////////////////////////////////////////////////////
	m_ResliceCursor->SetCenter(m_ImageData->GetCenter()); 
	m_ResliceCursor->SetImage(m_ImageData); 
	m_ResliceCursor->SetThickMode(0); 

	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetResliceCursor(m_ResliceCursor);
	m_ResliceCursorRep->GetResliceCursorActor()-> 
		GetCursorAlgorithm()->SetReslicePlaneNormal(m_Direction);

	m_ResliceCursorWidget->SetEnabled(1); 
	m_Renderer->ResetCamera(); 

	//////////////////////////////////////////////////////////////////////////
	double range[2]; 
	m_ImageData->GetScalarRange(range); 
	m_ResliceCursorWidget->GetResliceCursorRepresentation()->
		SetWindowLevel(range[1]-range[0], (range[0]+range[1])/2.0); 
	m_ImagePlaneWidget->SetWindowLevel(range[1]-range[0], (range[0]+range[1])/2.0); 

	
}

void CvtkView::SetResliceCursor(vtkSmartPointer< vtkResliceCursor > cursor)
{
	m_ResliceCursor = cursor;
}

void CvtkView::Render()
{
	m_RenderWindow->Render();
}