#ifndef CAMERA_H
#define CAMERA_H

#include <QtOpenGL>
#include <QVector3D>
#include <QMatrix4x4>
#include <QWidget>
#include <QEvent>
#include "helpfun.h"

class Camera
{
public:
    Camera(QVector3D cam_position = QVector3D(0.0f,0.0f,0.0f));
    ~Camera();
    QMatrix4x4 CamLookAt();
    void CamSetPosition(QVector3D pos);
    void CamSetyRotate(float yRoate);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent* event);
    double alpha;
    bool Cam2D;
private:
    QVector3D position;
    double beta;
    double distance;
    double MouseSensitive;
    QPoint lastMousePosition;


protected:


};


#endif // CAMERA_H
