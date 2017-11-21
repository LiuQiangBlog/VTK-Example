#**********************************************************************
#
#  Copyright (c) 张晓东, 罗火灵. All rights reserved.
#  更多信息请访问: 
#    http://www.vtkchina.org (VTK中国)
#	  http://blog.csdn.net/www_doling_net (东灵工作室) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Chap07)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(7.1_VolumeRenderingApp 7.1_VolumeRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.1_VolumeRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_MIPVolRenderingApp 7.2_MIPVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_MIPVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_IsoSurfaceVolRenderingApp 7.2_IsoSurfaceVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_IsoSurfaceVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_FixedPointVolRenderingApp 7.2_FixedPointVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_FixedPointVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_GPURayCastingVolRenderingApp 7.2_GPURayCastingVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_GPURayCastingVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_Texture2DVolRenderingApp 7.2_Texture2DVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_Texture2DVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_Texture3DVolRenderingApp 7.2_Texture3DVolRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_Texture3DVolRenderingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_CroppingApp 7.2_CroppingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_CroppingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.2_ClippingApp 7.2_ClippingApp.cpp)
TARGET_LINK_LIBRARIES(7.2_ClippingApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.3_vtkLODProp3DApp 7.3_vtkLODProp3DApp.cpp)
TARGET_LINK_LIBRARIES(7.3_vtkLODProp3DApp ${VTK_LIBRARIES})

ADD_EXECUTABLE(7.4_UnstructuredGridVolumeRenderingApp 7.4_UnstructuredGridVolumeRenderingApp.cpp)
TARGET_LINK_LIBRARIES(7.4_UnstructuredGridVolumeRenderingApp ${VTK_LIBRARIES})

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
