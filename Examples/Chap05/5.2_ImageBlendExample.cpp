/**********************************************************************

  文件名: 5.2_ImageBlendExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageBlend.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

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
	reader->SetFileName ( argv[1] );
	reader->Update();

	vtkSmartPointer<vtkImageCanvasSource2D> imageSource = 
		vtkSmartPointer<vtkImageCanvasSource2D>::New();
	imageSource->SetNumberOfScalarComponents(1);
	imageSource->SetScalarTypeToUnsignedChar();
	imageSource->SetExtent(0, 512, 0, 512, 0, 0);
	imageSource->SetDrawColor(0.0);
	imageSource->FillBox(0, 512, 0, 512);
	imageSource->SetDrawColor(255.0);
	imageSource->FillBox(100,400,100,400);
	imageSource->Update();

	vtkSmartPointer<vtkImageBlend> imageBlend = 
		vtkSmartPointer<vtkImageBlend>::New();
	imageBlend->SetInput(0, reader->GetOutput());
	imageBlend->SetInput(1, imageSource->GetOutput());
	imageBlend->SetOpacity(0, 0.4);
	imageBlend->SetOpacity(1, 0.6);
	imageBlend->Update();

	// Create actors
	vtkSmartPointer<vtkImageActor> originalActor1 =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor1->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> originalActor2 =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor2->SetInput(imageSource->GetOutput());

	vtkSmartPointer<vtkImageActor> blendActor =
		vtkSmartPointer<vtkImageActor>::New();
	blendActor->SetInput(imageBlend->GetOutput());

	// Define viewport ranges
	// (xmin, ymin, xmax, ymax)
	double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
	double midViewport[4] = {0.33, 0.0, 0.66, 1.0};
	double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

	// Setup renderers
	vtkSmartPointer<vtkRenderer> originalRenderer1 =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer1->SetViewport(leftViewport);
	originalRenderer1->AddActor(originalActor1);
	originalRenderer1->ResetCamera();
	originalRenderer1->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> originalRenderer2 =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer2->SetViewport(midViewport);
	originalRenderer2->AddActor(originalActor2);
	originalRenderer2->ResetCamera();
	originalRenderer2->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> blendRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	blendRenderer->SetViewport(rightViewport);
	blendRenderer->AddActor(blendActor);
	blendRenderer->ResetCamera();
	blendRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer1);
	renderWindow->AddRenderer(originalRenderer2);
	renderWindow->AddRenderer(blendRenderer);
	renderWindow->SetSize( 640, 320 );
	renderWindow->Render();
	renderWindow->SetWindowName("ImageBlendExample");

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