/**********************************************************************

  文件名: 5.3_ImageChangeInformationExample.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageData.h>

//测试图像：../data/lena.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	int dims[3];
	double origin[3];
	double spaceing[3];

	reader->GetOutput()->GetDimensions(dims);
	std::cout<<"原图像维数:" <<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<std::endl;
	reader->GetOutput()->GetOrigin(origin);
	std::cout<<"原图像原点:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
	reader->GetOutput()->GetSpacing(spaceing);
	std::cout<<"原像素间隔:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl<<std::endl;;

	vtkSmartPointer<vtkImageChangeInformation> changer =
		vtkSmartPointer<vtkImageChangeInformation>::New();
	changer->SetInput(reader->GetOutput());
	changer->SetOutputOrigin(100, 100, 0);
	changer->SetOutputSpacing(5,5,1);
	changer->SetCenterImage(1);
	changer->Update();

	changer->GetOutput()->GetDimensions(dims);
	std::cout<<"修改后图像维数:" <<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<std::endl;
	changer->GetOutput()->GetOrigin(origin);
	std::cout<<"修改后图像原点:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
	changer->GetOutput()->GetSpacing(spaceing);
	std::cout<<"修改后像素间隔:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl;

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(changer->GetOutputPort());
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ImageChangeInformationExample");


	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
