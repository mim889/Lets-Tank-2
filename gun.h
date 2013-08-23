#ifndef GUN_H
#define GUN_H
#include <QVector3D>
#include "bullets.h"
class Gun
{
public:
    Gun(int Power, int Speed, bool is_anti_tank);
    virtual ~Gun();
    void virtual Fire(Bullets * bullets,QVector3D position, float yRoate);
    void virtual Update(float dt);
    double timeAfterLastFire;
protected:
    short int Power;
    short int Speed;
    bool is_anti_tank;
    float fire_speed;
};

#endif // GUN_H
