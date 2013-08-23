#include "anti_human_gun.h"

Anti_Human_Gun::Anti_Human_Gun():Gun(10,25,false)
{
    fire_speed = 0.5;
}
Anti_Human_Gun::~Anti_Human_Gun()
{

}
void Anti_Human_Gun::Fire(Bullets * bullets,QVector3D position, float yRoate)
{
    if(timeAfterLastFire > fire_speed)
    {
        bullets->addBullet(position,yRoate,Speed,is_anti_tank,Power);
        timeAfterLastFire = 0;
    }

}
void Anti_Human_Gun::Update(float dt)
{
    timeAfterLastFire += dt;
}
