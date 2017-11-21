/**********************************************************************

  文件名: 6.2_PolyDataCurvature.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkCurvatures.h>
#include <vtkPolyDataReader.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkColorSeries.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkScalarBarActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <iostream>
using namespace std;

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

	vtkSmartPointer<vtkCurvatures> curvaturesFilter = 
		vtkSmartPointer<vtkCurvatures>::New();
	curvaturesFilter->SetInputConnection(reader->GetOutputPort());
	//curvaturesFilter->SetCurvatureTypeToMinimum();
	curvaturesFilter->SetCurvatureTypeToMaximum();
	//curvaturesFilter->SetCurvatureTypeToGaussian();
	//curvaturesFilter->SetCurvatureTypeToMean();
	curvaturesFilter->Update();

	double scalarRange[2];
	curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);

	vtkSmartPointer<vtkLookupTable> lut = 
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetHueRange(0.0,0.6);
	lut->SetAlphaRange(1.0,1.0);
	lut->SetValueRange(1.0,1.0);
	lut->SetSaturationRange(1.0,1.0);
	lut->SetNumberOfTableValues(256);
	lut->SetRange(scalarRange);
	lut->Build();

	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInput(curvaturesFilter->GetOutput());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(scalarRange);

	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkScalarBarActor> scalarBar = 
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(mapper->GetLookupTable());
	scalarBar->SetTitle(
		curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
	scalarBar->SetNumberOfLabels(5);

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->AddActor2D(scalarBar);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataCurvature");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}