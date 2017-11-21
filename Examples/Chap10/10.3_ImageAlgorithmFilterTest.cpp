/**********************************************************************

  文件名: 10.3_ImageAlgorithmFilterTest.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include "vtkImageAlgorithmFilter.h"
#include "vtkImageData.h"

void PrintImage(vtkImageData* image);

int main (int argc, char *argv[])
{
	vtkSmartPointer<vtkImageData> input =
		vtkSmartPointer<vtkImageData>::New();
	input->SetDimensions(2,2,1);
	input->SetNumberOfScalarComponents(1);

	int* dims = input->GetDimensions();

	for (int y=0; y<dims[1]; y++)
	{
		for (int x=0; x<dims[0]; x++)
		{
			input->SetScalarComponentFromDouble(x,y,0,0,2.0);
		}
	}

	std::cout << "Input image: " << std::endl;
	PrintImage(input);

	vtkSmartPointer<vtkImageAlgorithmFilter> filter =
		vtkSmartPointer<vtkImageAlgorithmFilter>::New();
	filter->SetInput(input);
	filter->Update();

	vtkImageData* output = filter->GetOutput();

	std::cout << "Output image: " << std::endl;
	PrintImage(output);

	system("pause");

	return EXIT_SUCCESS;
}

void PrintImage(vtkImageData* image)
{
	int* dims = image->GetDimensions();

	for (int y=0; y<dims[1]; y++)
	{
		for (int x=0; x<dims[0]; x++)
		{
			double v = image->GetScalarComponentAsDouble(x,y,0,0);
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}
}