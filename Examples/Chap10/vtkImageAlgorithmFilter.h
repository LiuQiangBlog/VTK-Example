/**********************************************************************

  文件名: vtkImageAlgorithmFilter.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkImageAlgorithmFilter_h
#define __vtkImageAlgorithmFilter_h

#include "vtkImageAlgorithm.h"

class vtkImageAlgorithmFilter : public vtkImageAlgorithm 
{
public:
	static vtkImageAlgorithmFilter *New();
	vtkTypeMacro(vtkImageAlgorithmFilter,vtkImageAlgorithm);

	vtkImageAlgorithmFilter(){}

protected:
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
	vtkImageAlgorithmFilter(const vtkImageAlgorithmFilter&);  // Not implemented.
	void operator=(const vtkImageAlgorithmFilter&);  // Not implemented.
};

#endif