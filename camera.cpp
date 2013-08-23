#include "camera.h"


Camera::Camera(QVector3D cam_position)
{
    alpha = 0;
    beta = 0.2;
    distance = 1;
    position = cam_position;
    MouseSensitive = 0.0075;
    Cam2D = true;
}
Camera::~Camera()
{

}
void Camera::mousePressEvent(QMouseEvent *event)
{
     lastMousePosition = event->pos();
     event->accept();
}
void Camera::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    if (event->buttons() & Qt::LeftButton)
    {


        if(alpha > 360 || alpha < -360)
        {
            alpha = 0;
        }
        alpha -= deltaX*MouseSensitive;
     lastMousePosition = event->pos();
     }
     event->accept();

}
void Camera::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical)
    {
        if (delta < 0)
        {
            distance *= 1.1;
        } else if (delta > 0)
        {
            distance *= 0.9;
        }
    }
    event->accept();
}
void Camera::keyPressEvent(QKeyEvent* event)
{
    float moveSpeed = 0.1;
    if(event->key() == Qt::Key_W)
    {
        position.setX(position.x()+moveSpeed*sin(alpha));
        position.setZ(position.z()+moveSpeed*cos(alpha));
    }
    if(event->key() == Qt::Key_S)
    {
        position.setX(position.x()-moveSpeed*sin(alpha));
        position.setZ(position.z()+moveSpeed*cos(alpha));
    }
    if(event->key() == Qt::Key_A)
    {
        position.setZ(position.z()+1);
    }
    if(event->key() == Qt::Key_D)
    {
        position.setZ(position.z()-1);
    }
    if(event->key() == Qt::Key_Plus)
    {
        distance *= 0.9;
    }
    if(event->key() == Qt::Key_Minus)
    {
        distance *= 1.1;
    }
}
QMatrix4x4 Camera::CamLookAt()
{
    QMatrix4x4 cameraTransformation;
    QMatrix4x4 vMatrix;
    if(Cam2D)
    {
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);                       //kamera 2D widok z góry jak w gta 2
        QVector3D cameraViev = QVector3D(sin(alpha)*distance*0.5 + position.x(),beta,cos(alpha)*distance*0.5 + position.z());
        vMatrix.lookAt(position + QVector3D(0,distance+5,0), cameraViev, cameraUpDirection);
    }
    else
    {
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);                  //kamera 3D
        QVector3D cameraViev = position;
        vMatrix.lookAt(position-QVector3D(distance*sin(alpha)*distance*0.5,0,distance*cos(alpha)*distance*0.5), cameraViev, cameraUpDirection);
    }
    return vMatrix;
}
void Camera::CamSetyRotate(float yRoate)
{
    alpha = yRoate;
}
void Camera::CamSetPosition(QVector3D pos)
{
    position = pos+QVector3D(0.0,0.9,0.0);
}
