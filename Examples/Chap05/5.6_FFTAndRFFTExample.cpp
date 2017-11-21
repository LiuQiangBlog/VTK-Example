/**********************************************************************

  文件名: 5.6_FFTAndRFFTExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageFFT.h>
#include <vtkImageRFFT.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkJPEGReader.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageFourierCenter.h>
#include <vtkImageMagnitude.h>
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
	reader->SetFileName (argv[1]);
	reader->Update();

	vtkSmartPointer<vtkImageFFT> fftFilter = 
		vtkSmartPointer<vtkImageFFT>::New();
	fftFilter->SetInputConnection(reader->GetOutputPort());
	fftFilter->SetDimensionality(2);
	fftFilter->Update();

	vtkSmartPointer<vtkImageExtractComponents> fftExtractReal =
		vtkSmartPointer<vtkImageExtractComponents>::New();
	fftExtractReal->SetInputConnection(fftFilter->GetOutputPort());
	fftExtractReal->SetComponents(0);

	double range[2];
	fftExtractReal->GetOutput()->GetScalarRange(range);

	vtkSmartPointer<vtkImageShiftScale> ShiftScale =
		vtkSmartPointer<vtkImageShiftScale>::New();
	ShiftScale->SetOutputScalarTypeToUnsignedChar();
	ShiftScale->SetScale( 255.0 / (range[1]-range[0]) );
	ShiftScale->SetShift(-range[0]);
	ShiftScale->SetInputConnection(fftExtractReal->GetOutputPort());
	ShiftScale->Update();

	vtkSmartPointer<vtkImageRFFT> rfftFilter =
		vtkSmartPointer<vtkImageRFFT>::New();
	rfftFilter->SetInputConnection(fftFilter->GetOutputPort());
	rfftFilter->SetDimensionality(2);
	rfftFilter->Update();

	vtkSmartPointer<vtkImageExtractComponents> ifftExtractReal =
		vtkSmartPointer<vtkImageExtractComponents>::New();
	ifftExtractReal->SetInputConnection(rfftFilter->GetOutputPort());
	ifftExtractReal->SetComponents(0);

	vtkSmartPointer<vtkImageCast> rfftCastFilter =
		vtkSmartPointer<vtkImageCast>::New();
	rfftCastFilter->SetInputConnection(ifftExtractReal->GetOutputPort());
	rfftCastFilter->SetOutputScalarTypeToUnsignedChar();
	rfftCastFilter->Update();

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> fftActor =
		vtkSmartPointer<vtkImageActor>::New();
	fftActor->SetInput(ShiftScale->GetOutput());

	vtkSmartPointer<vtkImageActor> rfftActor =
		vtkSmartPointer<vtkImageActor>::New();
	rfftActor->SetInput(rfftCastFilter->GetOutput());

	double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
	double fftViewport[4] = {0.33, 0.0, 0.66, 1.0};
	double rfftViewport[4] = {0.66, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> fftRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	fftRenderer->SetViewport(fftViewport);
	fftRenderer->AddActor(fftActor);
	fftRenderer->ResetCamera();
	fftRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> rfftRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	rfftRenderer->SetViewport(rfftViewport);
	rfftRenderer->AddActor(rfftActor);
	rfftRenderer->ResetCamera();
	rfftRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(fftRenderer);
	renderWindow->AddRenderer(rfftRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("FFTAndRFFTExample");

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
