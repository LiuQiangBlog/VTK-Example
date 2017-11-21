/**********************************************************************

  文件名: 5.4_CannyExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageShiftScale.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkImageCast.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageGradient.h>
#include <vtkImageMagnitude.h>
#include <vtkImageNonMaximumSuppression.h>
#include <vtkImageConstantPad.h>
#include <vtkImageToStructuredPoints.h>
#include <vtkLinkEdgels.h>
#include <vtkThreshold.h>
#include <vtkGeometryFilter.h>
#include <vtkSubPixelPositionEdgels.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>

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

	vtkSmartPointer<vtkImageCast> ic =
		vtkSmartPointer<vtkImageCast>::New();
	ic->SetOutputScalarTypeToFloat();
	ic->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkImageGaussianSmooth> gs =
		vtkSmartPointer<vtkImageGaussianSmooth>::New();
	gs->SetInputConnection(ic->GetOutputPort());
	gs->SetDimensionality(2);
	gs->SetRadiusFactors(1, 1, 0);

	vtkSmartPointer<vtkImageGradient> imgGradient =
		vtkSmartPointer<vtkImageGradient>::New();
	imgGradient->SetInputConnection(gs->GetOutputPort());
	imgGradient->SetDimensionality(2);

	vtkSmartPointer<vtkImageMagnitude> imgMagnitude =
		vtkSmartPointer<vtkImageMagnitude>::New();
	imgMagnitude->SetInputConnection(imgGradient->GetOutputPort());

	vtkSmartPointer<vtkImageNonMaximumSuppression> nonMax =
		vtkSmartPointer<vtkImageNonMaximumSuppression>::New();
	nonMax->SetMagnitudeInput(imgMagnitude->GetOutput());
	nonMax->SetVectorInput(imgGradient->GetOutput());
	nonMax->SetDimensionality(2);

	vtkSmartPointer<vtkImageConstantPad> pad =
		vtkSmartPointer<vtkImageConstantPad>::New();
	pad->SetInputConnection(imgGradient->GetOutputPort());
	pad->SetOutputNumberOfScalarComponents(3);
	pad->SetConstant(0);

	vtkSmartPointer<vtkImageToStructuredPoints> i2sp1 =
		vtkSmartPointer<vtkImageToStructuredPoints>::New();
	i2sp1->SetInputConnection(nonMax->GetOutputPort());
	i2sp1->SetVectorInput(pad->GetOutput());

	vtkSmartPointer<vtkLinkEdgels> imgLink =
		vtkSmartPointer<vtkLinkEdgels>::New();
	imgLink->SetInput(i2sp1->GetOutput());
	imgLink->SetGradientThreshold(2);

	vtkSmartPointer<vtkThreshold> thresholdEdgels =
		vtkSmartPointer<vtkThreshold>::New();
	thresholdEdgels->SetInputConnection(imgLink->GetOutputPort());
	thresholdEdgels->ThresholdByUpper(10);
	thresholdEdgels->AllScalarsOff();

	vtkSmartPointer<vtkGeometryFilter> gf =
		vtkSmartPointer<vtkGeometryFilter>::New();
	gf->SetInputConnection(thresholdEdgels->GetOutputPort());

	vtkSmartPointer<vtkImageToStructuredPoints> i2sp =
		vtkSmartPointer<vtkImageToStructuredPoints>::New();
	i2sp->SetInputConnection(imgMagnitude->GetOutputPort());
	i2sp->SetVectorInput(pad->GetOutput());

	vtkSmartPointer<vtkSubPixelPositionEdgels> spe =
		vtkSmartPointer<vtkSubPixelPositionEdgels>::New();
	spe->SetInputConnection(gf->GetOutputPort());
	spe->SetGradMaps(i2sp->GetStructuredPointsOutput());

	vtkSmartPointer<vtkStripper> strip =
		vtkSmartPointer<vtkStripper>::New();
	strip->SetInputConnection(spe->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> dsm =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	dsm->SetInputConnection(strip->GetOutputPort());
	dsm->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> planeActor =
		vtkSmartPointer<vtkActor>::New();
	planeActor->SetMapper(dsm);
	planeActor->GetProperty()->SetAmbient(1.0);
	planeActor->GetProperty()->SetDiffuse(0.0);
	planeActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInput(reader->GetOutput());

	double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double gradviewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> gradRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	gradRenderer->SetViewport(gradviewport);
	gradRenderer->AddActor(planeActor);
	gradRenderer->ResetCamera();
	gradRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(900, 300);
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(gradRenderer);
	renderWindow->Render();
	renderWindow->SetWindowName("CannyExample");

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