// ======================================================================== //
// Copyright 2009-2014 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include <QtGui>
#include <QGLWidget>
#include <ospray/ospray.h>

struct Viewport
{
  Viewport() : from(0,-1,0),
               at(0,0,0),
               up(0,0,1),
               aspect(1.f),
               fovY(60.f),
               modified(true)
  {
    frame = osp::affine3f::translate(from) * osp::affine3f(embree::one);
  }

  osp::vec3f from;
  osp::vec3f at;
  osp::vec3f up;

  /*! aspect ratio (width / height) */
  float aspect;

  /*! vertical field of view (degrees) */
  float fovY;

  /*! this flag should be set every time the viewport is modified */
  bool modified;

  /*! camera frame in which the Y axis is the depth axis, and X
    and Z axes are parallel to the screen X and Y axis. The frame
    itself remains normalized. */
  osp::affine3f frame;

  /*! set up vector */
  void setUp(const osp::vec3f &vec)
  {
    up = vec;
    snapUp();
    modified = true;
  }

  /*! set frame 'up' vector. if this vector is (0,0,0) the window will
   *not* apply the up-vector after camera manipulation */
  void snapUp()
  {
    if(fabsf(dot(up,frame.l.vz)) < 1e-3f)
      return;

    frame.l.vx = normalize(cross(frame.l.vy,up));
    frame.l.vz = normalize(cross(frame.l.vx,frame.l.vy));
    frame.l.vy = normalize(cross(frame.l.vz,frame.l.vx));
  }
};


class QOSPRayWindow : public QGLWidget
{
public:

  QOSPRayWindow(QMainWindow *parent, OSPRenderer renderer, bool showFrameRate);
  virtual ~QOSPRayWindow();

  void setRenderingEnabled(bool renderingEnabled);
  void setRotationRate(float rotationRate);
  void setBenchmarkParameters(int benchmarkWarmUpFrames, int benchmarkFrames);
  virtual void setWorldBounds(const osp::box3f &worldBounds);

  Viewport * getViewport() { return &viewport; }

  OSPFrameBuffer getFrameBuffer() { return frameBuffer; }

protected:

  /*! Parent Qt window. */
  QMainWindow *parent;

  /*! Display the frame rate in the main window title bar. */
  bool showFrameRate;

  virtual void paintGL();
  virtual void resizeGL(int width, int height);
  virtual void mousePressEvent(QMouseEvent * event);
  virtual void mouseReleaseEvent(QMouseEvent * event);
  virtual void mouseMoveEvent(QMouseEvent * event);

  /*! rotate about center point */
  virtual void rotateCenter(float du, float dv);

  /*! frame counter */
  long frameCount;

  /*! only render when this flag is true. this allows the window to be created before all required components are ospCommit()'d. */
  bool renderingEnabled;

  /*! rotation rate to automatically rotate view. */
  float rotationRate;

  /*! benchmarking: number of warm-up frames */
  int benchmarkWarmUpFrames;

  /*! benchmarking: number of frames over which to measure frame rate */
  int benchmarkFrames;

  /*! benchmarking: timer to measure elapsed time over benchmark frames */
  QTime benchmarkTimer;

  /*! Timer to measure elapsed time over a single frame. */
  QTime renderFrameTimer;

  osp::vec2i windowSize;
  Viewport viewport;
  osp::box3f worldBounds;
  QPoint lastMousePosition;

  OSPFrameBuffer frameBuffer;
  OSPRenderer renderer;
  OSPCamera camera;
};
