/**********************************************************************

  文件名: ProjectMainWindow.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef Project_MainWindow_H
#define Project_MainWindow_H

#include <QMainWindow>
#include "ui_ProjectMainWindow.h"
#include <vtkSmartPointer.h>

class vtkImageViewer2;
class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

class ProjectMainWindow : public QMainWindow, public Ui::ProjectMainWindow
{
	Q_OBJECT

public:
	ProjectMainWindow();
	~ProjectMainWindow();

private slots:
	//响应打开图像文件的槽函数
	void onOpenSlot();

	//响应鼠标移动的消息，实时输出鼠标的当前位置
	void updateCoords(vtkObject* obj);

private:
	vtkSmartPointer< vtkImageViewer2 >           m_pImageViewer;
	vtkSmartPointer< vtkRenderer >                   m_pRenderder;

	vtkEventQtSlotConnect* m_Connections;
};

#endif
