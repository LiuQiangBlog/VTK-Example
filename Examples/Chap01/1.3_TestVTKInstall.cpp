/**********************************************************************

  文件名: 1.3_TestVTKInstall.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

int main()
{
	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->Render();

	renWin->SetWindowName("TestVTKInstall");
	renWin->SetSize(640, 480);
	renWin->Render();

	std::cin.get();
	return EXIT_SUCCESS;
}
