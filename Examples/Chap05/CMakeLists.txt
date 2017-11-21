#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Chap05)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(5.1_ImageCanvasSource2D 	5.1_ImageCanvasSource2D.cpp)
TARGET_LINK_LIBRARIES(5.1_ImageCanvasSource2D ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.1_CreateVTKImageData	5.1_CreateVTKImageData.cpp)
TARGET_LINK_LIBRARIES(5.1_CreateVTKImageData ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.2_DisplayImageExample	5.2_DisplayImageExample.cpp)
TARGET_LINK_LIBRARIES(5.2_DisplayImageExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.2_DisplayImageExample2	5.2_DisplayImageExample2.cpp)
TARGET_LINK_LIBRARIES(5.2_DisplayImageExample2 ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.2_ImageBlendExample	5.2_ImageBlendExample.cpp)
TARGET_LINK_LIBRARIES(5.2_ImageBlendExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_GetImageInformationExample	5.3_GetImageInformationExample.cpp)
TARGET_LINK_LIBRARIES(5.3_GetImageInformationExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageChangeInformationExample	5.3_ImageChangeInformationExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageChangeInformationExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_VisitImagePixelDirectlyExample	5.3_VisitImagePixelDirectlyExample.cpp)
TARGET_LINK_LIBRARIES(5.3_VisitImagePixelDirectlyExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_VisitImagePixelIterativelyExample	5.3_VisitImagePixelIterativelyExample.cpp)
TARGET_LINK_LIBRARIES(5.3_VisitImagePixelIterativelyExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageCastExample	5.3_ImageCastExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageCastExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.3_Color2GrayImageExample	5.3_Color2GrayImageExample.cpp)
TARGET_LINK_LIBRARIES(5.3_Color2GrayImageExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageExtractComponentsExample	5.3_ImageExtractComponentsExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageExtractComponentsExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.3_Gray2ColorImageExample	5.3_Gray2ColorImageExample.cpp)
TARGET_LINK_LIBRARIES(5.3_Gray2ColorImageExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.3_ImageAppendComponentsExample	5.3_ImageAppendComponentsExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageAppendComponentsExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ExtractVOIExample	5.3_ExtractVOIExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ExtractVOIExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageResliceExample	5.3_ImageResliceExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageResliceExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.3_ImageResliceExample2	5.3_ImageResliceExample2.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageResliceExample2 ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageAccumulateExample	5.3_ImageAccumulateExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageAccumulateExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.3_ImageAccumulateExample2	5.3_ImageAccumulateExample2.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageAccumulateExample2 ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageShrink3DExample	5.3_ImageShrink3DExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageShrink3DExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageShrinkMagnifyExample	5.3_ImageShrinkMagnifyExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageShrinkMagnifyExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageMathematicsExample	5.3_ImageMathematicsExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageMathematicsExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageLogicExample	5.3_ImageLogicExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageLogicExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.3_ImageBinaryExample	5.3_ImageBinaryExample.cpp)
TARGET_LINK_LIBRARIES(5.3_ImageBinaryExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.4_ImageGradientExample	5.4_ImageGradientExample.cpp)
TARGET_LINK_LIBRARIES(5.4_ImageGradientExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.4_SobelExample	5.4_SobelExample.cpp)
TARGET_LINK_LIBRARIES(5.4_SobelExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.4_CannyExample	5.4_CannyExample.cpp)
TARGET_LINK_LIBRARIES(5.4_CannyExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.4_LaplacianExample	5.4_LaplacianExample.cpp)
TARGET_LINK_LIBRARIES(5.4_LaplacianExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.5_MeanFilterExample	5.5_MeanFilterExample.cpp)
TARGET_LINK_LIBRARIES(5.5_MeanFilterExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.5_GaussianFilterExample	5.5_GaussianFilterExample.cpp)
TARGET_LINK_LIBRARIES(5.5_GaussianFilterExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.5_MedianFilterExample	5.5_MedianFilterExample.cpp)
TARGET_LINK_LIBRARIES(5.5_MedianFilterExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.5_AnistropicFilteringExample	5.5_AnistropicFilteringExample.cpp)
TARGET_LINK_LIBRARIES(5.5_AnistropicFilteringExample ${VTK_LIBRARIES})	

ADD_EXECUTABLE(5.6_FFTAndRFFTExample	5.6_FFTAndRFFTExample.cpp)
TARGET_LINK_LIBRARIES(5.6_FFTAndRFFTExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.6_IdealLowPassExample	5.6_IdealLowPassExample.cpp)
TARGET_LINK_LIBRARIES(5.6_IdealLowPassExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.6_ButterworthLowPassExample	5.6_ButterworthLowPassExample.cpp)
TARGET_LINK_LIBRARIES(5.6_ButterworthLowPassExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.6_IdealHighPassExample	5.6_IdealHighPassExample.cpp)
TARGET_LINK_LIBRARIES(5.6_IdealHighPassExample ${VTK_LIBRARIES})
	
ADD_EXECUTABLE(5.6_ButterworthHighPassExample	5.6_ButterworthHighPassExample.cpp)
TARGET_LINK_LIBRARIES(5.6_ButterworthHighPassExample ${VTK_LIBRARIES})

#-----------------------------------------------------------------------------------------------------------------------------------
# Construct a list of paths containing runtime directories for project applications on Windows.
# Create two batch files which correctly set up the environment for the application and for Visual Studio.
IF(WIN32)
  SET(PROJECT_RUNTIME_PATH "${VTK_DIR}/bin/@VS_BUILD_TYPE@")
  INCLUDE(CreateWindowsBatchScript.cmake)
  SET(VS_SOLUTION_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sln")
  FOREACH(VS_BUILD_TYPE Debug Release)
    CreateWindowsBatchScript("${CMAKE_SOURCE_DIR}/StartVS.bat.in"
      ${PROJECT_BINARY_DIR}/StartVS_${VS_BUILD_TYPE}.bat
      ${VS_BUILD_TYPE})
  ENDFOREACH()
ENDIF(WIN32)