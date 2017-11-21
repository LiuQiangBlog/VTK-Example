/**********************************************************************

  文件名: TransparencySetButton.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#if !defined(AFX_TransparencySetButton_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
#define AFX_TransparencySetButton_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
#include <Afxtempl.h>
#include <vector>
using namespace std;

#define WM_UPDATE_OPACITY_INFO_MSG WM_USER+103
#define WM_UPDATE_OPACITY_VIEW_MSG WM_USER+104

class  CTransparencySetButton : public CButton
{
// Construction
public:
	CTransparencySetButton();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparencySetButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparencySetButton();

	void GetKeyPointPair(std::vector<std::pair<double, double>>& keyPair);
	void SetHistogram(double grayMin, double grayMax, unsigned long *histogram);
	void SetKeyPoint(double gray, double opacity);
	bool GetCurrentKeyPoint(double&gray, double&opacity);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparencySetButton)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void   DrawGrayHistogram(CDC *pDC, CRect &Rc);
	void   DrawTransparencyCurve(CDC *pDC, CRect &Rc);
	int    GetSelectedKeyPointIndex(const CPoint point);

	float GetRelativeBin( double left, double right ) const;
	float GetMaxFreqOfHistogram();


public:
	CArray<CPoint ,CPoint> m_KeyPointSet;

	int  m_KeyPointIndex;		
	bool m_IsLButtonDown;


	unsigned long *m_Histogram;
	double        m_Max;
	double        m_Min;
	double        m_FreqMax;


	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象

	CRect   m_ButtonRect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TransparencySetButton_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
