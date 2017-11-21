#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	 http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Chap04)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(4.1_ReadWriteSingleImage 4.1_ReadWriteSingleImage.cpp)
TARGET_LINK_LIBRARIES(4.1_ReadWriteSingleImage ${VTK_LIBRARIES})

ADD_EXECUTABLE(4.1_ReadUnknowFormatImage 4.1_ReadUnknowFormatImage.cpp)
TARGET_LINK_LIBRARIES(4.1_ReadUnknowFormatImage ${VTK_LIBRARIES})

ADD_EXECUTABLE(4.1_ReadSeriesImages1 4.1_ReadSeriesImages1.cpp)
TARGET_LINK_LIBRARIES(4.1_ReadSeriesImages1 ${VTK_LIBRARIES})

ADD_EXECUTABLE(4.1_ReadSeriesImages2 4.1_ReadSeriesImages2.cpp)
TARGET_LINK_LIBRARIES(4.1_ReadSeriesImages2 ${VTK_LIBRARIES})

ADD_EXECUTABLE(4.1_ReadSeriesImages3 4.1_ReadSeriesImages3.cpp)
TARGET_LINK_LIBRARIES(4.1_ReadSeriesImages3 ${VTK_LIBRARIES})

ADD_EXECUTABLE(4.2_Import3DS 4.2_Import3DS.cpp)
TARGET_LINK_LIBRARIES(4.2_Import3DS ${VTK_LIBRARIES})

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