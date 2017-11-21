/**********************************************************************

  文件名: 2.4_vtkPipelineDemo.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

//测试文件：data/head.vtk
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"VTK-File(*.vtk)"<<std::endl;
		return EXIT_FAILURE;
	}
	//读入Structured_Points类型的vtk文件。
	vtkSmartPointer<vtkStructuredPointsReader> reader = 
		vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName(argv[1]);

	//用移动立方体法提取等值面。
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = 
		vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0,500);

	//将生成的等值面数据进行Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());

	//把Mapper的输出送入渲染引擎进行显示
	//////////////////////////////////////渲染引擎部分////////////////////////////////////
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("vtkPipelineDemo");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renWin);

	interactor->Initialize();
	interactor->Start();
	//////////////////////////////////////////////////////////////////////////////////////////////////

	return EXIT_SUCCESS;
}