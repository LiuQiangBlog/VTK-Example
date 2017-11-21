#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	 http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Chap02)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(2.1_RenderCylinder 2.1_RenderCylinder.cpp)
TARGET_LINK_LIBRARIES(2.1_RenderCylinder ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.2_RenderCylinder-Lights 2.2_RenderCylinder-Lights.cpp)
TARGET_LINK_LIBRARIES(2.2_RenderCylinder-Lights ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.2_TextureExample 2.2_TextureExample.cpp)
TARGET_LINK_LIBRARIES(2.2_TextureExample ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.3_Viewport 2.3_Viewport.cpp)
TARGET_LINK_LIBRARIES(2.3_Viewport ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.4_vtkPipelineDemo 2.4_vtkPipelineDemo.cpp)
TARGET_LINK_LIBRARIES(2.4_vtkPipelineDemo ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.4_vtkPipelineExecute 2.4_vtkPipelineExecute.cpp)
TARGET_LINK_LIBRARIES(2.4_vtkPipelineExecute ${VTK_LIBRARIES})

ADD_EXECUTABLE(2.5_ReferenceCounting 2.5_ReferenceCounting.cpp)
TARGET_LINK_LIBRARIES(2.5_ReferenceCounting ${VTK_LIBRARIES})

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

