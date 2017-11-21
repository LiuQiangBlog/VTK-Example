/**********************************************************************

  文件名: main.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "MainWindow.h"
#include <QTextCodec>

//程序发布时，可以添加以下语句，运行时就不会带控制台输出窗口
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

int main( int argc, char **argv ) 
{
	QApplication *app = new QApplication(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

	MainWindow window;
	window.show();
	return app->exec();
};

