/**********************************************************************

  文件名: vtkReportProgressFilter.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkReportProgressFilter.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkReportProgressFilter);

int vtkReportProgressFilter::RequestData(vtkInformation *vtkNotUsed(request),
										 vtkInformationVector **inputVector,
										 vtkInformationVector *outputVector)
{
	vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
	vtkInformation *outInfo = outputVector->GetInformationObject(0);

	vtkPolyData *input = vtkPolyData::SafeDownCast(
		inInfo->Get(vtkDataObject::DATA_OBJECT()));

	vtkPolyData *output = vtkPolyData::SafeDownCast(
		outInfo->Get(vtkDataObject::DATA_OBJECT()));

	for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
	{
		this->UpdateProgress(static_cast<double>(i)/input->GetNumberOfPoints());
	}

	output->ShallowCopy(input);

	return 1;
}