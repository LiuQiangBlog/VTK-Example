/**********************************************************************

  文件名: ResampleDialog.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "stdafx.h"
#include "vtkSDI.h"
#include "ResampleDialog.h"


// CResampleDialog dialog

IMPLEMENT_DYNAMIC(CResampleDialog, CDialog)

CResampleDialog::CResampleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CResampleDialog::IDD, pParent)
{
	m_iDx = 0;
	m_iDy = 0;
	m_iDz = 0;

	m_fSx = 0;
	m_fSy = 0;
	m_fSz = 0;

	m_bChangeDim = 1;
}

CResampleDialog::CResampleDialog(int dx, int dy, int dz, float sx, float sy, float sz, CWnd* pParent)
	: CDialog(CResampleDialog::IDD, pParent)
{
	m_iDx = dx;
	m_iDy = dy;
	m_iDz = dz;

	m_fSx = sx;
	m_fSy = sy;
	m_fSz = sz;

	m_bChangeDim = 1;
}

CResampleDialog::~CResampleDialog()
{
}

void CResampleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResampleDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CResampleDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CResampleDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_DX, &CResampleDialog::OnEnChangeEditDx)
	ON_EN_CHANGE(IDC_EDIT_SX, &CResampleDialog::OnEnChangeEditSx)
	ON_EN_CHANGE(IDC_EDIT_DY, &CResampleDialog::OnEnChangeEditDy)
	ON_EN_CHANGE(IDC_EDIT_SY, &CResampleDialog::OnEnChangeEditSy)
	ON_EN_CHANGE(IDC_EDIT_DZ, &CResampleDialog::OnEnChangeEditDz)
	ON_EN_CHANGE(IDC_EDIT_SZ, &CResampleDialog::OnEnChangeEditSz)
	ON_BN_CLICKED(IDC_RADIO_DIMENSION, &CResampleDialog::OnBnClickedRadioDimension)
	ON_BN_CLICKED(IDC_RADIO_SPACE, &CResampleDialog::OnBnClickedRadioSpace)
END_MESSAGE_MAP()


// CResampleDialog message handlers

void CResampleDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;

	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	m_iDx = atoi(str);

	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	m_iDy = atoi(str);

	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	m_iDz = atoi(str);

	GetDlgItem(IDC_EDIT_SX)->GetWindowText(str);
	m_fSx = atof(str);

	GetDlgItem(IDC_EDIT_SY)->GetWindowText(str);
	m_fSy = atof(str);

	GetDlgItem(IDC_EDIT_SZ)->GetWindowText(str);
	m_fSz = atof(str);


	OnOK();
}

void CResampleDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

BOOL CResampleDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	str.Format("%d", m_iDx);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);

	str.Format("%d", m_iDy);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);

	str.Format("%d", m_iDz);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);

	str.Format("%.3f", m_fSx);
	GetDlgItem(IDC_EDIT_SX)->SetWindowText(str);

	str.Format("%.3f", m_fSy);
	GetDlgItem(IDC_EDIT_SY)->SetWindowText(str);

	str.Format("%.3f", m_fSz);
	GetDlgItem(IDC_EDIT_SZ)->SetWindowText(str);

	((CButton*)GetDlgItem(IDC_RADIO_DIMENSION))->SetCheck(TRUE);
	UpdateControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CResampleDialog::OnEnChangeEditDx()
{
	// TODO:  Add your control notification handler code here
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	int dx = atoi(str);

	float sx = m_fSx*m_iDx/dx;
	str.Format("%.3f", sx);
	GetDlgItem(IDC_EDIT_SX)->SetWindowText(str);

}

void CResampleDialog::OnEnChangeEditSx()
{
	// TODO:  Add your control notification handler code here
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SX)->GetWindowText(str);
	float sx = atof(str);

	int dx = m_fSx*m_iDx/sx;
	str.Format("%d", dx);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);
}

void CResampleDialog::OnEnChangeEditDy()
{
	// TODO:  Add your control notification handler code here
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	int dy = atoi(str);

	float sy = m_fSy*m_iDy/dy;
	str.Format("%.3f", sy);
	GetDlgItem(IDC_EDIT_SY)->SetWindowText(str);
}

void CResampleDialog::OnEnChangeEditSy()
{
	
	// TODO:  Add your control notification handler code here
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SY)->GetWindowText(str);
	float sy = atof(str);

	int dy = m_fSx*m_iDy/sy;
	str.Format("%d", dy);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);
}

void CResampleDialog::OnEnChangeEditDz()
{
	// TODO:  Add your control notification handler code here
	if(!m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	int dz = atoi(str);

	float sz = m_fSz*m_iDz/dz;
	str.Format("%.3f", sz);
	GetDlgItem(IDC_EDIT_SZ)->SetWindowText(str);
}

void CResampleDialog::OnEnChangeEditSz()
{
	
	// TODO:  Add your control notification handler code here
	if(m_bChangeDim) return;

	CString str;

	GetDlgItem(IDC_EDIT_SZ)->GetWindowText(str);
	float sz = atof(str);

	int dz = m_fSx*m_iDz/sz;
	str.Format("%d", dz);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);
}





void CResampleDialog::OnBnClickedRadioDimension()
{
	// TODO: Add your control notification handler code here
	m_bChangeDim = 1;
	UpdateControl();
}

void CResampleDialog::OnBnClickedRadioSpace()
{
	// TODO: Add your control notification handler code here
	m_bChangeDim = 0;
	UpdateControl();
}

void CResampleDialog::UpdateControl()
{
	if(m_bChangeDim)
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_SX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(TRUE);
	}

	if (m_iDx <= 1) 
	{
		GetDlgItem(IDC_EDIT_DX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SX)->EnableWindow(FALSE);
	}

	if (m_iDy <= 1) 
	{
		GetDlgItem(IDC_EDIT_DY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SY)->EnableWindow(FALSE);
	}
	
	if (m_iDz <= 1) 
	{
		GetDlgItem(IDC_EDIT_DZ)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SZ)->EnableWindow(FALSE);
	}
}