/**********************************************************************

  文件名: vtkPolyDataAlgorithmFilter.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkPolyDataAlgorithmFilter : public vtkPolyDataAlgorithm
{
public:
	vtkTypeMacro(vtkPolyDataAlgorithmFilter,vtkPolyDataAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);

	static vtkPolyDataAlgorithmFilter *New();

protected:
	vtkPolyDataAlgorithmFilter(){}
	~vtkPolyDataAlgorithmFilter(){}

	int FillInputPortInformation( int port, vtkInformation* info );
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
	vtkPolyDataAlgorithmFilter(const vtkPolyDataAlgorithmFilter&);  // Not implemented.
	void operator=(const vtkPolyDataAlgorithmFilter&);  // Not implemented.
};

#endif