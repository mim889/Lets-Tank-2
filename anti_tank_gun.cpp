#include "anti_tank_gun.h"

Anti_Tank_Gun::Anti_Tank_Gun():Gun(25,20,true)
{
    fire_speed = 1;
}
Anti_Tank_Gun::~Anti_Tank_Gun()
{

}

void Anti_Tank_Gun::Fire(Bullets * bullets,QVector3D position, float yRoate)
{
    if(timeAfterLastFire > fire_speed)
    {
        bullets->addBullet(position,yRoate,Speed,is_anti_tank,Power);
        timeAfterLastFire = 0;
    }
}
void Anti_Tank_Gun::Update(float dt)
{
    timeAfterLastFire += dt;
}
