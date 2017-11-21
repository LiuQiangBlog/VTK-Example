/**********************************************************************

  文件名: 6.7_PolyDataMarchingCubes.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkContourFilter.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkProperty.h>

//测试：../data/HeadMRVolume.mhd 200
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout<<argv[0]<<" *.mhd isoValue"<<std::endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkMetaImageReader> reader =
		vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	double isoValue = atof(argv[2]);

	vtkSmartPointer<vtkMarchingCubes> surface = 
		vtkSmartPointer<vtkMarchingCubes>::New();
	surface->SetInput(reader->GetOutput());
	surface->ComputeNormalsOn();
	surface->SetValue(0, isoValue);
	//surface->GenerateValues(5, 150,200);

	/*vtkSmartPointer<vtkContourFilter> surface = 
	vtkSmartPointer<vtkContourFilter>::New();
	surface->SetInput(reader->GetOutput());
	surface->ComputeNormalsOn();
	surface->SetValue(0, isoValue);*/

	vtkSmartPointer<vtkPolyDataMapper> surfMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	surfMapper->SetInputConnection(surface->GetOutputPort());
	surfMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> surfActor = 
		vtkSmartPointer<vtkActor>::New();
	surfActor->SetMapper(surfMapper);
	surfActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(surfActor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataMarchingCubes");
	renderWindow->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	interactor->Start();

	return EXIT_SUCCESS;
}