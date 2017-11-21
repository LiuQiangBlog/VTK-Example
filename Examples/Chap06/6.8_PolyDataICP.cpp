/**********************************************************************

  文件名: 6.8_PolyDataICP.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkLandmarkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkPolyDataReader.h>
#include <vtkTransform.h>

//测试文件：../data/fran_cut.vtk
int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		std::cout<<argv[0]<<" *.vtk"<<std::endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkPolyDataReader> reader = 
		vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();
	vtkSmartPointer<vtkPolyData> original  =  reader->GetOutput();

	vtkSmartPointer<vtkTransform> translation =
		vtkSmartPointer<vtkTransform>::New();
	translation->Translate(0.2, 0.0, 0.0);
	translation->RotateX(30);

	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter1 =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter1->SetInput(reader->GetOutput());
	transformFilter1->SetTransform(translation);
	transformFilter1->Update();

	vtkSmartPointer<vtkPolyData> source =
		vtkSmartPointer<vtkPolyData>::New();
	source->SetPoints(original->GetPoints());

	vtkSmartPointer<vtkPolyData> target =
		vtkSmartPointer<vtkPolyData>::New();
	target->SetPoints(transformFilter1->GetOutput()->GetPoints());

	vtkSmartPointer<vtkVertexGlyphFilter> sourceGlyphFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	sourceGlyphFilter->SetInput(source);
	sourceGlyphFilter->Update();

	vtkSmartPointer<vtkVertexGlyphFilter> targetGlyphFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	targetGlyphFilter->SetInput(target);
	targetGlyphFilter->Update();

	vtkSmartPointer<vtkIterativeClosestPointTransform> icpTransform = 
		vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	icpTransform->SetSource(sourceGlyphFilter->GetOutput());
	icpTransform->SetTarget(targetGlyphFilter->GetOutput());
	icpTransform->GetLandmarkTransform()->SetModeToRigidBody();
	icpTransform->SetMaximumNumberOfIterations(20);
	icpTransform->StartByMatchingCentroidsOn();
	icpTransform->Modified();
	icpTransform->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter2 =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter2->SetInput(sourceGlyphFilter->GetOutput());
	transformFilter2->SetTransform(icpTransform);
	transformFilter2->Update();

	vtkSmartPointer<vtkPolyDataMapper> sourceMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	sourceMapper->SetInputConnection(sourceGlyphFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> sourceActor =
		vtkSmartPointer<vtkActor>::New();
	sourceActor->SetMapper(sourceMapper);
	sourceActor->GetProperty()->SetColor(0,1,0);
	sourceActor->GetProperty()->SetPointSize(3);

	vtkSmartPointer<vtkPolyDataMapper> targetMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	targetMapper->SetInputConnection(targetGlyphFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> targetActor =
		vtkSmartPointer<vtkActor>::New();
	targetActor->SetMapper(targetMapper);
	targetActor->GetProperty()->SetColor(1,0,0);
	targetActor->GetProperty()->SetPointSize(3);

	vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	solutionMapper->SetInputConnection(transformFilter2->GetOutputPort());

	vtkSmartPointer<vtkActor> solutionActor =
		vtkSmartPointer<vtkActor>::New();
	solutionActor->SetMapper(solutionMapper);
	solutionActor->GetProperty()->SetColor(0,0,1);
	solutionActor->GetProperty()->SetPointSize(3);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderer->AddActor(sourceActor);
	renderer->AddActor(targetActor);
	renderer->AddActor(solutionActor);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataICP");
	renderWindow->Render();
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}