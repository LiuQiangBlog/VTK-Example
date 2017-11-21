/**********************************************************************

  文件名: VRAppView.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// VRAppView.h : interface of the CVRAppView class
//


#pragma once

#include <vtkMetaImageReader.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkAxesActor.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>
#include <vtkVolume16Reader.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>

class CVRAppView : public CView
{
protected: // create from serialization only
	CVRAppView();
	DECLARE_DYNCREATE(CVRAppView)

// Attributes
public:
	CVRAppDoc* GetDocument() const;

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
	virtual ~CVRAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void SetInput();
	void OnUpdateColor();
	void OnUpdateOpacity();

	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFun;
	vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper;
	vtkSmartPointer<vtkVolume> volume;
	vtkSmartPointer<vtkRenderer> ren;
	vtkSmartPointer<vtkRenderWindow> renWin;
	vtkSmartPointer<vtkRenderWindowInteractor> iren;

	
};

#ifndef _DEBUG  // debug version in VRAppView.cpp
inline CVRAppDoc* CVRAppView::GetDocument() const
   { return reinterpret_cast<CVRAppDoc*>(m_pDocument); }
#endif

