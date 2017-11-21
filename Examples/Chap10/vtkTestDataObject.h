/**********************************************************************

  文件名: vtkTestDataObject.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkTestDataObject_h
#define __vtkTestDataObject_h

#include "vtkDataObject.h"

class vtkTestDataObject : public vtkDataObject
{
public:
	static vtkTestDataObject* New();
	vtkTypeMacro(vtkTestDataObject,vtkDataObject);

	void PrintSelf( ostream& os, vtkIndent indent );
	void ShallowCopy(vtkTestDataObject* t);

	vtkGetMacro(Value, double);
	vtkSetMacro(Value, double);

protected:
	vtkTestDataObject();
	~vtkTestDataObject();

private:
	vtkTestDataObject( const vtkTestDataObject& ); // Not implemented.
	void operator = ( const vtkTestDataObject& ); // Not implemented.

	double Value;
};

#endif