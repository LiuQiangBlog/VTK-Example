/**********************************************************************

  文件名: vtkTestClass.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkTestClass_h
#define __vtkTestClass_h

#include <vtkObject.h>

class vtkTestClass: public vtkObject
{
public:
	vtkTypeMacro(vtkTestClass,vtkObject);
	static vtkTestClass *New();

	vtkGetMacro(Flag,  bool);
	vtkGetMacro(Speed, double);
	vtkGetVector3Macro(Position,double);

	vtkSetMacro(Flag,bool);
	vtkSetMacro(Speed,double);
	vtkSetVector3Macro(Position,double);

	vtkBooleanMacro(Flag, bool);

	void PrintSelf(ostream &os, vtkIndent indent);

private:
	double Speed;
	double Position[3];
	bool   Flag;

protected:
	vtkTestClass();
	~vtkTestClass();

private:
	vtkTestClass(const vtkTestClass&);  // Not implemented.
	void operator=(const vtkTestClass&);  // Not implemented.

};

#endif