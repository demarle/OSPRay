## ======================================================================== ##
## Copyright 2009-2014 Intel Corporation                                    ##
##                                                                          ##
## Licensed under the Apache License, Version 2.0 (the "License");          ##
## you may not use this file except in compliance with the License.         ##
## You may obtain a copy of the License at                                  ##
##                                                                          ##
##     http://www.apache.org/licenses/LICENSE-2.0                           ##
##                                                                          ##
## Unless required by applicable law or agreed to in writing, software      ##
## distributed under the License is distributed on an "AS IS" BASIS,        ##
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ##
## See the License for the specific language governing permissions and      ##
## limitations under the License.                                           ##
## ======================================================================== ##

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ospray/include)

# setup dependencies
SET(LIBS ${LIBS} ospray ospray_fileio)

FIND_PACKAGE(Qt4 REQUIRED) 
SET(QT_USE_QTOPENGL TRUE)
INCLUDE(${QT_USE_FILE})
SET(LIBS ${LIBS} ${QT_LIBRARIES})

FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})
SET(LIBS ${LIBS} ${OPENGL_LIBRARIES})

SET(SRCS ${SRCS}
  main.cpp
  ColorMap.cpp
  LightEditor.cpp
  LinearTransferFunctionWidget.cpp
  PLYGeometryFile.cpp
  QOSPRayWindow.cpp
  SliceWidget.cpp
  TransferFunctionEditor.cpp
  VolumeViewer.cpp
  )

SET(MOC_HEADERS
  LightEditor.h
  LinearTransferFunctionWidget.h
  SliceWidget.h
  TransferFunctionEditor.h
  VolumeViewer.h
  )

QT4_WRAP_CPP(MOC_OUTFILES ${MOC_HEADERS})

ADD_EXECUTABLE(ospVolumeViewer ${SRCS} ${MOC_OUTFILES})
TARGET_LINK_LIBRARIES(ospVolumeViewer ${LIBS})
# ------------------------------------------------------------
INSTALL(TARGETS ospVolumeViewer DESTINATION bin)
# ------------------------------------------------------------

