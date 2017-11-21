/**********************************************************************

  文件名: 5.3_ImageLogicExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageLogic.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
	vtkSmartPointer<vtkImageCanvasSource2D> imageSource1 =
		vtkSmartPointer<vtkImageCanvasSource2D>::New();
	imageSource1->SetScalarTypeToUnsignedChar();
	imageSource1->SetNumberOfScalarComponents(1);
	imageSource1->SetExtent(0, 100, 0, 100, 0, 0);
	imageSource1->SetDrawColor(0.0);
	imageSource1->FillBox(0,100,0,100);
	imageSource1->SetDrawColor(255);
	imageSource1->FillBox(20,60,20,60);
	imageSource1->Update();

	vtkSmartPointer<vtkImageCanvasSource2D> imageSource2 = 
		vtkSmartPointer<vtkImageCanvasSource2D>::New();
	imageSource2->SetNumberOfScalarComponents(1);
	imageSource2->SetScalarTypeToUnsignedChar();
	imageSource2->SetExtent(0, 100, 0, 100, 0, 0);
	imageSource2->SetDrawColor(0.0);
	imageSource2->FillBox(0,100,0,100);
	imageSource2->SetDrawColor(255.0);
	imageSource2->FillBox(40,80,40,80);
	imageSource2->Update();

	vtkSmartPointer<vtkImageLogic> imageLogic = 
		vtkSmartPointer<vtkImageLogic>::New();
	imageLogic->SetInput1(imageSource1->GetOutput());
	imageLogic->SetInput2(imageSource2->GetOutput());
	imageLogic->SetOperationToXor();
	imageLogic->SetOutputTrueValue(128);
	imageLogic->Update();

	vtkSmartPointer<vtkImageActor> originalActor1 =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor1->SetInput(imageSource1->GetOutput());

	vtkSmartPointer<vtkImageActor> originalActor2 =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor2->SetInput(imageSource2->GetOutput());

	vtkSmartPointer<vtkImageActor> logicActor =
		vtkSmartPointer<vtkImageActor>::New();
	logicActor->SetInput(imageLogic->GetOutput());

	double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
	double midViewport[4] = {0.33, 0.0, 0.66, 1.0};
	double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

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
	originalRenderer2->SetBackground(0.8, 0.8, 0.8);

	vtkSmartPointer<vtkRenderer> logicRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	logicRenderer->SetViewport(rightViewport);
	logicRenderer->AddActor(logicActor);
	logicRenderer->ResetCamera();
	logicRenderer->SetBackground(0.6, 0.6, 0.6);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer1);
	renderWindow->AddRenderer(originalRenderer2);
	renderWindow->AddRenderer(logicRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageLogicExample");

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