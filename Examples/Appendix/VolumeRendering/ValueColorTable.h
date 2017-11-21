/**********************************************************************

  文件名: ValueColorTable.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#pragma once

#include <afxtempl.h>
#include <vector>

using namespace std;

class  CValueColorTable
{
public:
	CValueColorTable(void);
	CValueColorTable(double min, double max);
	//拷贝构造函数
	CValueColorTable(const CValueColorTable &ValueColorTable);

public:
	~CValueColorTable(void);
public:
	// 加载缺省设置
	void LoadDefaultColorTable();
	//初始化
	void SetValueColorTable(CArray<double,double> &values, CArray<long,long> &colors);
	void SetValueColorTable(CValueColorTable Source);
	//赋值运算符
	CValueColorTable& operator=(CValueColorTable &ValueColorTable);
	//获取值数组和颜色数组
	void GetValueColorTable(CArray <double, double> &values, CArray <long, long> &colors);
	//得到值的范围
	double GetValueRange();
	//得到关键点的偏移量
	double GetOffSetAt(int index);
	//获取关键点数
	int GetSize();
	//获取关键点的值和颜色
	double GetValueAt(int index);
	long   GetColorAt(int index);
	//得到最小最大值
	void   GetValueMinMax(double &min, double &max);
	//根据偏移获取值
	double GetValueByOffset(double offset);
	//添加关键点
	void AddKeyPoint(double value, long color);
	//插入关键点
	void InsertAt(int index, double value, long color);
	//插入一个关键点，根据值自动找到相应的位置
	void InsertKeyPoint(double value, long color);
	//设置关键点
	void SetKeyPoint(int index, double value, long color);
	//删除一个关键点
	void DeleteKeyPoint(int index);
	//清空
	void RemoveAll();
	//值与颜色转换
	int GetColorByValue(double value, Color &color);
	
	
	BOOL SetValue( int, double, long );
	
	void displayValue();

	BOOL getColorValuePosition(vector<double> &, vector<long> &, vector<double> & );

	BOOL getColorPosition( vector<double> & );

	BOOL SetMinMaxKeyPointFollow( double, double );
	BOOL setMinMaxKeyPoint( double, double );

	//设置颜色表类型
	void SetType(int iType);
	int  GetType();

private:
	CArray<long ,long>  m_Colors;   //渐变颜色的数组
	CArray<double,double> m_Values; //值

	int m_iType;
};
