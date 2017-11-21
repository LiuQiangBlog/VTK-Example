/**********************************************************************

  文件名: vtkDialogDlg.cpp 
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vtkDialog.h"
#include "vtkDialogDlg.h"

#include "vtkCommand.h"
#include "vtkRenderer.h"
#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkPlaneSource.h"
#include "vtkMetaImageReader.h"

#include "vtkImagePlaneWidget.h"
#include "vtkPlaneSource.h" 
#include "vtkPlane.h" 

#include "vtkSmartPointer.h"
#include "vtkResliceCursorActor.h" 
#include "vtkResliceCursorPolyDataAlgorithm.h" 
#include "vtkResliceCursor.h" 
#include "vtkResliceCursorWidget.h" 
#include "vtkResliceCursorLineRepresentation.h" 
#include "vtkResliceCursorThickLineRepresentation.h" 

#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"



//---------------------------------------------------------------------------- 
class vtkResliceCursorCallback : public vtkCommand 
{ 
public: 
	static vtkResliceCursorCallback *New() 
	{ return new vtkResliceCursorCallback; } 

	void Execute( vtkObject *caller, unsigned long /*ev*/, 
		void *callData ) 
	{ 
		/*vtkImagePlaneWidget* ipw = 
			dynamic_cast< vtkImagePlaneWidget* >( caller ); 
		if (ipw) 
		{ 
			double* wl = static_cast<double*>( callData ); 

			if ( ipw == this->IPW[0] ) 
			{ 
				this->IPW[1]->SetWindowLevel(wl[0],wl[1],1); 
				this->IPW[2]->SetWindowLevel(wl[0],wl[1],1); 
			} 
			else if( ipw == this->IPW[1] ) 
			{ 
				this->IPW[0]->SetWindowLevel(wl[0],wl[1],1); 
				this->IPW[2]->SetWindowLevel(wl[0],wl[1],1); 
			} 
			else if (ipw == this->IPW[2]) 
			{ 
				this->IPW[0]->SetWindowLevel(wl[0],wl[1],1); 
				this->IPW[1]->SetWindowLevel(wl[0],wl[1],1); 
			} 
		} */

		vtkResliceCursorWidget *rcw = dynamic_cast< 
			vtkResliceCursorWidget * >(caller); 
		if (rcw) 
		{ 
			for (int i = 0; i < 3; i++) 
			{ 
				vtkPlaneSource *ps = static_cast< vtkPlaneSource * >( 
					view[i]->GetImagePlaneWidget()->GetPolyDataAlgorithm()); 

				ps->SetOrigin(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetOrigin());
				ps->SetPoint1(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint1());
				ps->SetPoint2(view[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint2());

				view[i]->GetImagePlaneWidget()->UpdatePlacement(); 
				view[i]->Render();
			} 

			view3D->Render();
		} 
		
	} 

	vtkResliceCursorCallback() {} 
	CvtkView *view[3];
	CvtkView3D *view3D;
	//CvtkView *view3D;
}; 


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CvtkDialogDlg dialog




CvtkDialogDlg::CvtkDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvtkDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvtkDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_AXIAL, m_AxialView);
	DDX_Control(pDX, IDC_STATIC_SAGITTAL, m_SagittalView);
	DDX_Control(pDX, IDC_STATIC_CORONAL, m_CoronalView);
	DDX_Control(pDX, IDC_STATIC_3D, m_3DView);
	DDX_Control(pDX, IDC_TREE_IMAGE, m_ImageTree);
}

BEGIN_MESSAGE_MAP(CvtkDialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RCLICK, IDC_TREE_IMAGE, &CvtkDialogDlg::OnNMRClickTreeImage)
	ON_NOTIFY(NM_CLICK, IDC_TREE_IMAGE, &CvtkDialogDlg::OnNMClickTreeImage)
	ON_COMMAND(ID_TREE_FILE_OPEN, &CvtkDialogDlg::OnTreeFileOpen)
	ON_COMMAND(ID_TREE_FILE_CLEAR, &CvtkDialogDlg::OnTreeFileClear)
END_MESSAGE_MAP()


// CvtkDialogDlg message handlers

BOOL CvtkDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	//初始化文件树
	m_ImageTreeRoot = m_ImageTree.InsertItem("Images", NULL, NULL);
	m_ImageTree.Expand(m_ImageTreeRoot,TVE_EXPAND); 

	m_AxialView.SetSliceDirection(0);
	m_AxialView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_AxialView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());
	
	m_SagittalView.SetSliceDirection(1);
	m_SagittalView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_SagittalView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());
	m_SagittalView.SetResliceCursor(m_AxialView.GetResliceCursor());

	m_CoronalView.SetSliceDirection(2);
	m_CoronalView.GetImagePlaneWidget()->SetInteractor(m_3DView.GetInteractor());
	m_CoronalView.GetImagePlaneWidget()->SetDefaultRenderer(m_3DView.GetRenderer());
	m_CoronalView.SetResliceCursor(m_AxialView.GetResliceCursor());

	vtkSmartPointer<vtkResliceCursorCallback> cbk = 
		vtkSmartPointer<vtkResliceCursorCallback>::New(); 
	cbk->view[0] = &m_AxialView;
	m_AxialView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk ); 

	cbk->view[1] = &m_SagittalView;
	m_SagittalView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk );

	cbk->view[2] = &m_CoronalView;
	m_CoronalView.GetResliceCursorWidget()->AddObserver( 
		vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk );

	cbk->view3D = &m_3DView;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CvtkDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CvtkDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CvtkDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CvtkDialogDlg::OnNMRClickTreeImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CPoint pt ;//= point;
	GetCursorPos(&pt);
	CPoint ScreenPt = pt;     //Screen coordinates 
	m_ImageTree.ScreenToClient(&pt);      //coordinates in Client Window

	UINT uFlags;
	HTREEITEM hItem = m_ImageTree.HitTest(pt, &uFlags); //Get selected item
	if ((hItem == m_ImageTreeRoot) && (TVHT_ONITEM & uFlags))
	{
		m_ImageTree.SetFocus();
		m_ImageTree.Select(hItem,TVGN_CARET);
		CMenu PopMenu;
		PopMenu.LoadMenu(IDR_MENU_FILE);
		PopMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,ScreenPt.x,ScreenPt.y,this);  
	}

	*pResult = 0;


}

void CvtkDialogDlg::OnNMClickTreeImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here


	CPoint pt ;//= point;
	GetCursorPos(&pt);
	CPoint ScreenPt = pt;     //Screen coordinates 
	m_ImageTree.ScreenToClient(&pt);      //coordinates in Client Window

	UINT uFlags;
	HTREEITEM hItem = m_ImageTree.HitTest(pt, &uFlags); //Get selected item

	if ((hItem  != NULL) && (TVHT_ONITEM & uFlags))
	{
		CString str = m_ImageTree.GetItemText(hItem);   
		m_CoronalView.SetImageData(m_Images[str]);
		m_SagittalView.SetImageData(m_Images[str]);
		m_AxialView.SetImageData(m_Images[str]);
		m_3DView.Invalidate(FALSE);
	}

	*pResult = 0;
}

void CvtkDialogDlg::OnTreeFileOpen()
{
	// TODO: Add your command handler code here
	CString FilePathName;
	vtkSmartPointer<vtkImageData> image = NULL;

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

			image = reader->GetOutput();
			reader->Delete();

			m_Images.insert(make_pair(FilePathName, image));
			HTREEITEM node = m_ImageTree.InsertItem(FilePathName, m_ImageTreeRoot, NULL);
			m_ImageTree.Expand(m_ImageTreeRoot,TVE_EXPAND); 
			m_ImageTree.SetRedraw(TRUE);

	
			m_CoronalView.SetImageData(image);
			m_SagittalView.SetImageData(image);
			m_AxialView.SetImageData(image);
			m_3DView.Render();

		}
		else
		{
			AfxMessageBox("Image Format is not supported now!");
		}
	}
	else
	{
		return;
	}
}

void CvtkDialogDlg::OnTreeFileClear()
{
	// TODO: Add your command handler code here

	//m_tree.Expand(hRoot,TVE_EXPAND); 
}
