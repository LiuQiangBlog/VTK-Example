/**********************************************************************

  文件名: GradientColorButton.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// GradientColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "GradientColorButton.h"
#include <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FLAG_HALF_WIDTH 10

/////////////////////////////////////////////////////////////////////////////
// CGradientColorButton

CGradientColorButton::CGradientColorButton()
{
	//左键未按下
	m_IsLButtonDown = false;

	m_ValueColorIndex = -1;
}

CGradientColorButton::~CGradientColorButton()
{
}

BEGIN_MESSAGE_MAP(CGradientColorButton, CButton)
	//{{AFX_MSG_MAP(CGradientColorButton)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientColorButton message handlers

//设置值和颜色表
void CGradientColorButton::SetValueColorTable(CValueColorTable &ValueColorTable)
{
	m_ValueColorTable = ValueColorTable;
	this->Invalidate();
}

//获取值和颜色表
void CGradientColorButton::GetValueColorTable(CValueColorTable &ValueColorTable)
{
	ValueColorTable = m_ValueColorTable;
}

void CGradientColorButton::GetValueColorTable(std::vector<std::vector<double>>& table)
{
	int segNum = m_ValueColorTable.GetSize();
	for (int n = 0; n < segNum; n++)
	{
		long c;
		int r,g,b;
		c = m_ValueColorTable.GetColorAt(n);
		r = (c)&(0x000000FF);
		g = ((c)&(0x0000FF00))>>8;
		b = ((c)&(0x00FF0000))>>16;

		std::vector<double> key;
		key.push_back(m_ValueColorTable.GetValueAt(n));
		key.push_back(r/255.0);
		key.push_back(g/255.0);
		key.push_back(b/255.0);
		table.push_back(key);
	}
}

bool CGradientColorButton::GetCurrentValueColor(double& value, double& r, double& g, double& b)
{
	if(m_ValueColorIndex == -1 || m_ValueColorIndex>=m_ValueColorTable.GetSize()) return false;
	
	value = m_ValueColorTable.GetValueAt(m_ValueColorIndex);

	long c;
	c = m_ValueColorTable.GetColorAt(m_ValueColorIndex);
	r = (c)&(0x000000FF);
	g = ((c)&(0x0000FF00))>>8;
	b = ((c)&(0x00FF0000))>>16;
	
	return 1;
}

void CGradientColorButton::SetTableByValueMinMax(double min, double max)
{
	CValueColorTable table(min, max);
	SetValueColorTable(table);
	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_VIEW_MSG, 0, 0);
}


void CGradientColorButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CGradientColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect Rc= lpDrawItemStruct->rcItem ;

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	MemBitmap.CreateCompatibleBitmap(pDC,Rc.Width(),Rc.Height());

	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);

	//按原来背景填充客户区，不然会是黑色  
	MemDC.FillSolidRect(Rc,RGB(255,255,255));

	if (m_ValueColorTable.GetType() == 0)
		DrawContinusColorTable(pDC, Rc);
	else
		DrawDiscreteColorTable(pDC, Rc);
	

	CBrush frame(RGB(0,0,0));
	pDC->FrameRect(&lpDrawItemStruct->rcItem, &frame);

	//将内存中的图拷贝到屏幕上进行显示
	pDC->BitBlt(0,0,Rc.Width(),Rc.Height(),&MemDC,0,0,SRCCOPY);
	//绘图完成后的清理

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

}

void CGradientColorButton::DrawContinusColorTable(CDC *pDC,CRect &Rc)
{
	int length = Rc.Width();
	float Range = (float)m_ValueColorTable.GetValueRange();

	Rc.right = Rc.left;
	for(int i=0;i<=length;i++){
		COLORREF cr = CalculateColor(length,i);
		CBrush br(cr);
		pDC->FrameRect(&Rc, &br);
		Rc.OffsetRect(1,0);
	}

	//根据值绘制点
	for(int index=0; index<m_ValueColorTable.GetSize(); index++)
	{
		// draw with a thick  pen
		CPen penBlack(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&penBlack);

		// and a solid red brush
		CBrush brushRed(RGB(0, 0, 0));
		CBrush* pOldBrush = pDC->SelectObject(&brushRed);

		double minValue = m_ValueColorTable.GetValueAt(0);
		double curValue = m_ValueColorTable.GetValueAt(index);

		//the vertices of our polygon.
		CPoint pts[1];
		int width,height;
		width=5;
		height=Rc.Height();

		pts[0].x = (LONG)((curValue-minValue)/(Range)*length)-FLAG_HALF_WIDTH/3;
		pts[0].y = 7;

		pDC->Rectangle(pts[0].x,pts[0].y,pts[0].x+width,pts[0].y+height-15);

		// Put back the old objects.
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);

	}
}

void CGradientColorButton::DrawDiscreteColorTable(CDC *pDC, CRect &Rc)
{
	int length = Rc.Width();
	float Range = (float)m_ValueColorTable.GetValueRange()+1;

	Rc.right = Rc.left;
	for(int i=0;i<=length;i++){
		COLORREF cr = CalculateColor(length,i);
		CBrush br(cr);
		pDC->FrameRect(&Rc, &br);
		Rc.OffsetRect(1,0);
	}

	//根据值绘制点
	for(int index=0; index<m_ValueColorTable.GetSize(); index++)
	{
		double minValue  = m_ValueColorTable.GetValueAt(0);
		double curValue  = m_ValueColorTable.GetValueAt(index);

		// draw with a thick  pen
		CPen penBlack(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&penBlack);

		// and a solid red brush
		CBrush brushRed(RGB(255, 255, 255));
		CBrush* pOldBrush = pDC->SelectObject(&brushRed);

		//the vertices of our polygon.
		CPoint pts[3];
		pts[0].x = (LONG)((curValue-minValue)/(Range)*length)-FLAG_HALF_WIDTH/3;
		pts[0].y = 2;

		pts[1].x = (LONG)((curValue-minValue)/(Range)*length)+FLAG_HALF_WIDTH/3;
		pts[1].y = 2;

		pts[2].x = (LONG)((curValue-minValue)/(Range)*length);
		pts[2].y = FLAG_HALF_WIDTH*3;

		// Calling Polygon() on that array will draw three lines
		// between the points, as well as an additional line to
		// close the shape--from the last point to the first point
		// we specified.
		pDC->Polygon(pts, 3);

		// Put back the old objects.
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);

	}
}

long CGradientColorButton::CalculateColor(double Length, double offset)
//根据插值空间的长度Length，偏移量offest计算颜色
{
	if(m_ValueColorTable.GetSize() ==0) return 0;
	if(m_ValueColorTable.GetSize() ==1) return m_ValueColorTable.GetColorAt(0);
	//如果offset越界
	if(offset <= 0 ) return m_ValueColorTable.GetColorAt(0);
	if(offset >= Length ) return m_ValueColorTable.GetColorAt(m_ValueColorTable.GetSize()-1);

	//计算离散颜色表对应的颜色
	if (m_ValueColorTable.GetType() == 1)
	{
		return CalculateDiscreteColor(Length, offset);
	}

	//根据值找到相应的插值段
	int n = m_ValueColorTable.GetSize();
	//得到值的范围
	float Range = (float)m_ValueColorTable.GetValueRange();
	
	for(n=0;n<m_ValueColorTable.GetSize()-1;n++){
		double p  = offset/Length;
		double p1 = m_ValueColorTable.GetOffSetAt(n);
		double p2 = m_ValueColorTable.GetOffSetAt(n+1);
		if(p>=p1 && p<p2) break;
	}

	//此时n表示该偏移在第n段
	//得到n,n+1的颜色
	long c1,c2;
	int r1,r2,g1,g2,b1,b2;

	c1 = m_ValueColorTable.GetColorAt(n);
	c2 = m_ValueColorTable.GetColorAt(n+1);

	r1 = (c1)&(0x000000FF);
	g1 = ((c1)&(0x0000FF00))>>8;
	b1 = ((c1)&(0x00FF0000))>>16;

	r2 = (c2)&(0x000000FF);
	g2 = ((c2)&(0x0000FF00))>>8;
	b2 = ((c2)&(0x00FF0000))>>16;

	//段内偏移
	double offset1 = offset - m_ValueColorTable.GetOffSetAt(n)*Length;
	//计算所在区间长度
	double bin = (m_ValueColorTable.GetOffSetAt(n+1)-m_ValueColorTable.GetOffSetAt(n))*Length;
	double pp = offset1/bin;

	//段内颜色插值
	int r,g,b;
	r = (int)((r2-r1)*pp+r1);
	g = (int)((g2-g1)*pp+g1);
	b = (int)((b2-b1)*pp+b1);

	return RGB(r,g,b);
}

long CGradientColorButton::CalculateDiscreteColor(double Length,double offset)
{
	for(int index=0; index<m_ValueColorTable.GetSize(); index++)
	{
		int left, right;
		left = m_ValueColorTable.GetOffSetAt(index)*Length;
		if (index == m_ValueColorTable.GetSize()-1) right = Length;
		else right =  m_ValueColorTable.GetOffSetAt(index+1)*Length;

		if (offset>left && offset <= right)
			return m_ValueColorTable.GetColorAt(index);
	}

	return 0;
}

double CGradientColorButton::GetPointValue(const CPoint point)
{
	CRect Rc ;
	this->GetClientRect(&Rc);
	int length = Rc.Width();
	double offset = point.x/(double)length;

	return m_ValueColorTable.GetValueAt(0)+offset*m_ValueColorTable.GetValueRange();
}

//得到关键点索引
int  CGradientColorButton::GetSelectedColorIndex(const CPoint point)
{
	if(m_ValueColorTable.GetSize()<=1) return -1;

	CRect Rc ;
	this->GetClientRect(&Rc);
	int length = Rc.Width();

	////离散情况下
	if (m_ValueColorTable.GetType() == 1)
	{
		for(int index=0;index<m_ValueColorTable.GetSize();index++){
			//根据值来判断点的位置
			int pos = (int)(m_ValueColorTable.GetOffSetAt(index)*length);
			if(abs(point.x - pos)<=FLAG_HALF_WIDTH) return index;
		}
		return -1;
	}
	

	/////连续情况
	double curValue = GetPointValue(point);
	//找到值最近的关键点
	int     minClose  = -1;
	double  minDis = 1e10;
	for(int index=0;index<m_ValueColorTable.GetSize();index++){
		double dis = fabs(m_ValueColorTable.GetValueAt(index)-curValue);
		if (dis < minDis && abs(point.x - m_ValueColorTable.GetOffSetAt(index)*length)<=FLAG_HALF_WIDTH)
		{
			minDis	  = dis;
			minClose  = index; 
		}
	}
	return minClose;


}


//鼠标双击为添加和修改关键点
void CGradientColorButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//得到关键点的索引
	m_ValueColorIndex = GetSelectedColorIndex(point);
	if (m_ValueColorIndex == -1) return;

	double value = m_ValueColorTable.GetValueAt(m_ValueColorIndex);
	COLORREF color = RGB(0,0,0);
	CColorDialog cd(color);
	if(cd.DoModal()==IDOK){
		color = cd.GetColor();
		m_ValueColorTable.SetValue( m_ValueColorIndex , value, color );
	}
	this->Invalidate();

	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_VIEW_MSG, 0, 0);
	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_INFO_MSG, 0, 0);

	CButton::OnLButtonDblClk(nFlags, point);
}

void CGradientColorButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//得到关键点的索引
	m_ValueColorIndex = GetSelectedColorIndex(point);

	if (m_ValueColorIndex == -1)
	{
		CRect Rc ;
		GetClientRect(&Rc);
		int Length = Rc.Width();

		//插入点的值和颜色
		double value = m_ValueColorTable.GetValueByOffset((double)point.x/Length);
		long color = CalculateColor(Length,point.x);
		m_ValueColorTable.InsertKeyPoint(value, color);
		this->Invalidate();
	}
	else
	{
		//标志鼠标按下
		m_IsLButtonDown = true;
	}
}

void CGradientColorButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonUp(nFlags, point);

	//左键弹起
	m_IsLButtonDown = false;

	m_ValueColorIndex = GetSelectedColorIndex(point);
	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_VIEW_MSG, 0, 0);
	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_INFO_MSG, 0, 0);
}

void CGradientColorButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnRButtonDown(nFlags, point);

	//找到点的index
	m_ValueColorIndex = GetSelectedColorIndex(point);

	if (m_ValueColorIndex == -1) return;
	if (m_ValueColorIndex == 0)  return;
	if (m_ValueColorIndex == m_ValueColorTable.GetSize()-1) return;


	//删除相应的点
	m_ValueColorTable.DeleteKeyPoint(m_ValueColorIndex);
	this->Invalidate();

	AfxGetMainWnd()->PostMessage(WM_UPDATE_COLOR_VIEW_MSG, 0, 0);
}

//拖动关键点
void CGradientColorButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnMouseMove(nFlags, point);

	//离散情况下不能拖动
	if (m_ValueColorTable.GetType() == 1) return;

	if (m_ValueColorIndex == -1) return;
	if (m_ValueColorIndex == 0)  return;
	if (m_ValueColorIndex == m_ValueColorTable.GetSize()-1) return;
	if (!m_IsLButtonDown) return;

	CRect Rc ;
	GetClientRect(&Rc);
	int Length = Rc.Width();
	float Range = (float)m_ValueColorTable.GetValueRange();

		
	//确保拖动范围内进行
	double p1 = m_ValueColorTable.GetOffSetAt(m_ValueColorIndex-1)*Length;
	double p2 = m_ValueColorTable.GetOffSetAt(m_ValueColorIndex+1)*Length;
	if((point.x-p1 > FLAG_HALF_WIDTH) && (point.x-p2 < FLAG_HALF_WIDTH))
	{
		//计算移动后的值
		float value = (float)(m_ValueColorTable.GetValueAt(0)+(double)point.x/Length*Range);
		m_ValueColorTable.SetKeyPoint(m_ValueColorIndex, value, m_ValueColorTable.GetColorAt(m_ValueColorIndex));
		Invalidate();
	}
}

void CGradientColorButton::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	CButton::OnRButtonDblClk(nFlags, point);

	CMenu menuPopup;
	menuPopup.CreatePopupMenu();

	ClientToScreen(&point);

	int nCmd = ( int ) menuPopup.TrackPopupMenu( (TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD),
		point.x, point.y, this->GetParent());

	switch(nCmd)
	{
// 	case ID_MENUITEM_CONTINUS:
// 		m_ValueColorTable.SetType(0);
// 		break;
// 	case ID_MENUITEM_DISCRETE:
// 		m_ValueColorTable.SetType(1);
// 		break;
// 	default:
// 		break;
	}

	Invalidate();
}
BOOL CGradientColorButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}
