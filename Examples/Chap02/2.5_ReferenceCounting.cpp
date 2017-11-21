/**********************************************************************

  文件名: 2.5_ReferenceCounting.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkObject.h>

// MyFunction函数：演示智能指针可以作为函数返回值
vtkSmartPointer<vtkImageData> MyFunction()
{
	vtkSmartPointer<vtkImageData> myObject = vtkSmartPointer<vtkImageData>::New();
	std::cout<<"MyFunction::myObject reference count = "<<myObject->GetReferenceCount()<<std::endl;
	return myObject;
}

//测试文件：data/VTK-logo.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"BMP-File(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}
	//演示引用计数：
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	std::cout<<"Reference Count of reader->GetOutput (Before Assignment) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> image1 = reader->GetOutput();
	std::cout<<"Reference Count of reader->GetOutput (Assign to image1) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of image1 = "
		<<image1->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> image2 = reader->GetOutput();
	std::cout<<"Reference Count of reader->GetOutput (Assign to image2) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of image2 = "
		<<image2->GetReferenceCount()<<std::endl;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//演示智能指针可以作为函数返回值
	//由于函数MyFunction()的返回值是通过拷贝的方式，
	//将数据赋予调用的变量，因此该数据的引用计数保持不变
	std::cout<<"myObject reference count = "
		<<MyFunction()->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> MyImageData = MyFunction();
	std::cout<<"MyFunction return value reference count = "
		<<MyFunction()->GetReferenceCount()<<std::endl;

	std::cout<<"MyImageData reference count = "
		<<MyImageData->GetReferenceCount()<<std::endl;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//如果没有给对象分配内存，仍然可以使用智能指针:
	vtkSmartPointer<vtkBMPReader> Reader = vtkSmartPointer<vtkBMPReader>::New();
	vtkImageData* pd = Reader->GetOutput();
	//////////////////////////////////////////////////////////////////////////

	system("pause");
	return EXIT_SUCCESS;
}