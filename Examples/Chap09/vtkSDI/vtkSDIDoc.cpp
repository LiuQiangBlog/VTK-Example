/**********************************************************************

  文件名: vtkSDIDoc.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkSDIDoc.cpp : implementation of the CvtkSDIDoc class
//

#include "stdafx.h"
#include "vtkSDI.h"

#include "vtkSDIDoc.h"

#include "vtkJPEGReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkSDIDoc

IMPLEMENT_DYNCREATE(CvtkSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CvtkSDIDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CvtkSDIDoc::OnFileOpen)
END_MESSAGE_MAP()


// CvtkSDIDoc construction/destruction

CvtkSDIDoc::CvtkSDIDoc()
{
	// TODO: add one-time construction code here
	m_pImageData = vtkSmartPointer<vtkImageData>::New();
	m_pImageData = NULL;

}

CvtkSDIDoc::~CvtkSDIDoc()
{
}

BOOL CvtkSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CvtkSDIDoc serialization

void CvtkSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CvtkSDIDoc diagnostics

#ifdef _DEBUG
void CvtkSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvtkSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvtkSDIDoc commands

void CvtkSDIDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CString FilePathName;

	CFileDialog dlg(TRUE, NULL, NULL,
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"),
					NULL);

	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();

		vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
		reader->SetFileName(FilePathName.GetBuffer(0));
		reader->Update();

		m_pImageData = reader->GetOutput();

		UpdateAllViews(0);

	}
	else
	{
		return;
	}

}

void CvtkSDIDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(lpszTitle);
}
