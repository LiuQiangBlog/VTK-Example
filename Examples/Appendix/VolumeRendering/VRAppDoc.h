/**********************************************************************

  文件名: VRAppDoc.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// VRAppDoc.h : interface of the CVRAppDoc class
//


#pragma once
#include "vtkSmartPointer.h"
#include "vtkImageData.h"

class CVRAppDoc : public CDocument
{
protected: // create from serialization only
	CVRAppDoc();
	DECLARE_DYNCREATE(CVRAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CVRAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();

private:
	unsigned long * ComputeFromImageData(vtkSmartPointer<vtkImageData> imgData);


public:
	vtkSmartPointer<vtkImageData> m_pImageData;
	int m_iDx, m_iDy, m_iDz;
	float m_Max, m_Min;
	unsigned long *m_Histogram;

	CString m_ImageFormat;
	virtual void SetTitle(LPCTSTR lpszTitle);
};


