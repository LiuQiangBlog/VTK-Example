/**********************************************************************

  文件名: vtkReportProgressFilter.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkReportProgressFilter_h
#define __vtkReportProgressFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkReportProgressFilter : public vtkPolyDataAlgorithm 
{
public:
	vtkTypeMacro(vtkReportProgressFilter,vtkPolyDataAlgorithm);

	static vtkReportProgressFilter *New();

protected:
	vtkReportProgressFilter(){}
	~vtkReportProgressFilter(){}

	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
	vtkReportProgressFilter(const vtkReportProgressFilter&);  // Not implemented.
	void operator=(const vtkReportProgressFilter&);  // Not implemented.
};

#endif