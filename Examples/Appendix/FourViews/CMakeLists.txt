#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( FourViews )

#----------------------------------------------------------------------------------
FIND_PACKAGE( VTK REQUIRED )
FIND_PACKAGE( Qt4 REQUIRED )

INCLUDE( ${VTK_USE_FILE} )
INCLUDE( ${QT_USE_FILE} )

#----------------------------------------------------------------------------------
SET( PROJECT_SRCS
    main.cpp
    MainWindow.cpp
    vtkSynchronizedView.h
    vtkSynchronizedView.cpp
    vtkOrientationAnnotation.h
    vtkOrientationAnnotation.cpp
    vtkViewImage.h
    vtkViewImage.cpp
    vtkViewImage3D.h
    vtkViewImage3D.cpp
    vtkDataSet3DCroppingPlaneCallback.h
    vtkDataSet3DCroppingPlaneCallback.cpp
    vtkOrientedBoxWidget.h
    vtkOrientedBoxWidget.cpp
    vtkImage3DCroppingBoxCallback.h
    vtkImage3DCroppingBoxCallback.cpp
    vtkViewImage2D.h
    vtkViewImage2D.cpp
    vtkViewImage2DCommand.h
    vtkViewImage2DCommand.cpp
    vtkInteractorStyleImage2D.h
    vtkInteractorStyleImage2D.cpp
    vtkViewImage2DFullCommand.h
    vtkViewImage2DFullCommand.cpp
    vtkImageBlendWithMask.h
    vtkImageBlendWithMask.cpp
    vtkRulerWidget.h
    vtkRulerWidget.cpp
    vtkBorderSelectionWidget.h
    vtkBorderSelectionWidget.cpp
    
    vtkCornerChineseAnnotation.h
    vtkCornerChineseAnnotation.cpp
    vtkFreeTypeUtilitiesUnicode.h
    vtkFreeTypeUtilitiesUnicode.cpp
    vtkFTGLChineseCharacterMapper.h
    vtkFTGLChineseCharacterMapper.cpp
    vtkTextUnicodeProperty.h
    vtkTextUnicodeProperty.cpp
    
    icon.rc
    icon.ico
    resource.h
    )

SET( PROJECT_UIS
    MainWindow.ui
)

SET( PROJECT_MOC_HDRS
  MainWindow.h
)

#----------------------------------------------------------------------------------
QT4_WRAP_UI( PROJECT_UIS_H 
             ${PROJECT_UIS}
           )

QT4_WRAP_CPP( PROJECT_MOC_SRCS 
              ${PROJECT_MOC_HDRS}
            )
 
SET(PROJECT_RCCS resource.qrc)
QT4_ADD_RESOURCES(PROJECT_RCC_SRCS ${PROJECT_RCCS})

#----------------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} 
                     ${CMAKE_CURRENT_BINARY_DIR} 
                     ${VTK_DIR} 
                   )

ADD_EXECUTABLE( FourViews 
                ${PROJECT_SRCS} 
                ${PROJECT_UIS_H} 
                ${PROJECT_MOC_SRCS} 
                ${PROJECT_RCC_SRCS}
              )

TARGET_LINK_LIBRARIES ( FourViews
  ${VTK_LIBRARIES}
  vtkfreetype 
  vtkftgl
  QVTK 
  )

#-----------------------------------------------------------------------------------
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