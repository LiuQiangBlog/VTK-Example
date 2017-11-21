/**********************************************************************

  文件名: 3.2_TrianglePoints.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>

int main(int argc, char *argv[])
{
	//创建点数据
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint ( 1.0, 0.0, 0.0 );
	points->InsertNextPoint ( 0.0, 0.0, 0.0 );
	points->InsertNextPoint ( 0.0, 1.0, 0.0 );

	//创建vtkPolyData类型的数据，vtkPolyData派生自vtkPointSet，
	//vtkPointSet是vtkDataSet的子类。
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

	//将创建的点数据加入到vtkPolyData数据里
	polydata->SetPoints ( points );

	//将vtkPolyData类型的数据写入到一个vtk文件，保存位置是工程当前目录
	vtkSmartPointer< vtkPolyDataWriter > writer = vtkSmartPointer< vtkPolyDataWriter >::New();
	writer->SetFileName("triangle.vtk");
	writer->SetInput(polydata);
	writer->Write();

	return EXIT_SUCCESS;
}
