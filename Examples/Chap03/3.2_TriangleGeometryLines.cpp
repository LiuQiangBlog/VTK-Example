/**********************************************************************

  文件名: 3.2_TriangleGeometryLines.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>

int main(int argc, char *argv[])
{
	//创建三个坐标点
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint ( 1.0, 0.0, 0.0 ); //返回第一个点的ID：0
	points->InsertNextPoint ( 0.0, 0.0, 1.0 ); //返回第二个点的ID：1
	points->InsertNextPoint ( 0.0, 0.0, 0.0 ); //返回第三个点的ID：2

	//每两个坐标点之间分别创建一条线
	//SetId()的第一个参数是线段的端点ID，第二个参数是连接的点的ID
	vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
	line0->GetPointIds()->SetId ( 0,0 ); 
	line0->GetPointIds()->SetId ( 1,1 );

	vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
	line1->GetPointIds()->SetId ( 0,1 );
	line1->GetPointIds()->SetId ( 1,2 );

	vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
	line2->GetPointIds()->SetId ( 0,2 );
	line2->GetPointIds()->SetId ( 1,0 );

	//创建Cell数组，用于存储以上创建的线段
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	lines->InsertNextCell ( line0 );
	lines->InsertNextCell ( line1 );
	lines->InsertNextCell ( line2 );

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

	//将点和线加入到数据集中，前者指定数据集的几何，后者指定其拓扑
	polydata->SetPoints ( points );
	polydata->SetLines ( lines );

	vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	writer->SetFileName ( "TriangleLines.vtk" );
	writer->SetInput ( polydata );
	writer->Write();

	return EXIT_SUCCESS;
}