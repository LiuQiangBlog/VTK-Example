/**********************************************************************

  文件名: vtkSDIDoc.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkSDIDoc.h : interface of the CvtkSDIDoc class
//


#pragma once

#include "vtkSmartPointer.h"
#include "vtkImageData.h"

class CvtkSDIDoc : public CDocument
{
protected: // create from serialization only
	CvtkSDIDoc();
	DECLARE_DYNCREATE(CvtkSDIDoc)

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
	virtual ~CvtkSDIDoc();
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

public:
	vtkSmartPointer<vtkImageData> m_pImageData;
	virtual void SetTitle(LPCTSTR lpszTitle);
};


