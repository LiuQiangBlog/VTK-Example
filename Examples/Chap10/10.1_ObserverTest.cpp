/**********************************************************************

  文件名: 10.1_ObserverTest.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include "vtkTestFilter.h"
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

void CallbackFunction(vtkObject* caller,
					  long unsigned int eventId,
					  void* clientData, void* callData )
{
	int* callDataCasted = reinterpret_cast<int*>(callData);
	std::cout << *callDataCasted << std::endl;
}

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkTestFilter> filter =
		vtkSmartPointer<vtkTestFilter>::New();

	vtkSmartPointer<vtkCallbackCommand> callback =
		vtkSmartPointer<vtkCallbackCommand>::New();
	callback->SetCallback(CallbackFunction );

	filter->AddObserver(MyEvent, callback);
	filter->Update();

	system("pause");

	return EXIT_SUCCESS;
}