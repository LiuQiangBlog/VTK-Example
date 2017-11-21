/**********************************************************************

  文件名: VRToolBar.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#pragma once

#include "resource.h"
#include "TransparencySetButton.h"
#include "GradientColorButton.h"
// CVRToolBar dialog

class CVRToolBar : public CDialogBar
{
	DECLARE_DYNAMIC(CVRToolBar)

public:
	CVRToolBar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVRToolBar();

// Dialog Data
	enum { IDD = IDD_VR_TOOLBAR };

	//更新控件
	void InitControls();

	void UpdateOpacityInfo(double gray, double opacity);
	void UpdateColorInfo(double gray);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg /*LONG*/LRESULT OnInitDialog ( /*UINT*/WPARAM , /*LONG*/LPARAM  );
	afx_msg void OnUpdateButton(CCmdUI * pCmdUI); //响应button按钮

	DECLARE_MESSAGE_MAP()

public:
	CGradientColorButton   m_VolumeColor;
	CTransparencySetButton m_VolumeOpacity;
	afx_msg void OnEnChangeOpacityValue();
};
