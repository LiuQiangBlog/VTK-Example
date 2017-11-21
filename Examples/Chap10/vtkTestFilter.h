/**********************************************************************

  文件名: vtkTestFilter.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include "vtkPolyDataAlgorithm.h"

#define MyEvent (vtkCommand::UserEvent+1)

class vtkTestFilter : public vtkPolyDataAlgorithm
{
public:
	vtkTypeMacro(vtkTestFilter,vtkPolyDataAlgorithm);
	static vtkTestFilter *New();

protected:
	vtkTestFilter();
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
	int m_Value;

private:
	vtkTestFilter(const vtkTestFilter&);  // Not implemented.
	void operator=(const vtkTestFilter&);  // Not implemented.

};
#endif