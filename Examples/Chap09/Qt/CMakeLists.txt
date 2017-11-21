#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( Qt )

#----------------------------------------------------------------------------------
FIND_PACKAGE( VTK REQUIRED )
FIND_PACKAGE( Qt4 REQUIRED )

INCLUDE( ${VTK_USE_FILE} )
INCLUDE( ${QT_USE_FILE} )

#----------------------------------------------------------------------------------
SET( PROJECT_SRCS
    main.cpp
    ProjectMainWindow.cpp
    )

SET( PROJECT_UIS
    ProjectMainWindow.ui
)

SET( PROJECT_MOC_HDRS
  ProjectMainWindow.h
)

#----------------------------------------------------------------------------------
QT4_WRAP_UI( PROJECT_UIS_H 
             ${PROJECT_UIS}
           )

QT4_WRAP_CPP( PROJECT_MOC_SRCS 
              ${PROJECT_MOC_HDRS}
            )

#----------------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} 
                     ${CMAKE_CURRENT_BINARY_DIR} 
                     ${VTK_DIR} 
                   )

ADD_EXECUTABLE( Qt 
                ${PROJECT_SRCS} 
                ${PROJECT_UIS_H} 
                ${PROJECT_MOC_SRCS} 
              )

TARGET_LINK_LIBRARIES ( Qt
  ${VTK_LIBRARIES}
  QVTK 
  )

#-----------------------------------------------------------------------------------------------------------------------------------
# Construct a list of paths containing runtime 
# directories for project applications on Windows
SET(PROJECT_RUNTIME_PATH 
    "${VTK_LIBRARY_DIRS}/@VS_BUILD_TYPE@;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/@VS_BUILD_TYPE@"
    )
IF(QT4_FOUND)
  SET(PROJECT_RUNTIME_PATH "${PROJECT_RUNTIME_PATH};${QT_LIBRARY_DIR}/../bin")
ENDIF()

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