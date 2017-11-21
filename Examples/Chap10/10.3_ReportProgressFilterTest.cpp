/**********************************************************************

  文件名: 10.3_ReportProgressFilterTest.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include "vtkReportProgressFilter.h"

void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

int main(int, char *[])
{ 
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();

	vtkSmartPointer<vtkCallbackCommand> progressCallback = 
		vtkSmartPointer<vtkCallbackCommand>::New();
	progressCallback->SetCallback(ProgressFunction);

	vtkSmartPointer<vtkReportProgressFilter> testFilter = 
		vtkSmartPointer<vtkReportProgressFilter>::New();
	testFilter->SetInputConnection(sphereSource->GetOutputPort());
	testFilter->AddObserver(vtkCommand::ProgressEvent, progressCallback);
	testFilter->Update();

	system("pause");
	return EXIT_SUCCESS;
}

void ProgressFunction ( vtkObject* caller,
					   long unsigned int vtkNotUsed(eventId),
					   void* vtkNotUsed(clientData),
					   void* vtkNotUsed(callData) )
{
	vtkReportProgressFilter* testFilter = static_cast<vtkReportProgressFilter*>(caller);
	std::cout << "Progress: " << testFilter->GetProgress() << std::endl;
}