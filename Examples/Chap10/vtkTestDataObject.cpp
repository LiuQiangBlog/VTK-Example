/**********************************************************************

  文件名: vtkTestDataObject.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkTestDataObject.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTestDataObject);

vtkTestDataObject::vtkTestDataObject()
{
	this->Value = 0.0;
}

vtkTestDataObject::~vtkTestDataObject()
{
}

void vtkTestDataObject::PrintSelf( ostream& os, vtkIndent indent )
{
	this->Superclass::PrintSelf( os, indent );
}

void vtkTestDataObject::ShallowCopy(vtkTestDataObject* t)
{
	this->Value = t->GetValue(); 
}