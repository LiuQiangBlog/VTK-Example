#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT( Chap06 )
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(6.1_PolyDataSource 6.1_PolyDataSource.cpp)
TARGET_LINK_LIBRARIES(6.1_PolyDataSource ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.1_PolyDataNew 6.1_PolyDataNew.cpp)
TARGET_LINK_LIBRARIES(6.1_PolyDataNew ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.1_PolyDataColor 6.1_PolyDataColor.cpp)
TARGET_LINK_LIBRARIES(6.1_PolyDataColor ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.1_PolyDataAttribute 6.1_PolyDataAttribute.cpp)
TARGET_LINK_LIBRARIES(6.1_PolyDataAttribute ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.2_PolyDataMassProperty 6.2_PolyDataMassProperty.cpp)
TARGET_LINK_LIBRARIES(6.2_PolyDataMassProperty ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.2_PolyDataGeodesic 6.2_PolyDataGeodesic.cpp)
TARGET_LINK_LIBRARIES(6.2_PolyDataGeodesic ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.2_PolyDataBoundingBox 6.2_PolyDataBoundingBox.cpp)
TARGET_LINK_LIBRARIES(6.2_PolyDataBoundingBox ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.2_PolyDataNormal 6.2_PolyDataNormal.cpp)
TARGET_LINK_LIBRARIES(6.2_PolyDataNormal ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.2_PolyDataCurvature 6.2_PolyDataCurvature.cpp)
TARGET_LINK_LIBRARIES(6.2_PolyDataCurvature ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.3_PolyDataLapLasianSmooth 6.3_PolyDataLapLasianSmooth.cpp)
TARGET_LINK_LIBRARIES(6.3_PolyDataLapLasianSmooth ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.4_PolyDataClosed 6.4_PolyDataClosed.cpp)
TARGET_LINK_LIBRARIES(6.4_PolyDataClosed ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.5_PolyDataConnectedCompExtract 6.5_PolyDataConnectedCompExtract.cpp)
TARGET_LINK_LIBRARIES(6.5_PolyDataConnectedCompExtract ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.5_PolyDataConnectedAllCompExtract 6.5_PolyDataConnectedAllCompExtract.cpp)
TARGET_LINK_LIBRARIES(6.5_PolyDataConnectedAllCompExtract ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.6_PolyDataDecimation 6.6_PolyDataDecimation.cpp)
TARGET_LINK_LIBRARIES(6.6_PolyDataDecimation ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.6_PolyDataSubdivision 6.6_PolyDataSubdivision.cpp)
TARGET_LINK_LIBRARIES(6.6_PolyDataSubdivision ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.7_PolyDataDelaunay2D 6.7_PolyDataDelaunay2D.cpp)
TARGET_LINK_LIBRARIES(6.7_PolyDataDelaunay2D ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.7_PolyDataConstrainedDelaunay2D 6.7_PolyDataConstrainedDelaunay2D.cpp)
TARGET_LINK_LIBRARIES(6.7_PolyDataConstrainedDelaunay2D ${VTK_LIBRARIES})

ADD_EXECUTABLE(6.7_PolyDataMarchingCubes 6.7_PolyDataMarchingCubes.cpp)
TARGET_LINK_LIBRARIES(6.7_PolyDataMarchingCubes ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.7_PolyDataSurfaceReconstruction 6.7_PolyDataSurfaceReconstruction.cpp)
TARGET_LINK_LIBRARIES(6.7_PolyDataSurfaceReconstruction ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.8_PolyDataLandmarkReg 6.8_PolyDataLandmarkReg.cpp)
TARGET_LINK_LIBRARIES(6.8_PolyDataLandmarkReg ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.8_PolyDataICP 6.8_PolyDataICP.cpp)
TARGET_LINK_LIBRARIES(6.8_PolyDataICP ${VTK_LIBRARIES}) 

ADD_EXECUTABLE(6.9_TextureMap 6.9_TextureMap.cpp)
TARGET_LINK_LIBRARIES(6.9_TextureMap ${VTK_LIBRARIES}) 

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