/**********************************************************************

  文件名: 5.3_ImageAccumulateExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkActor.h>
#include <vtkBarChartActor.h>
#include <vtkFieldData.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkIntArray.h>
#include <vtkJPEGReader.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>

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
	reader->SetFileName ( "..\\data\\lena-gray.jpg" );
	reader->Update();

	int bins   = 16;
	int comps  = 1;

	vtkSmartPointer<vtkImageAccumulate> histogram =
		vtkSmartPointer<vtkImageAccumulate>::New();
	histogram->SetInput(reader->GetOutput());
	histogram->SetComponentExtent(0, bins-1, 0, 0, 0, 0);
	histogram->SetComponentOrigin(0, 0, 0);
	histogram->SetComponentSpacing(256.0/bins, 0, 0);
	histogram->Update();

	int* output = static_cast<int*>(histogram->GetOutput()->GetScalarPointer());

	vtkSmartPointer<vtkIntArray> frequencies = 
		vtkSmartPointer<vtkIntArray>::New();
	frequencies->SetNumberOfComponents(1);

	for(int j = 0; j < bins; ++j)
	{
		for(int i=0; i<comps; i++)
		{
			frequencies->InsertNextTuple1(*output++);
		}
	}

	vtkSmartPointer<vtkDataObject> dataObject = 
		vtkSmartPointer<vtkDataObject>::New();
	dataObject->GetFieldData()->AddArray( frequencies );

	vtkSmartPointer<vtkBarChartActor> barChart = 
		vtkSmartPointer<vtkBarChartActor>::New();
	barChart->SetInput(dataObject);
	barChart->SetTitle("Histogram");
	barChart->GetPositionCoordinate()->SetValue(0.05,0.05,0.0);
	barChart->GetPosition2Coordinate()->SetValue(0.95,0.95,0.0);
	barChart->GetProperty()->SetColor(0,0,0);
	barChart->GetTitleTextProperty()->SetColor(0,0,0);
	barChart->GetLabelTextProperty()->SetColor(0,0,0);
	barChart->GetLegendActor()->SetNumberOfEntries(dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
	barChart->LegendVisibilityOff();
	barChart->LabelVisibilityOff();

	double colors[3][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 } };

	int count = 0;
	for( int i = 0; i < bins; ++i )
	{
		for( int j = 0; j < comps; ++j )
		{
			barChart->SetBarColor( count++, colors[j] );
		}
	}

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(barChart);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageAccumulateExample");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}
