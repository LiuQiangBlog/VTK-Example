#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Chap08)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(8.1_ObserverCommandDemo1 8.1_ObserverCommandDemo1.cpp)
TARGET_LINK_LIBRARIES(8.1_ObserverCommandDemo1 ${VTK_LIBRARIES})
 
ADD_EXECUTABLE(8.1_ObserverCommandDemo2 8.1_ObserverCommandDemo2.cpp)
TARGET_LINK_LIBRARIES(8.1_ObserverCommandDemo2 ${VTK_LIBRARIES})
 
ADD_EXECUTABLE(8.2_InteractionDemo 8.2_InteractionDemo.cpp)
TARGET_LINK_LIBRARIES(8.2_InteractionDemo ${VTK_LIBRARIES})

ADD_EXECUTABLE(8.3_MeasurementWidget 8.3_MeasurementWidget.cpp)
TARGET_LINK_LIBRARIES(8.3_MeasurementWidget ${VTK_LIBRARIES})

ADD_EXECUTABLE(8.3_AnnotationWidget 8.3_AnnotationWidget.cpp)
TARGET_LINK_LIBRARIES(8.3_AnnotationWidget ${VTK_LIBRARIES})

ADD_EXECUTABLE(8.4_PointPicker 8.4_PointPicker.cpp)
TARGET_LINK_LIBRARIES(8.4_PointPicker ${VTK_LIBRARIES})

ADD_EXECUTABLE(8.4_CellPicker 8.4_CellPicker.cpp)
TARGET_LINK_LIBRARIES(8.4_CellPicker ${VTK_LIBRARIES})

ADD_EXECUTABLE(8.4_PropPicker 8.4_PropPicker.cpp)
TARGET_LINK_LIBRARIES(8.4_PropPicker ${VTK_LIBRARIES})

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