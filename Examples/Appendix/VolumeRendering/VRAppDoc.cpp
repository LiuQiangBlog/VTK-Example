/**********************************************************************

  文件名: VRAppDoc.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// VRAppDoc.cpp : implementation of the CVRAppDoc class
//

#include "stdafx.h"
#include "VRApp.h"
#include "MainFrm.h"

#include "VRAppDoc.h"
#include "VRAppView.h"
#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"
#include "vtkImageShiftScale.h"
#include "vtkDoubleArray.h"
#include "vtkImageResample.h"
#include "vtkImageCast.h"
#include "vtkPointData.h"
#include "vtkMetaImageWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVRAppDoc

IMPLEMENT_DYNCREATE(CVRAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CVRAppDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CVRAppDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CVRAppDoc::OnFileSave)
END_MESSAGE_MAP()


// CVRAppDoc construction/destruction

CVRAppDoc::CVRAppDoc()
{
	// TODO: add one-time construction code here
	m_Histogram = 0;

}

CVRAppDoc::~CVRAppDoc()
{
	if(m_Histogram) delete m_Histogram;
	m_Histogram = 0;
}

BOOL CVRAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CVRAppDoc serialization

void CVRAppDoc::Serialize(CArchive& ar)
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


// CVRAppDoc diagnostics

#ifdef _DEBUG
void CVRAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVRAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVRAppDoc commands
void CVRAppDoc::OnFileOpen()
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

			vtkSmartPointer<vtkImageData> image = reader->GetOutput();
			reader->Delete();

			if(image->GetNumberOfScalarComponents() != 1)
			{
				AfxMessageBox("Only gray images are supported!");
				return;
			}
			//get the dimension
			int dims[3];
			image->GetDimensions(dims);
			m_iDx = dims[0];
			m_iDy = dims[1];
			m_iDz = dims[2];

			if(m_iDz <= 1)
			{
				AfxMessageBox("Two few slices!");
				return;
			}

			m_Min = image->GetScalarRange()[0];
			m_Max = image->GetScalarRange()[1];

			vtkSmartPointer<vtkImageShiftScale> imageShiftScale =
				vtkSmartPointer<vtkImageShiftScale>::New();
			imageShiftScale->SetInput(image);
			imageShiftScale->SetOutputScalarTypeToUnsignedChar();
			imageShiftScale->SetScale(255.0/(m_Max-m_Min));
			imageShiftScale->SetShift(m_Min);
			imageShiftScale->Update();

			m_pImageData = imageShiftScale->GetOutput();
			m_Histogram  = ComputeFromImageData(m_pImageData);

			vtkSmartPointer<vtkMetaImageWriter> writer = 
				vtkSmartPointer<vtkMetaImageWriter>::New();
			writer->SetInput(m_pImageData);
			writer->SetFileName("test.mhd");
			writer->Write();
			//update min and max
			m_Min = m_pImageData->GetScalarRange()[0];
			m_Max = m_pImageData->GetScalarRange()[1];;

			//更新VRToolBar控件
			((CMainFrame*)AfxGetMainWnd())->m_ToolBar.InitControls();

			//更新视图
			CView* pView = ((CMainFrame*)AfxGetMainWnd())->GetActiveView();
			((CVRAppView*)pView)->SetInput();
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

void CVRAppDoc::OnFileSave()
{
	// TODO: Add your command handler code here
}

unsigned long * CVRAppDoc::ComputeFromImageData(vtkSmartPointer<vtkImageData> imgData)
{
	
	unsigned long * histogram;
	
	int first = -32768;// support at least full signed and unsigned short range
	int last = 65535;

	
	int typInt=0;	
	{
		const char *typ = imgData->GetScalarTypeAsString();
		if (strcmp("unsigned char",typ) == 0){ typInt = 0;  }
		else if (strcmp("signed char",typ) == 0){ typInt = 1;  }
		else if (strcmp("unsigned short",typ) == 0){ typInt = 2;  }
		else if (strcmp("signed short",typ) == 0 ){ typInt = 3;  }
		else if (strcmp("float",typ) == 0 ){ typInt = 4;}
		else if (strcmp("short",typ) == 0 ){ typInt = 5;}
		else
		{
			AfxMessageBox("Histogram calculate currently only surpports un/signed char/short");
			return NULL;
		}
	}

	histogram = new unsigned long[65535+32768+1];

	for (unsigned long i = 0; i < 65535+1+32768; i++)
	{
		histogram[i] = 0;
	}

	unsigned int num = 1;
	int dim[3] = {1};
	imgData->GetDimensions(dim);
	num = dim[0]*dim[1]*dim[2];

	void *src = imgData->GetScalarPointer();

	do 
	{
		int value;

		switch(typInt)
		{
		case 0: { unsigned char *t = (unsigned char *)src; value = *t++; src = (void*)t;}break;
		case 1: { signed char *t = (signed char *)src; value = *t++; src = (void*)t;}break;
		case 2: { unsigned short *t = (unsigned short *)src; value = *t++; src = (void*)t;}break;
		case 3: { signed short *t = (signed short *)src; value = *t++; src = (void*)t;}break;
		case 4: { float *t = (float*)src; value = *t++; src = (void*)t;}break;
		case 5: { short *t = (short*)src; value = *t++; src = (void*)t;}break;
		}

		if (value >= first && value <= last )
		{
			histogram[value-first]++;
		}
	} while (--num);
	
	return histogram;
}
void CVRAppDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle("东灵工作室");
}
