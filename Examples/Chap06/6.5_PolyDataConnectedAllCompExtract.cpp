/**********************************************************************

  文件名: 6.5_PolyDataConnectedAllCompExtract.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkConnectivityFilter.h>

int main(int, char *[])
{
	vtkSmartPointer<vtkSphereSource> sphereSource = 
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(10);
	sphereSource->SetThetaResolution(10);
	sphereSource->SetPhiResolution(10);
	sphereSource->Update();

	vtkSmartPointer<vtkConeSource> coneSource = 
		vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetRadius(5);
	coneSource->SetHeight(10);
	coneSource->SetCenter(25,0,0);
	coneSource->Update();

	vtkSmartPointer<vtkAppendPolyData> appendFilter = 
		vtkSmartPointer<vtkAppendPolyData>::New();
	appendFilter->AddInput(sphereSource->GetOutput());
	appendFilter->AddInput(coneSource->GetOutput());
	appendFilter->Update();

	vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter = 
		vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	connectivityFilter->SetInput(appendFilter->GetOutput());
	connectivityFilter->SetExtractionModeToAllRegions();
	connectivityFilter->Update();

	int regionNum = connectivityFilter->GetNumberOfExtractedRegions();
	for (int i=0; i<regionNum; i++)
	{
		vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter2 = 
			vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
		connectivityFilter2->SetInput(appendFilter->GetOutput());
		connectivityFilter2->InitializeSpecifiedRegionList();
		connectivityFilter2->SetExtractionModeToSpecifiedRegions();
		connectivityFilter2->AddSpecifiedRegion(i);
		connectivityFilter2->Update();

		char str[256];
		itoa(i, str, 10);
		strcat(str, ".vtk");

		vtkSmartPointer<vtkPolyDataWriter> writer = 
			vtkSmartPointer<vtkPolyDataWriter>::New();
		writer->SetFileName(str);
		writer->SetInput(connectivityFilter2->GetOutput());
		writer->Update();
	}

	vtkSmartPointer<vtkPolyDataMapper> originalMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	originalMapper->SetInput(appendFilter->GetOutput());

	vtkSmartPointer<vtkActor> originalActor = 
		vtkSmartPointer<vtkActor>::New();
	originalActor->SetMapper(originalMapper);

	vtkSmartPointer<vtkPolyDataMapper> extractedMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	extractedMapper->SetInput(connectivityFilter->GetOutput());

	vtkSmartPointer<vtkActor> extractedActor = 
		vtkSmartPointer<vtkActor>::New();
	extractedActor->SetMapper(extractedMapper);

	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> leftRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	leftRenderer->SetViewport(leftViewport);
	leftRenderer->AddActor(originalActor);
	leftRenderer->SetBackground(0.2,0.1,0.5);
	leftRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> rightRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	rightRenderer->SetViewport(rightViewport);
	rightRenderer->AddActor(extractedActor);
	rightRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(leftRenderer);
	renderWindow->AddRenderer(rightRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("6.5_PolyDataConnectedAllCompExtract");

	leftRenderer->ResetCamera();
	rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}