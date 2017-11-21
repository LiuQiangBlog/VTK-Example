/**********************************************************************

  文件名: 10.3_AlgorithmFilterTest.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include "vtkTestDataObject.h"
#include "vtkAlgorithmFilter.h"

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkTestDataObject> input = 
		vtkSmartPointer<vtkTestDataObject>::New();
	input->SetValue(10);

	vtkSmartPointer<vtkAlgorithmFilter> filter = vtkAlgorithmFilter::New();
	filter->SetInputConnection(input->GetProducerPort());
	filter->SetFactor(2);
	filter->Update();

	vtkTestDataObject* output = filter->GetOutput();
	std::cout << "Output value: " << output->GetValue() << std::endl;
	std::cout << "Input  value: " << input->GetValue() << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}