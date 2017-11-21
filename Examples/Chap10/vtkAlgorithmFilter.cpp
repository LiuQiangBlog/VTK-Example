/**********************************************************************

  文件名: vtkAlgorithmFilter.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkAlgorithmFilter.h"
#include "vtkTestDataObject.h"

#include "vtkCommand.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"

vtkStandardNewMacro(vtkAlgorithmFilter);

//----------------------------------------------------------------------------
vtkAlgorithmFilter::vtkAlgorithmFilter()
{
	Factor = 2.0;
	this->SetNumberOfInputPorts( 1 );
	this->SetNumberOfOutputPorts( 1 );
}

//----------------------------------------------------------------------------
vtkAlgorithmFilter::~vtkAlgorithmFilter()
{
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::ProcessRequest(vtkInformation* request,
									   vtkInformationVector** inputVector,
									   vtkInformationVector* outputVector)
{
	if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA_OBJECT()))
	{
		return this->RequestDataObject(request, inputVector, outputVector);
	}

	if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
	{
		return this->RequestData(request, inputVector, outputVector);
	}

	if(request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
	{
		return this->RequestUpdateExtent(request, inputVector, outputVector);
	}

	if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
	{
		return this->RequestInformation(request, inputVector, outputVector);
	}

	return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::FillOutputPortInformation(
	int vtkNotUsed(port), vtkInformation* info)
{
	info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTestDataObject");
	return 1;
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::FillInputPortInformation(
	int vtkNotUsed(port), vtkInformation* info)
{
	info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkTestDataObject");
	return 1;
}


int vtkAlgorithmFilter::RequestDataObject(vtkInformation* vtkNotUsed(request),
										  vtkInformationVector** vtkNotUsed(inputVector),
										  vtkInformationVector* outputVector )
{
	vtkInformation* outInfo = outputVector->GetInformationObject(0);
	vtkTestDataObject* output = vtkTestDataObject::SafeDownCast(
		outInfo->Get( vtkDataObject::DATA_OBJECT() ) );


	if ( ! output )
	{
		output = vtkTestDataObject::New();
		outInfo->Set( vtkDataObject::DATA_OBJECT(), output );
		output->FastDelete();
		output->SetPipelineInformation( outInfo );

		this->GetOutputPortInformation(0)->Set(
			vtkDataObject::DATA_EXTENT_TYPE(), output->GetExtentType() );
	}

	return 1;
}


//----------------------------------------------------------------------------
int vtkAlgorithmFilter::RequestInformation(
	vtkInformation* vtkNotUsed(request),
	vtkInformationVector** vtkNotUsed(inputVector),
	vtkInformationVector* vtkNotUsed(outputVector))
{
	return 1;
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::RequestUpdateExtent(
	vtkInformation* vtkNotUsed(request),
	vtkInformationVector** inputVector,
	vtkInformationVector* vtkNotUsed(outputVector))
{
	int numInputPorts = this->GetNumberOfInputPorts();
	for (int i=0; i<numInputPorts; i++)
	{
		int numInputConnections = this->GetNumberOfInputConnections(i);
		for (int j=0; j<numInputConnections; j++)
		{
			vtkInformation* inputInfo = inputVector[i]->GetInformationObject(j);
			inputInfo->Set(vtkStreamingDemandDrivenPipeline::EXACT_EXTENT(), 1);
		}
	}
	return 1;
}

//----------------------------------------------------------------------------
int vtkAlgorithmFilter::RequestData(
									vtkInformation* vtkNotUsed(request),
									vtkInformationVector **inputVector,
									vtkInformationVector* outputVector )
{
	vtkInformation* outInfo = outputVector->GetInformationObject(0);
	vtkTestDataObject* output = vtkTestDataObject::SafeDownCast(
		outInfo->Get( vtkDataObject::DATA_OBJECT() ) );

	vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
	vtkTestDataObject *input = vtkTestDataObject::SafeDownCast(
		inInfo->Get(vtkDataObject::DATA_OBJECT()));
	output->ShallowCopy(input);
	output->SetValue(output->GetValue() + this->GetFactor());

	return 1;
}

vtkTestDataObject* vtkAlgorithmFilter::GetOutput()
{
	return this->GetOutput(0);
}

//----------------------------------------------------------------------------
vtkTestDataObject* vtkAlgorithmFilter::GetOutput(int port)
{
	return vtkTestDataObject::SafeDownCast(this->GetOutputDataObject(port));
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::SetOutput(vtkDataObject* d)
{
	this->GetExecutive()->SetOutputData(0, d);
}

//----------------------------------------------------------------------------
vtkDataObject* vtkAlgorithmFilter::GetInput()
{
	return this->GetInput(0);
}

//----------------------------------------------------------------------------
vtkDataObject* vtkAlgorithmFilter::GetInput(int port)
{
	return this->GetExecutive()->GetInputData(port, 0);
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::SetInput(vtkDataObject* input)
{
	this->SetInput(0, input);
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::SetInput(int index, vtkDataObject* input)
{
	if(input)
	{
		this->SetInputConnection(index, input->GetProducerPort());
	}
	else
	{
		this->SetInputConnection(index, 0);
	}
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::AddInput(vtkDataObject* input)
{
	this->AddInput(0, input);
}

//----------------------------------------------------------------------------
void vtkAlgorithmFilter::AddInput(int index, vtkDataObject* input)
{
	if(input)
	{
		this->AddInputConnection(index, input->GetProducerPort());
	}
}
