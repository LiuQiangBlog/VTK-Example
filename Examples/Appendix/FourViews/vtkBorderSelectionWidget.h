/**********************************************************************

  文件名: vtkBorderSelectionWidget.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef _vtkBorderSelectionWidget_h_
#define _vtkBorderSelectionWidget_h_

#include "vtkBorderWidget.h"
#include "vtkBorderRepresentation.h"
#include "vtkWidgetCallbackMapper.h"
#include "vtkSmartPointer.h"
#include "vtkCommand.h"
#include "vtkWidgetEvent.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"

class vtkBorderSelectionWidget : public vtkBorderWidget
{
public:
  static vtkBorderSelectionWidget *New();
  vtkTypeMacro(vtkBorderSelectionWidget, vtkBorderWidget);
 
  static void EndSelectAction(vtkAbstractWidget *w);
 
  vtkBorderSelectionWidget();
};

#endif /* _vtkBorderSelectionWidget_h_ */