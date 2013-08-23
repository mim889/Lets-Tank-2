#ifndef TANK_H
#define TANK_H 1

#include <QtCore>
#include <QString>
#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>

#include "model.h"
#include "camera.h"
#include "engine.h"
#include "collisionengine.h"
#include "barrel.h"
#include "bullets.h"
#include "helpfun.h"
#include "gun.h"
#include "anti_human_gun.h"
#include "anti_tank_gun.h"

class Tank : public Engine, public Model, public Barrel
{
public:

    Tank(QString file_name, QString file_name_mtl, QString file_name_barrel, QString file_name_mtl_barrel, QVector3D position);
    virtual ~Tank();
    void Draw(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QVector3D LightPosition);
    QVector3D position;

    void virtual update(float dt, Camera *camera, Model map, Bullets *bullets,Tank** tanks, int tank_number, int number_of_all_tanks);
    void virtual update(float dt, Bullets *bullets, Tank **tanks, int tank_number, int number_of_all_tanks);
    void virtual keyPressEvent(QKeyEvent* event);
    void virtual keyReleaseEvent(QKeyEvent *event );
    float yRoate;
    short int life;
protected:

    Anti_Human_Gun aHuman_Gun;
    Anti_Tank_Gun aTank_Gun;
    bool is_Anti_Tank_Gun_En;
    Gun *any_gun;

};

#endif // TANK_H
