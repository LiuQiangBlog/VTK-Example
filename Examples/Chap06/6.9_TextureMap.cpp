/**********************************************************************

  文件名: 6.9_TextureMap.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransformTextureCoords.h>
#include <vtkTexture.h>
#include <vtkTextureMapToSphere.h>
#include <vtkTextureMapToCylinder.h>
#include <vtkBMPReader.h>
#include <vtkTexturedSphereSource.h>
#include <vtkXMLPolyDataReader.h>

//测试：../data/masonry.bmp ../data/cow.vtp
int main (int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Usage: " << argv[0]
		<< "texture(.png)"
			<< "model(.vtp)" <<std::endl;
		return EXIT_FAILURE;
	}

	double translate[3];
	translate[0] = 10.0;
	translate[1] = 0.0;
	translate[2] = 0.0;
	std::cout << translate[0] << ", "
		<< translate[1] << ", "
		<< translate[2] << "\n";

	vtkSmartPointer<vtkBMPReader> texReader =
		vtkSmartPointer<vtkBMPReader>::New();
	texReader->SetFileName(argv[1]);

	vtkSmartPointer<vtkTexture> texture =
		vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());

	vtkSmartPointer<vtkXMLPolyDataReader> modelReader =
		vtkSmartPointer<vtkXMLPolyDataReader>::New();
	modelReader->SetFileName(argv[2]);

	vtkSmartPointer<vtkTextureMapToCylinder> texturemap = 
		vtkSmartPointer<vtkTextureMapToCylinder>::New();
	texturemap->SetInputConnection(modelReader->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(texturemap->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper( mapper );
	actor->SetTexture( texture );

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer( renderer );

	vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renWinInteractor->SetRenderWindow( renderWindow );

	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("TextureMap");
	renderWindow->Render();
	renderWindow->Render();
	renWinInteractor->Start();

	return EXIT_SUCCESS;
}