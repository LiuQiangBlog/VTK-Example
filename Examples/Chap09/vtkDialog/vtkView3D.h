/**********************************************************************

  文件名: vtkView3D.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#pragma once

#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
// CvtkView3D

class CvtkView3D : public CStatic
{
	DECLARE_DYNAMIC(CvtkView3D)

public:
	CvtkView3D();
	virtual ~CvtkView3D();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();

public:
	afx_msg void OnPaint();
	void Render();

	vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() {return m_RenderWindow->GetInteractor();}
	vtkSmartPointer<vtkRenderer> GetRenderer() {return m_Renderer;}


public:
	vtkSmartPointer<vtkRenderer>     m_Renderer;
	vtkSmartPointer<vtkRenderWindow> m_RenderWindow;
};


