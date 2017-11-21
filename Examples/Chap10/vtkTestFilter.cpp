/**********************************************************************

  文件名: vtkTestFilter.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkTestFilter.h"

vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
	this->SetNumberOfInputPorts(0);

	m_Value = 10;
}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
							   vtkInformationVector **inputVector,
							   vtkInformationVector *outputVector)
{
	this->InvokeEvent(MyEvent, &m_Value);
	return 1;
}