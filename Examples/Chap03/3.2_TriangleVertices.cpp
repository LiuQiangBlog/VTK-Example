/**********************************************************************

  文件名: 3.2_TriangleVertices.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>

int main(int argc, char *argv[])
{
    //创建点的坐标
    double X[3] = {1.0, 0.0, 0.0};
    double Y[3] = {0.0, 0.0, 1.0};
    double Z[3] = {0.0, 0.0, 0.0};

    //创建点数据以及在每个点坐标上加入(顶点)Vertex这种Cell
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    for ( unsigned int i = 0; i < 3; ++i )
    {
        //定义用于存储点索引的中间变量，vtkIdType就相当于int或long型
        vtkIdType pid[1];

        //把每个点坐标加入到vtkPoints中，InsertNextPoint()返回加入的点的索引号，
        //下面我们需要使用这个索引号来创建Vertex类型的Cell
        pid[0] = points->InsertNextPoint ( X[i], Y[i], Z[i] );

        //在每个坐标点上分别创建一个Vertex，Vertex是Cell里的一种
        vertices->InsertNextCell ( 1,pid );
    }

    //创建vtkPolyData对象
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //指定数据集的几何(由points指定)，以及数据集的拓扑(由vertices指定)
    polydata->SetPoints ( points );
    polydata->SetVerts ( vertices );

    //将生成的数据集写到TriangleVerts.vtk文件里，保存在工程当前目录下
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName ( "TriangleVerts.vtk" );
    writer->SetInput ( polydata );
    writer->Write();

    return EXIT_SUCCESS;
}