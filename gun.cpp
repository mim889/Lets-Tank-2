#include "gun.h"

Gun::Gun(int Power,int Speed,bool is_anti_tank): Power(Power), Speed(Speed),is_anti_tank(is_anti_tank), timeAfterLastFire(0.0)
{
}
Gun::~Gun()
{

}
void Gun::Fire(Bullets * bullets,QVector3D position, float yRoate)
{

}
void Gun::Update(float dt)
{

}
