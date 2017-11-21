# VTK-Example
VTK图形图像开发进阶里面的例子程序
## 第1章：概述部分
简单显示了一个VTK窗口，学习[CMakeLists.txt](https://github.com/GHAUOA/VTK-Example/blob/master/Examples/Chap01/CMakeLists.txt)的脚本写法
## 第2章：VTK的基本概念
[一个稍微复杂的VTK程序](https://github.com/GHAUOA/VTK-Example/blob/master/Examples/Chap02/2.1_RenderCylinder.cpp)

当我们去看舞台剧的时候，我们坐在台下，展现在我们面前的是一个舞台，舞台上有各式的灯光，各样的演员。演员出场的时候肯定是会先化妆，有些演员可能会打扮成高富帅，有些演员可能会化妆成白富美。观众有时还会与台上的演员有一定的互动。
整个剧院就好比VTK程序的渲染窗口(vtkRenderWindow)；舞台就相当于渲染场景(vtkRenderer)；而那些高富帅、白富美就是我们程序中的Actor(有些文献翻译成“演员”，有些翻译成“角色”，这里我们不作翻译)；台上的演员与台下观众的互动可以看成是程序的交互(vtkRenderWindowInteractor)；演员与观众的互动方式有很多种，现场的观众可以直接上台跟演员们握手拥抱，电视机前的可以发短信，电脑、移动终端用户等可以微博关注、加粉等等，这就好比我们程序里的交互器样式(vtkInteractorStyle)；舞台上的演员我们都能一一分辨出来，不会把高富帅弄混淆，是因为他们化的妆、穿的服饰都不一样，这就相当于我们程序里vtkActor的不同属性(vtkProperty)；台下观众的眼睛可以看作是vtkCamera，前排的观众因为离得近，看台上演员会显得比较高大，而后排的观众看到的会显得小点，每个观众看到的东西在他的世界里都是唯一的，所以渲染场景Renderer里的vtkCamera对象也是只有一个；舞台上的灯光可以有多个，所以渲染场景里的vtkLight也存在多个。可以参考下图，加深理解：

![图片](http://img.blog.csdn.net/20161116172359845)

[VTK光照vtkLight](https://github.com/GHAUOA/VTK-Example/blob/master/Examples/Chap02/2.2_RenderCylinder-Lights.cpp)


