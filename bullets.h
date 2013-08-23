#ifndef BULLETS_H
#define BULLETS_H
#include <QList>
#include <QVector3D>
#include <qmath.h>
#include "model.h"
#include "helpfun.h"
//
class Tank;
struct Bullet
{
   QVector3D position;
   float yRot;
   float speed;
   bool is_Anti_Tank;
   float damage;

};

class Bullets
{
public:
    Bullets();
    ~Bullets();
    void addBullet(QVector3D position, float yRot, float speed, bool is_anty_tank, float damage);
    void update(float dt, CollisionEngine map, Tank **tanks, int num_of_tanks);
    void Draw(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QVector3D LightPosition);
    QList<Bullet> bullets;
    Model *aTank,*aHuman;

};

#endif // BULLETS_H
