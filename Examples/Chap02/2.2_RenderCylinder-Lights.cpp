/**********************************************************************

  文件名: 2.2_RenderCylinder-Lights.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

int main()
{
	vtkSmartPointer<vtkCylinderSource> cylinder = 
		vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight( 3.0 );
	cylinder->SetRadius( 1.0 );
	cylinder->SetResolution( 10 ); 

	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection( cylinder->GetOutputPort() ); 

	vtkSmartPointer<vtkActor> cylinderActor = 
		vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper( cylinderMapper );

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor( cylinderActor );
	renderer->SetBackground( 1.0, 1.0, 1.0 );

	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer( renderer );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("RenderCylinder-Lights");

	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);

	vtkSmartPointer<vtkLight> myLight = 
		vtkSmartPointer<vtkLight>::New();
	myLight->SetColor(0,1,0);
	myLight->SetPosition(0,0,1);
	myLight->SetFocalPoint(
		renderer->GetActiveCamera()->GetFocalPoint());
	renderer->AddLight(myLight);

	vtkSmartPointer<vtkLight> myLight2 =
		vtkSmartPointer<vtkLight>::New();
	myLight2->SetColor(0,0,1);
	myLight2->SetPosition(0,0,-1);
	myLight2->SetFocalPoint(
		renderer->GetActiveCamera()->GetFocalPoint());
	renderer->AddLight(myLight2);

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}