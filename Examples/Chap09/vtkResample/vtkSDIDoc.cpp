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

#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"

#include "vtkImageWriter.h"
#include "vtkJPEGWriter.h"
#include "vtkBMPWriter.h"
#include "vtkPNGWriter.h"
#include "vtkTIFFWriter.h"
#include "vtkMetaImageWriter.h"

#include "vtkImageResample.h"
#include "vtkImageCast.h"

#include "ResampleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkSDIDoc

IMPLEMENT_DYNCREATE(CvtkSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CvtkSDIDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CvtkSDIDoc::OnFileOpen)
	ON_COMMAND(ID_SIZE_RESAMPLE, &CvtkSDIDoc::OnSizeResample)
	ON_COMMAND(ID_FILE_SAVE, &CvtkSDIDoc::OnFileSave)
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
	m_pImageData = NULL;
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
	m_pImageData = NULL;

	CFileDialog dlg(TRUE, NULL, NULL,
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
					NULL);

	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		
		// Read file
		vtkSmartPointer<vtkImageReader2Factory> readerFactory =
			vtkSmartPointer<vtkImageReader2Factory>::New();
		vtkImageReader2 * reader = readerFactory->CreateImageReader2(FilePathName.GetBuffer(0));
		if (reader)
		{
			reader->SetFileName(FilePathName.GetBuffer(0));
			reader->Update();

			m_pImageData = reader->GetOutput();
			reader->Delete();

			//get the dimension
			int dims[3];
			m_pImageData->GetDimensions(dims);
			m_iDx = dims[0];
			m_iDy = dims[1];
			m_iDz = dims[2];

			//get min and max
			m_Max = m_pImageData->GetScalarRange()[1];
			m_Min = m_pImageData->GetScalarRange()[0];


			UpdateAllViews(0);
		}
		else
		{
			m_pImageData = NULL;
			AfxMessageBox("Image Format is not supported now!");
		}
	}
	else
	{
		return;
	}

}

void CvtkSDIDoc::OnFileSave()
{
	// TODO: Add your command handler code here

	if(m_pImageData == NULL) return;

	CString FilePathName;

	CFileDialog dlg(FALSE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);

	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		m_ImageFormat = FilePathName.Right(FilePathName.GetLength()-FilePathName.ReverseFind('.')-1);
		if(m_ImageFormat == "") m_ImageFormat = "mhd";

		if(m_ImageFormat.Compare("bmp") == 0)
		{
			vtkSmartPointer<vtkBMPWriter> writer = vtkSmartPointer<vtkBMPWriter>::New();
			writer->SetFileName(FilePathName.GetBuffer(0));
			writer->SetInput(m_pImageData);
			writer->Write();
		}

		if(m_ImageFormat.Compare("jpg") == 0)
		{
			vtkSmartPointer<vtkJPEGWriter> writer = vtkSmartPointer<vtkJPEGWriter>::New();
			writer->SetFileName(FilePathName.GetBuffer(0));
			writer->SetInput(m_pImageData);
			writer->Write();
		}

		if(m_ImageFormat.Compare("tif") == 0)
		{
			vtkSmartPointer<vtkTIFFWriter> writer = vtkSmartPointer<vtkTIFFWriter>::New();
			writer->SetFileName(FilePathName.GetBuffer(0));
			writer->SetInput(m_pImageData);
			writer->Write();
		}

		if(m_ImageFormat.Compare("png") == 0)
		{
			vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
			writer->SetFileName(FilePathName.GetBuffer(0));
			writer->SetInput(m_pImageData);
			writer->Write();
		}

		if(m_ImageFormat.Compare("mhd") == 0)
		{
			vtkSmartPointer<vtkMetaImageWriter> writer = vtkSmartPointer<vtkMetaImageWriter>::New();
			writer->SetFileName(FilePathName.GetBuffer(0));
			writer->SetInput(m_pImageData);
			writer->Write();
		}

	}
	else
	{
		return;
	}
}

void CvtkSDIDoc::LoadImage(CString path)
{
	
}

void CvtkSDIDoc::OnSizeResample()
{
	// TODO: Add your command handler code here

	//get dimension and space of original image
	if (m_pImageData == NULL) return;

	int dims[3];
	m_pImageData->GetDimensions(dims);

	double spaces[3];
	m_pImageData->GetSpacing(spaces);

	CResampleDialog dlg(dims[0], dims[1], dims[2], spaces[0], spaces[1], spaces[2]);
	if(dlg.DoModal() == IDOK)
	{
		//get the new dimension and space information
		int dx = dlg.m_iDx;
		int dy = dlg.m_iDy;
		int dz = dlg.m_iDz;

		float sx = dlg.m_fSx;
		float sy = dlg.m_fSy;
		float sz = dlg.m_fSz;

		vtkSmartPointer<vtkImageResample> resample = 
			vtkSmartPointer<vtkImageResample>::New();

		resample->SetInput(m_pImageData);
		resample->SetAxisOutputSpacing(0, sx);
		resample->SetAxisOutputSpacing(1, sy);
		resample->SetAxisOutputSpacing(2, sz);
		resample->SetInterpolationModeToLinear();
		resample->SetInterpolationModeToNearestNeighbor();
		
		vtkSmartPointer<vtkImageCast> imageCast = 
			vtkSmartPointer<vtkImageCast>::New();
		imageCast->SetInput(resample->GetOutput());
		imageCast->SetOutputScalarTypeToUnsignedChar();
		imageCast->Update();


		m_pImageData = NULL;
		m_pImageData = resample->GetOutput();
		UpdateAllViews(0);
	}
}


