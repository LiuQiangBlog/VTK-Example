#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	 http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Chap03)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(3.2_TrianglePoints 3.2_TrianglePoints.cpp)
TARGET_LINK_LIBRARIES(3.2_TrianglePoints ${VTK_LIBRARIES})
 
ADD_EXECUTABLE(3.2_TriangleVertices 3.2_TriangleVertices.cpp)
TARGET_LINK_LIBRARIES(3.2_TriangleVertices ${VTK_LIBRARIES})
 
ADD_EXECUTABLE(3.2_TriangleGeometryLines 3.2_TriangleGeometryLines.cpp)
TARGET_LINK_LIBRARIES(3.2_TriangleGeometryLines ${VTK_LIBRARIES})
 
ADD_EXECUTABLE(3.4_VTKConceptScalars 3.4_VTKConceptScalars.cpp)
TARGET_LINK_LIBRARIES(3.4_VTKConceptScalars ${VTK_LIBRARIES})

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