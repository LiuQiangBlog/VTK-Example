/**********************************************************************

  文件名: vtkDialogDlg.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// vtkDialogDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "vtkView.h"
#include "vtkView3D.h"
#include "vtkImageData.h"

#include <map>
#include <string> 
using namespace std;

// CvtkDialogDlg dialog
class CvtkDialogDlg : public CDialog
{
// Construction
public:
	CvtkDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VTKDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnNMRClickTreeImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTreeImage(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CTreeCtrl m_ImageTree;

	CvtkView   m_AxialView;
	CvtkView   m_SagittalView;
	CvtkView   m_CoronalView;
	CvtkView3D m_3DView;
	//CvtkView   m_3DView;


	HTREEITEM m_ImageTreeRoot;
	std::map<CString, vtkSmartPointer<vtkImageData> > m_Images;
	afx_msg void OnTreeFileOpen();
	afx_msg void OnTreeFileClear();
};
