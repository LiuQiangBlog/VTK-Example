/**********************************************************************

  文件名: 6.2_PolyDataNormal.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPLYReader.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataNormals.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>
#include <vtkSphereSource.h>
#include <vtkMaskPoints.h>
#include <vtkProperty.h>

//测试文件：../data/fran_cut.vtk
int main(int argc, char *argv[])
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

	vtkSmartPointer<vtkPolyDataNormals> normFilter = 
		vtkSmartPointer<vtkPolyDataNormals>::New();
	normFilter->SetInput(reader->GetOutput());
	normFilter->SetComputePointNormals(1);
	normFilter->SetComputeCellNormals(0);
	normFilter->SetAutoOrientNormals(1);
	normFilter->SetSplitting(0);
	normFilter->Update();

	vtkSmartPointer<vtkMaskPoints> mask = 
		vtkSmartPointer<vtkMaskPoints>::New();
	mask->SetInput(normFilter->GetOutput());
	mask->SetMaximumNumberOfPoints(300);
	mask->RandomModeOn();

	vtkSmartPointer<vtkArrowSource> arrow = 
		vtkSmartPointer<vtkArrowSource>::New();

	vtkSmartPointer<vtkGlyph3D> glyph = 
		vtkSmartPointer<vtkGlyph3D>::New();
	glyph->SetInput(mask->GetOutput());
	glyph->SetSource(arrow->GetOutput()); 
	glyph->SetVectorModeToUseNormal();
	glyph->SetScaleFactor(0.01);

	vtkSmartPointer<vtkPolyDataMapper> originMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	originMapper->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkActor> originActor = 
		vtkSmartPointer<vtkActor>::New();
	originActor->SetMapper(originMapper);

	vtkSmartPointer<vtkPolyDataMapper> normedMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	normedMapper->SetInput(normFilter->GetOutput());

	vtkSmartPointer<vtkActor> normedActor = 
		vtkSmartPointer<vtkActor>::New();
	normedActor->SetMapper(normedMapper);

	vtkSmartPointer<vtkPolyDataMapper> glyphMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	glyphMapper->SetInput(glyph->GetOutput());

	vtkSmartPointer<vtkActor> glyphActor = 
		vtkSmartPointer<vtkActor>::New();
	glyphActor->SetMapper(glyphMapper);
	glyphActor->GetProperty()->SetColor(1., 0.,0.);

	double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
	double normViewport[4] = {0.33, 0.0, 0.66, 1.0};
	double glphViewport[4] = {0.66, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> normedRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	normedRenderer->SetViewport(normViewport);
	normedRenderer->AddActor(normedActor);
	normedRenderer->ResetCamera();
	normedRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> glyphRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	glyphRenderer->SetViewport(glphViewport);
	glyphRenderer->AddActor(glyphActor);
	glyphRenderer->AddActor(normedActor);
	glyphRenderer->ResetCamera();
	glyphRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(normedRenderer);
	renderWindow->AddRenderer(glyphRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataNormal");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}