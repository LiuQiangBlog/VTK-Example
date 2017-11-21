/**********************************************************************

  文件名: 8.3_MeasurementWidget.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkAngleWidget.h>
#include <vtkAngleRepresentation2D.h>
#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>
#include <vtkLeaderActor2D.h>
#include <vtkProperty2D.h>
#include <vtkCommand.h>

class vtkBiDimensionalCallback : public vtkCommand
{
public:
	static vtkBiDimensionalCallback *New()
	{
		return new vtkBiDimensionalCallback;
	}

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBiDimensionalWidget *biDimensionalWidget = 
			reinterpret_cast<vtkBiDimensionalWidget*>(caller);

		vtkBiDimensionalRepresentation2D* representation = 
			static_cast<vtkBiDimensionalRepresentation2D*>(biDimensionalWidget->GetRepresentation());

		double p1[3];
		representation->GetPoint1DisplayPosition(p1);
		double p2[3];
		representation->GetPoint1DisplayPosition(p2);
		double p3[3];
		representation->GetPoint1DisplayPosition(p3);
		double p4[3];
		representation->GetPoint1DisplayPosition(p4);

		//显示其中一个点的屏幕坐标(px)
		std::cout << "P1: " << p1[0] << " " << p1[1] << " " << p1[2] << std::endl;
	}
	vtkBiDimensionalCallback(){}
};

//测试：../data/lena.bmp 0/1/2
int main(int argc, char* argv[])
{
	if ( argc < 3 )
	{
		std::cout <<argv[0]<<" BMP-File(*bmp) WidgetType(0,1,2)" <<std::endl;

		return EXIT_FAILURE;
	}

	std::string fileName( argv[1] );
	int widgetType = atoi( argv[2] );

	vtkSmartPointer<vtkBMPReader> reader = 
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(fileName.c_str());
	reader->Update();

	vtkSmartPointer<vtkImageActor> imageActor = 
		vtkSmartPointer<vtkImageActor>::New();
	imageActor->SetInput( reader->GetOutput() );

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderer->AddActor(imageActor);
	renderWindow->Render();
	renderWindow->SetWindowName("MeasurementWidget");
	renderWindow->SetSize(400, 400);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleImage> style = 
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor->SetInteractorStyle(style);

	//////////////////////////////////////////////////////////////////////////
	//vtkDistanceWidget
	if ( widgetType == 0 )
	{
		vtkSmartPointer<vtkDistanceWidget> distanceWidget =
			vtkSmartPointer<vtkDistanceWidget>::New();
		distanceWidget->SetInteractor(renderWindowInteractor);
		distanceWidget->CreateDefaultRepresentation();
		static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())
			->SetLabelFormat("%-#6.3g px");

		renderWindowInteractor->Initialize();
		renderWindow->Render();
		distanceWidget->On();

		renderWindowInteractor->Start();
	}

	//////////////////////////////////////////////////////////////////////////
	//vtkAngleWidget
	if ( widgetType == 1 )
	{
		vtkSmartPointer< vtkAngleWidget > angleWidget =
			vtkSmartPointer< vtkAngleWidget >::New();
		angleWidget->SetInteractor(renderWindowInteractor);

		vtkSmartPointer< vtkAngleRepresentation2D > angleRep = 
			vtkSmartPointer< vtkAngleRepresentation2D >::New();
		angleRep->GetRay1()->GetProperty()->SetColor(1.0, 0.0, 0.0);
		angleRep->GetRay2()->GetProperty()->SetColor(0.0, 1.0, 0.0);
		angleRep->GetArc()->GetProperty()->SetColor(0.0, 0.0, 1.0);

		angleWidget->SetRepresentation(angleRep);

		renderWindowInteractor->Initialize();
		renderWindow->Render();
		angleWidget->On();

		renderWindowInteractor->Start();
	}

	//////////////////////////////////////////////////////////////////////////
	//vtkBiDimensionalWidget
	if ( widgetType == 2 )
	{
		vtkSmartPointer<vtkBiDimensionalWidget> biDimensionalWidget =
			vtkSmartPointer<vtkBiDimensionalWidget>::New();
		biDimensionalWidget->SetInteractor(renderWindowInteractor);
		biDimensionalWidget->CreateDefaultRepresentation();

		vtkSmartPointer<vtkBiDimensionalCallback> biDimensionalCallback = 
			vtkSmartPointer<vtkBiDimensionalCallback>::New();

		biDimensionalWidget->AddObserver(vtkCommand::InteractionEvent,biDimensionalCallback);

		renderWindowInteractor->Initialize();
		renderWindow->Render();
		biDimensionalWidget->On();

		renderWindowInteractor->Start();
	}

	return EXIT_SUCCESS;
}
