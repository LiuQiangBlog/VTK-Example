/**********************************************************************

  文件名: 6.3_PolyDataLapLasianSmooth.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

//测试文件：../data/fran_cut.vtk
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cout<<argv[0]<<" *.vtk"<<std::endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkPolyDataReader> reader = 
		vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter =
		vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
	smoothFilter->SetInputConnection(reader->GetOutputPort());
	smoothFilter->SetNumberOfIterations(200);
	smoothFilter->Update();

	vtkSmartPointer<vtkPolyDataMapper> inputMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	inputMapper->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkActor> inputActor =
		vtkSmartPointer<vtkActor>::New();
	inputActor->SetMapper(inputMapper);

	vtkSmartPointer<vtkPolyDataMapper> smoothedMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	smoothedMapper->SetInputConnection(smoothFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> smoothedActor =
		vtkSmartPointer<vtkActor>::New();
	smoothedActor->SetMapper(smoothedMapper);

	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> leftRenderer =
		vtkSmartPointer<vtkRenderer>::New();

	leftRenderer->SetViewport(leftViewport);
	leftRenderer->AddActor(inputActor);
	leftRenderer->SetBackground(0.8, 0.8, 0.8);
	leftRenderer->ResetCamera();

	vtkSmartPointer<vtkRenderer> rightRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	rightRenderer->SetViewport(rightViewport);
	rightRenderer->AddActor(smoothedActor);
	rightRenderer->SetBackground(0.8, 0.8, 0.8);
	rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());
	rightRenderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(leftRenderer);
	renderWindow->AddRenderer(rightRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataLapLasianSmooth");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	interactor->Start();

	return EXIT_SUCCESS;
}