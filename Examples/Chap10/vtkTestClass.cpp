/**********************************************************************

  文件名: vtkTestClass.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkTestClass.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTestClass);

vtkTestClass::vtkTestClass()
{
	Flag = false;

	Speed = 0;

	Position[0] = 0;
	Position[1] = 0;
	Position[2] = 0;

}

vtkTestClass::~vtkTestClass()
{
}

void vtkTestClass::PrintSelf(ostream &os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
	os << "Position: " << Position[0] << " " 
		<< Position[1] << " " 
		<< Position[2] << std::endl
		<< "Speed: "<<Speed<<std::endl
		<< "Flag:"<<Flag<<std::endl;
}