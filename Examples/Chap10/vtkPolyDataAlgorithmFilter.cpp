/**********************************************************************

  文件名: vtkPolyDataAlgorithmFilter.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkPolyDataAlgorithmFilter.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkPolyDataAlgorithmFilter);

int vtkPolyDataAlgorithmFilter::FillInputPortInformation( int port, vtkInformation* info )
{
	if(port == 0)
	{
		info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
		info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
		return 1;
	}

	vtkErrorMacro("This filter does not have more than 1 input port!");
	return 0;
}

int vtkPolyDataAlgorithmFilter::RequestData(vtkInformation *vtkNotUsed(request),
											vtkInformationVector **inputVector,
											vtkInformationVector *outputVector)
{
	vtkDebugMacro("Filter开始执行...\n");
	// get the info objects
	vtkInformation *inInfo0 = inputVector[0]->GetInformationObject(0);
	vtkInformation *inInfo1 = inputVector[0]->GetInformationObject(1);
	vtkInformation *outInfo = outputVector->GetInformationObject(0);

	vtkPolyData *output = vtkPolyData::SafeDownCast(
		outInfo->Get(vtkDataObject::DATA_OBJECT()));

	vtkPolyData *input0 = vtkPolyData::SafeDownCast(
		inInfo0->Get(vtkDataObject::DATA_OBJECT()));

	vtkPolyData *input1 = vtkPolyData::SafeDownCast(
		inInfo1->Get(vtkDataObject::DATA_OBJECT()));

	std::cout << "Input 0 has " << input0->GetNumberOfPoints() << " points." << std::endl;
	std::cout << "Input 1 has " << input1->GetNumberOfPoints() << " points." << std::endl;

	output->ShallowCopy(input0);

	return 1;
}

//----------------------------------------------------------------------------
void vtkPolyDataAlgorithmFilter::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os,indent);
}