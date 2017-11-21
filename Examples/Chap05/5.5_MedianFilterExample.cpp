/**********************************************************************

  文件名: 5.5_MedianFilterExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageHybridMedian2D.h>
#include <vtkImageThreshold.h>

//测试图像：../data/lena-noise.jpg
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.jpg)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkJPEGReader> reader =
		vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	vtkSmartPointer<vtkImageHybridMedian2D> hybridMedian =
		vtkSmartPointer<vtkImageHybridMedian2D>::New();
	hybridMedian->SetInput(reader->GetOutput());
	hybridMedian->Update();

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> hybridMedianActor =
		vtkSmartPointer<vtkImageActor>::New();
	hybridMedianActor->SetInput(hybridMedian->GetOutput());

	double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double hybridMedianViewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> hybridMedianRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	hybridMedianRenderer->SetViewport(hybridMedianViewport);
	hybridMedianRenderer->AddActor(hybridMedianActor);
	hybridMedianRenderer->ResetCamera();
	hybridMedianRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(hybridMedianRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("MedianFilterExample");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
