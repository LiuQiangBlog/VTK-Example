/**********************************************************************

  文件名: vtkBorderSelectionWidget.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkBorderSelectionWidget.h"

vtkStandardNewMacro(vtkBorderSelectionWidget);

vtkBorderSelectionWidget::vtkBorderSelectionWidget()
{
	this->CallbackMapper->SetCallbackMethod(vtkCommand::MiddleButtonReleaseEvent,
		vtkWidgetEvent::EndSelect,
		this, vtkBorderSelectionWidget::EndSelectAction);
}

void vtkBorderSelectionWidget::EndSelectAction(vtkAbstractWidget *w)
{
	vtkBorderWidget *borderWidget =
		vtkBorderWidget::SafeDownCast(w);

	// Get the actual box coordinates/planes
	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();

	// Get the bottom left corner
	double* lowerLeft;
	lowerLeft = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition();
	std::cout << "Lower left: " << lowerLeft[0] << " "
		<< lowerLeft[1] << std::endl;

	double* upperRight;
	upperRight = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition2();
	std::cout << "Upper right: " << upperRight[0] << " "
		<< upperRight[1] << std::endl;

	vtkBorderWidget::EndSelectAction(w);
}