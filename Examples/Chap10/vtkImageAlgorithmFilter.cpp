/**********************************************************************

  文件名: vtkImageAlgorithmFilter.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkImageAlgorithmFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkImageAlgorithmFilter);

int vtkImageAlgorithmFilter::RequestData(vtkInformation *vtkNotUsed(request),
										 vtkInformationVector **inputVector,
										 vtkInformationVector *outputVector)
{
	vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
	vtkInformation *outInfo = outputVector->GetInformationObject(0);

	vtkImageData *input = vtkImageData::SafeDownCast(
		inInfo->Get(vtkDataObject::DATA_OBJECT()));

	vtkImageData *output = vtkImageData::SafeDownCast(
		outInfo->Get(vtkDataObject::DATA_OBJECT()));

	vtkSmartPointer<vtkImageData> image =
		vtkSmartPointer<vtkImageData>::New();
	image->ShallowCopy(input);

	image->SetScalarComponentFromDouble(0,0,0,0, 5.0);

	output->ShallowCopy(image);

	output->SetExtent(input->GetExtent());
	output->SetUpdateExtent(output->GetExtent());
	output->SetWholeExtent(output->GetExtent());

	return 1;
}