#ifndef ANTI_HUMAN_GUN_H
#define ANTI_HUMAN_GUN_H
#include "gun.h"
#include "model.h"
#include "bullets.h"
class Anti_Human_Gun : public Gun
{
public:
    Anti_Human_Gun();
    ~Anti_Human_Gun();
    void Fire(Bullets * bullets,QVector3D position, float yRoate);
    void Update(float dt);

};

#endif // ANTI_HUMAN_GUN_H
