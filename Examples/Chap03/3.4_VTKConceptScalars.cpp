/**********************************************************************

  文件名: 3.4_VTKConceptScalars.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
	//创建点集数据：包含两个坐标点。
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0,0,0);
	points->InsertNextPoint(1,0,0);

	//创建多边形数据。
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	//准备加入点数据的标量值，两个标量值分别为1和2。
	vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
	weights->SetNumberOfValues(2);
	weights->SetValue(0, 1);
	weights->SetValue(1, 2);

	//先获取多边形数据的点数据指针，然后设置该点数据的标量属性值。
	polydata->GetPointData()->SetScalars(weights);

	//输出索引号为0的点的标量值。
	double weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
	std::cout << "double weight: " << weight << std::endl;

	return EXIT_SUCCESS;
}