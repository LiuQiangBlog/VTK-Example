/**********************************************************************

  文件名: 2.3_Viewport.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main()
{
	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();

	vtkSmartPointer<vtkPolyDataMapper> coneMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInput(cone->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInput(cube->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInput(cylinder->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInput(sphere->GetOutput());

	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);


	vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
	renderer1->AddActor(coneActor);
	renderer1->SetBackground(1.0,0.0,0.0);
	renderer1->SetViewport(0.0,0.0,0.5,0.5);
	vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
	renderer2->AddActor(cubeActor);
	renderer2->SetBackground(0.0,1.0,0.0);
	renderer2->SetViewport(0.5,0.0,1.0,0.5);
	vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
	renderer3->AddActor(cylinderActor);
	renderer3->SetBackground(0.0,0.0,1.0);
	renderer3->SetViewport(0.0,0.5,0.5,1.0);
	vtkSmartPointer<vtkRenderer> renderer4 = vtkSmartPointer<vtkRenderer>::New();
	renderer4->AddActor(sphereActor);
	renderer4->SetBackground(1.0,1.0,0.0);
	renderer4->SetViewport(0.5,0.5,1.0,1.0);

	vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer1);
	renWin->AddRenderer(renderer2);
	renWin->AddRenderer(renderer3);
	renWin->AddRenderer(renderer4);
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("Viewport");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renWin);

	renWin->Render();
	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}