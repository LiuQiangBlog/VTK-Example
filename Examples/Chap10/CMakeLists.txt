#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT( Chap10 )
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(VTK_LIBS ${VTK_LIBRARIES} vtkRendering vtkGraphics vtkHybrid vtkIO vtkFiltering vtkCommon vtkImaging)
 
ADD_EXECUTABLE( 10.1_vtkTest  10.1_vtkTest.cpp)
TARGET_LINK_LIBRARIES(10.1_vtkTest ${VTK_LIBS})


ADD_EXECUTABLE( 10.1_ObserverTest  10.1_ObserverTest.cpp 
                      vtkTestFilter.h 
                      vtkTestFilter.cpp )
TARGET_LINK_LIBRARIES(10.1_ObserverTest ${VTK_LIBS})

ADD_EXECUTABLE( 10.1_ClassTest  10.1_ClassTest.cpp 
                      vtkTestClass.h 
                      vtkTestClass.cpp )
TARGET_LINK_LIBRARIES(10.1_ClassTest ${VTK_LIBS})

ADD_EXECUTABLE( 10.3_ReportProgressFilterTest  10.3_ReportProgressFilterTest.cpp 
                      vtkReportProgressFilter.h 
                      vtkReportProgressFilter.cpp )
TARGET_LINK_LIBRARIES(10.3_ReportProgressFilterTest ${VTK_LIBS})

ADD_EXECUTABLE( 10.3_AlgorithmFilterTest  10.3_AlgorithmFilterTest.cpp 
                      vtkTestDataObject.h
                      vtkTestDataObject.cpp
                      vtkAlgorithmFilter.h 
                      vtkAlgorithmFilter.cpp )
TARGET_LINK_LIBRARIES(10.3_AlgorithmFilterTest ${VTK_LIBS})

ADD_EXECUTABLE( 10.3_ImageAlgorithmFilterTest  10.3_ImageAlgorithmFilterTest.cpp 
                     vtkImageAlgorithmFilter.h 
                     vtkImageAlgorithmFilter.cpp )
TARGET_LINK_LIBRARIES(10.3_ImageAlgorithmFilterTest ${VTK_LIBS})

ADD_EXECUTABLE( 10.3_PolyDataAlgorithmFilterTest  10.3_PolyDataAlgorithmFilterTest.cpp 
                      vtkPolyDataAlgorithmFilter.h 
                      vtkPolyDataAlgorithmFilter.cpp )
TARGET_LINK_LIBRARIES(10.3_PolyDataAlgorithmFilterTest ${VTK_LIBS})


 
#----------------------------------------------------------------------------------------------------------------------------
SET(PROJECT_RUNTIME_PATH 
    "${VTK_LIBRARY_DIRS}/@VS_BUILD_TYPE@;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/@VS_BUILD_TYPE@" )

INCLUDE(CreateWindowsBatchScript.cmake)

# If we are under Windows, create two batch files which correctly
# set up the environment for the application and for Visual Studio
if(WIN32)
  set(VS_SOLUTION_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sln")
  foreach(VS_BUILD_TYPE debug release)
    CreateWindowsBatchScript("${CMAKE_SOURCE_DIR}/StartVS.bat.in"
      ${PROJECT_BINARY_DIR}/StartVS_${VS_BUILD_TYPE}.bat
      ${VS_BUILD_TYPE})
  endforeach()
endif(WIN32)