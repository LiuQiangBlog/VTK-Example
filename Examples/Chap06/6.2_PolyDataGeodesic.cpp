/**********************************************************************

  文件名: 6.2_PolyDataGeodesic.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDijkstraGraphGeodesicPath.h>

int main(int , char *[])
{ 
	vtkSmartPointer<vtkSphereSource> sphereSource = 
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();

	vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra = 
		vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
	dijkstra->SetInput(sphereSource->GetOutput());
	dijkstra->SetStartVertex(0);
	dijkstra->SetEndVertex(10);
	dijkstra->Update();

	vtkSmartPointer<vtkPolyDataMapper> pathMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	pathMapper->SetInput(dijkstra->GetOutput());

	vtkSmartPointer<vtkActor> pathActor = 
		vtkSmartPointer<vtkActor>::New();
	pathActor->SetMapper(pathMapper);
	pathActor->GetProperty()->SetColor(1,0,0); 
	pathActor->GetProperty()->SetLineWidth(4);

	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInput(sphereSource->GetOutput());

	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->AddActor(pathActor);
	renderer->SetBackground(1.0, 1.0, 1.0); 

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize( 640, 480 );
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataGeodesic");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}