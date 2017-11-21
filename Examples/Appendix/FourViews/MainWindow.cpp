/**********************************************************************

  文件名: MainWindow.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "MainWindow.h"

#include <QFileDialog>
#include <QDir>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKWidget.h>
#include <vtkMetaImageReader.h> //读取后缀为*.mhd/*.mha图像文件
#include <vtkImageActor.h>

#include <vtkEventQtSlotConnect.h>
#include <vtkCommand.h>

#include "vtkViewImage2D.h"
#include "vtkViewImage3D.h"

MainWindow::MainWindow()
{
	m_MainWindow = new Ui_MainWindow;
	m_MainWindow->setupUi(this);
	this->setWindowIcon(QIcon(":/icon.ico"));
    initViews();
    setupConnection();
}

MainWindow::~MainWindow()
{
	m_AxialImage->Detach();
	m_SagittalImage->Detach();
	m_CoronalImage->Detach();
	m_3DImage->Detach();
}

void MainWindow::initViews()
{
    m_AxialRenderder     = vtkSmartPointer< vtkRenderer >::New();
    m_SagittalRenderder  = vtkSmartPointer< vtkRenderer >::New();
    m_CoronalRenderder = vtkSmartPointer< vtkRenderer >::New();
    m_3DRenderder         = vtkSmartPointer< vtkRenderer >::New();

    m_AxialRenWin      = vtkSmartPointer< vtkRenderWindow >::New();
    m_SagittalRenWin   = vtkSmartPointer< vtkRenderWindow >::New();
	m_CoronalRenWin  = vtkSmartPointer< vtkRenderWindow >::New();
	m_3DRenWin          = vtkSmartPointer< vtkRenderWindow >::New();

    m_3DInteractor         = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	m_AxialInteractor     = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	m_SagittalInteractor  = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	m_CoronalInteractor = vtkSmartPointer< vtkRenderWindowInteractor >::New();

    m_AxialRenWin->AddRenderer(m_AxialRenderder);
    m_SagittalRenWin->AddRenderer(m_SagittalRenderder);
    m_CoronalRenWin->AddRenderer(m_CoronalRenderder);
    m_3DRenWin->AddRenderer(m_3DRenderder);

    m_AxialInteractor->SetRenderWindow(m_AxialRenWin);
    m_SagittalInteractor->SetRenderWindow(m_SagittalRenWin);
	m_CoronalInteractor->SetRenderWindow(m_CoronalRenWin);
	m_3DInteractor->SetRenderWindow(m_3DRenWin);

    m_MainWindow->m_AxialWidget->SetRenderWindow(m_AxialRenWin);
    m_MainWindow->m_SagittalWidget->SetRenderWindow(m_SagittalRenWin);
    m_MainWindow->m_CoronalWidget->SetRenderWindow(m_CoronalRenWin);
    m_MainWindow->m_3DWidget->SetRenderWindow(m_3DRenWin);

    //Axial视图
    m_AxialImage = vtkSmartPointer< vtkViewImage2D >::New();
    m_AxialImage->SetRenderWindow( m_AxialRenWin ) ;
    m_AxialImage->SetRenderer( m_AxialRenderder ) ;
    m_AxialImage->SetLeftButtonInteractionStyle   (vtkViewImage2D::ZOOM_INTERACTION);
    m_AxialImage->SetMiddleButtonInteractionStyle (vtkViewImage2D::SELECT_INTERACTION);
    m_AxialImage->SetWheelInteractionStyle        (vtkViewImage2D::SELECT_INTERACTION);
    m_AxialImage->SetRightButtonInteractionStyle  (vtkViewImage2D::WINDOW_LEVEL_INTERACTION);
    m_AxialImage->SetBackgroundColor (0.0,0.0,0.0);
    m_AxialImage->SetAboutData("横断面");

    //Sagittal视图
    m_SagittalImage = vtkSmartPointer< vtkViewImage2D >::New();
    m_SagittalImage->SetRenderWindow( m_SagittalRenWin ) ;
    m_SagittalImage->SetRenderer( m_SagittalRenderder ) ;
    m_SagittalImage->SetLeftButtonInteractionStyle   (vtkViewImage2D::ZOOM_INTERACTION);
    m_SagittalImage->SetMiddleButtonInteractionStyle (vtkViewImage2D::SELECT_INTERACTION);
    m_SagittalImage->SetWheelInteractionStyle        (vtkViewImage2D::SELECT_INTERACTION);
    m_SagittalImage->SetRightButtonInteractionStyle  (vtkViewImage2D::WINDOW_LEVEL_INTERACTION);
    m_SagittalImage->SetBackgroundColor (0.0,0.0,0.0);
    m_SagittalImage->SetAboutData("矢状面");

    //Coronal视图
    m_CoronalImage = vtkSmartPointer< vtkViewImage2D >::New();
    m_CoronalImage->SetRenderWindow( m_CoronalRenWin ) ;
    m_CoronalImage->SetRenderer( m_CoronalRenderder ) ;
    m_CoronalImage->SetLeftButtonInteractionStyle   (vtkViewImage2D::ZOOM_INTERACTION);
    m_CoronalImage->SetMiddleButtonInteractionStyle (vtkViewImage2D::SELECT_INTERACTION);
    m_CoronalImage->SetWheelInteractionStyle        (vtkViewImage2D::SELECT_INTERACTION);
    m_CoronalImage->SetRightButtonInteractionStyle  (vtkViewImage2D::WINDOW_LEVEL_INTERACTION);
    m_CoronalImage->SetBackgroundColor (0.0,0.0,0.0);
    m_CoronalImage->SetAboutData("冠状面");

    //3D视图
    m_3DImage = vtkSmartPointer< vtkViewImage3D >::New();
    m_3DImage->SetRenderWindow( m_3DRenWin ) ;
    m_3DImage->SetRenderer( m_3DRenderder ) ;
    m_3DImage->SetBackgroundColor (0.0,0.0,0.0);
    m_3DImage->SetTextColor (0.0,0.0,0.0);
    m_3DImage->SetRenderingModeToPlanar();
    m_3DImage->SetVolumeRayCastFunctionToComposite();
    m_3DImage->BoxWidgetVisibilityOff();
    m_3DImage->SetCubeVisibility(1);
    m_3DImage->SetVRQualityToHigh();
    m_3DImage->ShadeOff();
    m_3DImage->SetAboutDataVisibility(1);
    m_3DImage->SetAxisVisibility(1);
    m_3DImage->GetRenderer()->SetBackground2(0.1,0.1,0.1);
    m_3DImage->GetRenderer()->SetBackground(0.95,0.95,0.95);
    m_3DImage->GetRenderer()->GradientBackgroundOn();
    m_3DImage->SetAboutData ("三维视图");

	m_AxialImage->SetLinkZoom (true);
	m_SagittalImage->SetLinkZoom (true);
	m_CoronalImage->SetLinkZoom (true);
	m_3DImage->SetLinkZoom (true);

	m_AxialImage->SetOrientation (vtkViewImage2D::AXIAL_ID);
	m_CoronalImage->SetOrientation (vtkViewImage2D::CORONAL_ID);
	m_SagittalImage->SetOrientation (vtkViewImage2D::SAGITTAL_ID);

	m_AxialImage->AddChild (m_CoronalImage);
	m_CoronalImage->AddChild (m_SagittalImage);
	m_SagittalImage->AddChild (m_3DImage);
	m_3DImage->AddChild (m_AxialImage);

	m_AxialInteractor->Initialize();
	m_SagittalInteractor->Initialize();
	m_CoronalInteractor->Initialize();
	m_3DInteractor->Initialize();
}

void MainWindow::setupConnection()
{
    //连接信号槽
    connect( m_MainWindow->m_ActionOpen, SIGNAL( triggered() ), this, SLOT( onOpenSlot() ) ); 
}

void MainWindow::onOpenSlot()
{
	QString filter;
	filter = "Meta image file (*.mhd *.mha)";

	QDir dir;
	QString fileName = QFileDialog::getOpenFileName( this, QString(tr("打开图像")), dir.absolutePath() , filter );
	if ( fileName.isEmpty() == true ) return;

	// 支持带中文路径的读取
	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();

	// 用vtkMetaImageReader读取图像
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName(fileName_str);
    reader->Update();

    m_AxialImage->SetImage(reader->GetOutput());
    m_SagittalImage->SetImage(reader->GetOutput());
    m_CoronalImage->SetImage(reader->GetOutput());
    m_3DImage->SetImage(reader->GetOutput());

	m_AxialImage->SyncResetCurrentPoint();
	m_AxialImage->SyncResetWindowLevel();

	m_AxialImage->Render();
	m_SagittalImage->Render();
	m_CoronalImage->Render();
	m_3DImage->Render();

    repaint();
}
