#ifndef ANTI_TANK_GUN_H
#define ANTI_TANK_GUN_H
#include "gun.h"
#include "model.h"
#include "bullets.h"
class Anti_Tank_Gun : public Gun
{
public:
    Anti_Tank_Gun();
    ~Anti_Tank_Gun();
    void Fire(Bullets * bullets,QVector3D position, float yRoate);
    void Update(float dt);
};

#endif // ANTI_TANK_GUN_H
