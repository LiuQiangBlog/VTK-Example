#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(vtkDisplayChinese)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET( vtkDisplayChinese_SRC
  vtkDisplayChinese.cpp 
  vtkFTGLChineseCharacterMapper.cpp
  vtkFTGLChineseCharacterMapper.h
  vtkFreeTypeUtilitiesUnicode.cpp
  vtkFreeTypeUtilitiesUnicode.h
  vtkTextUnicodeProperty.cpp
  vtkTextUnicodeProperty.h
)

ADD_EXECUTABLE( vtkDisplayChinese ${vtkDisplayChinese_SRC} )

TARGET_LINK_LIBRARIES(vtkDisplayChinese ${VTK_LIBRARIES} vtkfreetype vtkftgl)

SET(PROJECT_RUNTIME_PATH 
    "${VTK_LIBRARY_DIRS}/@VS_BUILD_TYPE@;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/@VS_BUILD_TYPE@"
    )

INCLUDE(CreateWindowsBatchScript.cmake)

# If we are under Windows, create two batch files which correctly
# set up the environment for the application and for Visual Studio
IF(WIN32)
  SET(VS_SOLUTION_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sln")
  FOREACH(VS_BUILD_TYPE debug release)
    CreateWindowsBatchScript("${CMAKE_SOURCE_DIR}/StartVS.bat.in"
      ${PROJECT_BINARY_DIR}/StartVS_${VS_BUILD_TYPE}.bat
      ${VS_BUILD_TYPE})
  ENDFOREACH()
ENDIF(WIN32)