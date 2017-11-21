/**********************************************************************

  文件名: 7.4_UnstructuredGridVolumeRenderingApp.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkHAVSVolumeMapper.h>
#include <vtkUnstructuredGridVolumeRayCastMapper.h>
#include <vtkUnstructuredGridVolumeZSweepMapper.h>
#include <vtkProjectedTetrahedraMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredPointsReader.h>
#include <vtkSLCReader.h>
#include <vtkStructuredPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkThreshold.h>
#include <vtkDataSetTriangleFilter.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkStdString.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTesting.h>

//测试：../data/ironProt.vtk
int main(int argc, char*argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"StructuredPointsFile(*.vtk)"<<std::endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkRenderer> ren =
		vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	iren->SetDesiredUpdateRate(3);

	vtkSmartPointer<vtkStructuredPointsReader> reader =
		vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName(argv[1]);

	vtkSmartPointer<vtkThreshold> thresh =
		vtkSmartPointer<vtkThreshold>::New();
	thresh->ThresholdByUpper(80);
	thresh->AllScalarsOff();
	thresh->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkDataSetTriangleFilter> trifilter =
		vtkSmartPointer<vtkDataSetTriangleFilter>::New();
	trifilter->SetInputConnection(thresh->GetOutputPort());

	vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacityTransferFunction->AddPoint(80.0,  0.0);
	opacityTransferFunction->AddPoint(120.0, 0.2);
	opacityTransferFunction->AddPoint(255.0, 0.2);

	vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	colorTransferFunction->AddRGBPoint(80.0,  0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(120.0, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(160.0, 1.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(200.0, 0.0, 1.0, 0.0);
	colorTransferFunction->AddRGBPoint(255.0, 0.0, 1.0, 1.0);

	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->ShadeOff();
	volumeProperty->SetInterpolationTypeToLinear();

	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetProperty(volumeProperty);

	int RenderType = 3;
	if (RenderType == 1)
	{
		vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper> volumeMapper =
			vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper>::New();
		volumeMapper->SetInputConnection(trifilter->GetOutputPort());
		volume->SetMapper(volumeMapper);
		ren->AddVolume(volume);
	}
	else if(RenderType == 2)
	{
		vtkSmartPointer<vtkUnstructuredGridVolumeZSweepMapper> volumeMapper =
			vtkSmartPointer<vtkUnstructuredGridVolumeZSweepMapper>::New();
		volumeMapper->SetInputConnection(trifilter->GetOutputPort());
		volume->SetMapper(volumeMapper);
		ren->AddVolume(volume);
	}
	else if(RenderType == 3)
	{
		vtkSmartPointer<vtkProjectedTetrahedraMapper> volumeMapper =
			vtkSmartPointer<vtkProjectedTetrahedraMapper>::New();
		volumeMapper->SetInputConnection(trifilter->GetOutputPort());
		volume->SetMapper(volumeMapper);
		ren->AddVolume(volume);
	}
	else if(RenderType == 4)
	{
		vtkSmartPointer<vtkHAVSVolumeMapper> volumeMapper =
			vtkSmartPointer<vtkHAVSVolumeMapper>::New();
		volumeMapper->SetInputConnection(trifilter->GetOutputPort());
		volumeMapper->SetLevelOfDetail(false);
		volumeMapper->SetGPUDataStructures(false);
		volumeMapper->SetKBufferSizeTo2();
		volume->SetMapper(volumeMapper);
		renWin->Render();

		int supported = volumeMapper->SupportedByHardware(ren);
		if(supported)
		{
			ren->AddVolume(volume);
			volumeMapper->SetLevelOfDetail(false);
			volumeMapper->SetKBufferSizeTo2();
		}
	}
	
	renWin->SetSize(640, 480);
	renWin->Render();
	renWin->SetWindowName("UnstructuredGridVolumeRendering");

	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}