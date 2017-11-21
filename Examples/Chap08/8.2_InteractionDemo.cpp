/**********************************************************************

  文件名: 8.2_InteractionDemo.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

//测试：../data/VTKBook-TestImage.jpg
int main(int argc, char* argv[])
{
	if ( argc < 2 )
	{
		std::cout<<"please load a *.jpg image."<<std::endl;
		return EXIT_FAILURE;
	}

	char* fileName = argv[1];
	vtkSmartPointer<vtkJPEGReader> reader = 
		vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	vtkSmartPointer<vtkImageActor> imageActor = 
		vtkSmartPointer<vtkImageActor>::New();
	imageActor->SetInput( reader->GetOutput() );

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor( imageActor );
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer( renderer );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("InteractionDemo");

	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleImage> style = 
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}
