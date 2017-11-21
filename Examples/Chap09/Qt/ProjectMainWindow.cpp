/**********************************************************************

  文件名: ProjectMainWindow.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "ProjectMainWindow.h"
#include <QFileDialog>
#include <QDir>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <QVTKWidget.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkCommand.h>

ProjectMainWindow::ProjectMainWindow()
{
	setupUi(this);

	m_pImageViewer  = vtkSmartPointer< vtkImageViewer2 >::New();
	m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();

	// 设置m_QVTKWidget的渲染器
	m_QVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderder);

	//连接打开的信号与相应的槽
	connect( m_OpenAction, SIGNAL( triggered() ), this, SLOT( onOpenSlot() ) ); 

	m_Connections = vtkEventQtSlotConnect::New();
	m_Connections->Connect(m_QVTKWidget->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));
}

ProjectMainWindow::~ProjectMainWindow()
{
}

void ProjectMainWindow::onOpenSlot()
{
	QString filter;
	filter = "JPEG image file (*.jpg *.jpeg)";

	QDir dir;
	QString fileName = QFileDialog::getOpenFileName( this, QString(tr("打开图像")), dir.absolutePath() , filter );
	if ( fileName.isEmpty() == true ) return;

	// 支持带中文路径的读取
	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();

	// 用vtkJPEGReader读取JPG图像
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName_str);

	// 将reader的输出作为m_pImageViewer的输入，并设置m_pImageViewer与渲染器m_pRenderer的关联
	m_pImageViewer->SetInput(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(m_QVTKWidget->GetRenderWindow());
	m_pImageViewer->SetRenderer(m_pRenderder);
	m_pImageViewer->SetupInteractor(m_QVTKWidget->GetRenderWindow()->GetInteractor());
	m_pImageViewer->SetSliceOrientationToXY(); //默认就是这个方向的
	m_pImageViewer->GetImageActor()->InterpolateOff();
	m_pRenderder->ResetCamera();
	m_pRenderder->DrawOn();
	m_QVTKWidget->GetRenderWindow()->Render();
}

void ProjectMainWindow::updateCoords(vtkObject* obj)
{
	// 获取交互器
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);

	// 获取鼠标的当前位置
	int event_pos[2];
	iren->GetEventPosition(event_pos);

	QString str;
	str.sprintf("x=%d : y=%d", event_pos[0], event_pos[1]);
	m_StatusBar->showMessage(str);
}
