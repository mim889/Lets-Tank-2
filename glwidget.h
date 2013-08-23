#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QTime>
#include <QGLFunctions>

#include "model.h"
#include "camera.h"
#include "human_tank.h"
#include "computer_tank.h"
#include "errorlog.h"
#include "bullets.h"
#include "helpfun.h"

class GlWidget : public QGLWidget, public QGLFunctions
{
    Q_OBJECT

public:
        GlWidget(QWidget *parent = 0);
        ~GlWidget();
        QSize sizeHint() const;

protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent *event);


private:
        void LoadShaderPorgram();
        Camera camera;
        QMatrix4x4 pMatrix;             //macierz projekcji
        QGLShaderProgram shaderProgram;
        QGLShaderProgram lifeBarShaderProgram;
        Model *lifeBar;
        Tank** tanks;
        Model *track;
        Bullets *bullets;
        QTimer *timer;
        QTime dttimer;
        double dt;
        float height,width;
        short int num_tanks;




protected: Q_SLOT
    void timeout();

};

#endif  // GLWIDGET_H
