/**********************************************************************

  文件名: 5.3_ImageExtractComponentsExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
 
//测试图像：../data/lena.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName (argv[1]);
 
	vtkSmartPointer<vtkImageExtractComponents> extractRedFilter =
		vtkSmartPointer<vtkImageExtractComponents>::New();
	extractRedFilter->SetInputConnection(reader->GetOutputPort());
	extractRedFilter->SetComponents(0);
	extractRedFilter->Update();
 
	vtkSmartPointer<vtkImageExtractComponents> extractGreenFilter =
		vtkSmartPointer<vtkImageExtractComponents>::New();
	extractGreenFilter->SetInputConnection(reader->GetOutputPort());
	extractGreenFilter->SetComponents(1);
	extractGreenFilter->Update();
 
	vtkSmartPointer<vtkImageExtractComponents> extractBlueFilter =
		vtkSmartPointer<vtkImageExtractComponents>::New();
	extractBlueFilter->SetInputConnection(reader->GetOutputPort());
	extractBlueFilter->SetComponents(2);
	extractBlueFilter->Update();
 
	// Create actors
	vtkSmartPointer<vtkImageActor> inputActor =
		vtkSmartPointer<vtkImageActor>::New();
	inputActor->SetInput(reader->GetOutput());
 
	vtkSmartPointer<vtkImageActor> redActor =
		vtkSmartPointer<vtkImageActor>::New();
	redActor->SetInput(extractRedFilter->GetOutput());
 
	vtkSmartPointer<vtkImageActor> greenActor =
		vtkSmartPointer<vtkImageActor>::New();
	greenActor->SetInput(extractGreenFilter->GetOutput());
 
	vtkSmartPointer<vtkImageActor> blueActor =
		vtkSmartPointer<vtkImageActor>::New();
	blueActor->SetInput(extractBlueFilter->GetOutput());

	double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
	double redViewport[4] = {0.25, 0.0, 0.5, 1.0};
	double greenViewport[4] = {0.5, 0.0, 0.75, 1.0};
	double blueViewport[4] = {0.75, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> inputRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	inputRenderer->SetViewport(inputViewport);
	inputRenderer->AddActor(inputActor);
	inputRenderer->ResetCamera();
	inputRenderer->SetBackground(1.0, 1.0, 1.0);
 
	vtkSmartPointer<vtkRenderer> redRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	redRenderer->SetViewport(redViewport);
	redRenderer->AddActor(redActor);
	redRenderer->ResetCamera();
	redRenderer->SetBackground(1.0, 1.0, 1.0);
 
	vtkSmartPointer<vtkRenderer> greenRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	greenRenderer->SetViewport(greenViewport);
	greenRenderer->AddActor(greenActor);
	greenRenderer->ResetCamera();
	greenRenderer->SetBackground(1.0, 1.0, 1.0);
 
	vtkSmartPointer<vtkRenderer> blueRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	blueRenderer->SetViewport(blueViewport);
	blueRenderer->AddActor(blueActor);
	blueRenderer->ResetCamera();
	blueRenderer->SetBackground(1.0, 1.0, 1.0);
 
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(inputRenderer);
	renderWindow->AddRenderer(redRenderer);
	renderWindow->AddRenderer(greenRenderer);
	renderWindow->AddRenderer(blueRenderer);

	renderWindow->SetSize(1200, 300);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageExtractComponentsExample");
 
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