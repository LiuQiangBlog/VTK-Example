/**********************************************************************

  文件名: GradientColorButton.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#if !defined(AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
#define AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GradientColorButton.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CGradientColorButton window
#include <Afxtempl.h>

#include "ValueColorTable.h"

#define WM_UPDATE_COLOR_INFO_MSG WM_USER+100
#define WM_UPDATE_COLOR_VIEW_MSG WM_USER+101

class  CGradientColorButton : public CButton
{
// Construction
public:
	CGradientColorButton();
	//设置值和颜色表
	void SetValueColorTable(CValueColorTable &ValueColorTable);
	//获取值和颜色表
	void GetValueColorTable(CValueColorTable &ValueColorTable);
	void GetValueColorTable(std::vector<std::vector<double>>& table);
	void SetTableByValueMinMax(double min, double max);
	bool GetCurrentValueColor(double& value, double& r, double& g, double& b);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradientColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGradientColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGradientColorButton)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	//根据插值空间的长度Length，偏移量offest计算颜色
	long   CalculateColor(double Length,double offset);
	long   CalculateDiscreteColor(double Length,double offset);
	int    GetSelectedColorIndex(const CPoint point);
	double GetPointValue(const CPoint point);

	void   DrawContinusColorTable(CDC *pDC, CRect &Rc);
	void   DrawDiscreteColorTable(CDC *pDC, CRect &Rc);

	//值和颜色表
	CValueColorTable m_ValueColorTable; 
	//鼠标按下时，关键点的索引
	int  m_ValueColorIndex;				 
	//判断鼠标左键是否按下	
	bool m_IsLButtonDown;

	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象

	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
