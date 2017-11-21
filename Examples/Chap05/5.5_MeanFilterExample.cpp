/**********************************************************************

  文件名: 5.5_MeanFilterExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageConvolve.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkJPEGReader.h>
#include <vtkImageShiftScale.h>

//测试图像：../data/lena-gray.jpg
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

	vtkSmartPointer<vtkImageCast> originalCastFilter =
		vtkSmartPointer<vtkImageCast>::New();
	originalCastFilter->SetInputConnection(reader->GetOutputPort());
	originalCastFilter->SetOutputScalarTypeToFloat();
	originalCastFilter->Update();

	vtkSmartPointer<vtkImageConvolve> convolveFilter =
		vtkSmartPointer<vtkImageConvolve>::New();
	convolveFilter->SetInputConnection(originalCastFilter->GetOutputPort());

	double kernel[25] = {0.04,0.04,0.04,0.04,0.04,
		0.04,0.04,0.04,0.04,0.04,
		0.04,0.04,0.04,0.04,0.04,
		0.04,0.04,0.04,0.04,0.04,
		0.04,0.04,0.04,0.04,0.04 };
	convolveFilter->SetKernel5x5(kernel);
	convolveFilter->Update();

	vtkSmartPointer<vtkImageCast> convCastFilter = 
		vtkSmartPointer<vtkImageCast>::New();
	convCastFilter->SetInput(convolveFilter->GetOutput());
	convCastFilter->SetOutputScalarTypeToUnsignedChar();
	convCastFilter->Update();

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> convolvedActor =
		vtkSmartPointer<vtkImageActor>::New();
	convolvedActor->SetInput(convCastFilter->GetOutput());

	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(leftViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->SetBackground(1.0, 1.0, 1.0);
	originalRenderer->ResetCamera();

	vtkSmartPointer<vtkRenderer> convolvedRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	convolvedRenderer->SetViewport(rightViewport);
	convolvedRenderer->AddActor(convolvedActor);
	convolvedRenderer->SetBackground(1.0, 1.0, 1.0);
	convolvedRenderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();;
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(convolvedRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("MeanFilterExample");

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