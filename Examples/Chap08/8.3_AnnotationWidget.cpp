/**********************************************************************

  文件名: 8.3_AnnotationWidget.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkScalarBarWidget.h>
#include <vtkTextActor.h>
#include <vtkTextWidget.h>
#include <vtkTextRepresentation.h>
#include <vtkTextProperty.h>
#include <vtkCaptionRepresentation.h>
#include <vtkCaptionWidget.h>
#include <vtkCaptionActor2D.h>
#include <vtkBalloonRepresentation.h> 
#include <vtkBalloonWidget.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>

//测试：../data/scalarBarWidgetTestData.vtk
int main(int argc, char* argv[])
{
	if ( argc < 2 )
	{
		std::cout<<argv[0]<<" "<<"scalarBarWidgetTestData.vtk(*.vtk)"<<std::endl;
		return EXIT_FAILURE;
	}
	char* fileName = argv[1];

	vtkSmartPointer< vtkUnstructuredGridReader > reader = vtkSmartPointer< vtkUnstructuredGridReader >::New();
	reader->SetFileName(fileName);
	reader->Update() ;

	vtkSmartPointer< vtkLookupTable > lut = vtkSmartPointer< vtkLookupTable >::New();
	lut->Build();

	vtkSmartPointer< vtkDataSetMapper > mapper = vtkSmartPointer< vtkDataSetMapper >::New();
	mapper->SetInput(reader->GetOutput());
	mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());
	mapper->SetLookupTable(lut);

	vtkSmartPointer< vtkActor > actor = vtkSmartPointer< vtkActor >::New();
	actor->SetMapper(mapper);

	vtkSmartPointer< vtkRenderer > renderer = vtkSmartPointer< vtkRenderer >::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer< vtkRenderWindow > renderWindow = vtkSmartPointer< vtkRenderWindow >::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->Render();
	renderWindow->SetWindowName("AnnotationWidget");
	renderWindow->SetSize(400, 400);

	vtkSmartPointer< vtkRenderWindowInteractor > interactor = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	interactor->SetRenderWindow(renderWindow);

	//////////////////////////////////////////////////////////////////////////
	// vtkScalarBarWidget
	vtkSmartPointer< vtkScalarBarActor > scalarBarActor = vtkSmartPointer< vtkScalarBarActor >::New();
	scalarBarActor->SetOrientationToHorizontal();
	scalarBarActor->SetLookupTable(lut);

	vtkSmartPointer< vtkScalarBarWidget > scalarBarWidget = vtkSmartPointer< vtkScalarBarWidget >::New();
	scalarBarWidget->SetInteractor(interactor);
	scalarBarWidget->SetScalarBarActor(scalarBarActor);
	scalarBarWidget->On();

	//////////////////////////////////////////////////////////////////////////
	// vtkTextWidget
	vtkSmartPointer<vtkTextActor> textActor =
		vtkSmartPointer<vtkTextActor>::New();
	textActor->SetInput("VTK Widgets");
	textActor->GetTextProperty()->SetColor( 0.0, 1.0, 0.0 );

	vtkSmartPointer<vtkTextWidget> textWidget =
		vtkSmartPointer<vtkTextWidget>::New();

	vtkSmartPointer<vtkTextRepresentation> textRepresentation =
		vtkSmartPointer<vtkTextRepresentation>::New();
	textRepresentation->GetPositionCoordinate()->SetValue( .15, .15 );
	textRepresentation->GetPosition2Coordinate()->SetValue( .7, .2 );
	textWidget ->SetRepresentation( textRepresentation );

	textWidget->SetInteractor(interactor);
	textWidget->SetTextActor(textActor);
	textWidget->SelectableOff();
	textWidget->On();

	//////////////////////////////////////////////////////////////////////////
	// vtkBalloonWidget
	vtkSmartPointer<vtkBalloonRepresentation> balloonRep =
		vtkSmartPointer<vtkBalloonRepresentation>::New();
	balloonRep->SetBalloonLayoutToImageRight();

	vtkSmartPointer<vtkBalloonWidget> balloonWidget =
		vtkSmartPointer<vtkBalloonWidget>::New();
	balloonWidget->SetInteractor(interactor);
	balloonWidget->SetRepresentation(balloonRep);
	balloonWidget->AddBalloon(actor, "This is a widget example",NULL);
	balloonWidget->On();

	//////////////////////////////////////////////////////////////////////////
	// vtkOrientationMarkerWidget
	vtkSmartPointer<vtkAxesActor> iconActor = vtkSmartPointer<vtkAxesActor>::New();
	vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget  =
		vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	orientationWidget ->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
	orientationWidget ->SetOrientationMarker( iconActor );
	orientationWidget ->SetInteractor( interactor );
	orientationWidget ->SetViewport( 0.0, 0.0, 0.2, 0.2 );
	orientationWidget ->SetEnabled( 1 );
	orientationWidget ->InteractiveOn();

	////////////////////////////////////////////////////////////////////////////
	//// vtkCaptionWidget
	//vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = 
	//	vtkSmartPointer<vtkCaptionRepresentation>::New();
	//captionRepresentation->GetCaptionActor2D()->SetCaption("Caption Widget");
	//captionRepresentation->GetCaptionActor2D()->GetTextActor()->GetTextProperty()->SetFontSize(20);

	//double pos[3] = {.5,0,0};
	//captionRepresentation->SetAnchorPosition(pos);

	//vtkSmartPointer<vtkCaptionWidget> captionWidget = 
	//	vtkSmartPointer<vtkCaptionWidget>::New();
	//captionWidget->SetInteractor(interactor);
	//captionWidget->SetRepresentation(captionRepresentation);
	//captionWidget->On();

	renderWindow->Render();
	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}
