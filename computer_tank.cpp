#include "computer_tank.h"

Computer_Tank::Computer_Tank(QString file_name, QString file_name_mtl,QString file_name_barrel, QString file_name_mtl_barrel,QVector3D position):
  Tank(file_name, file_name_mtl,file_name_barrel, file_name_mtl_barrel, position)
{
    any_gun = &aTank_Gun;
}
Computer_Tank::~Computer_Tank()
{

}

void Computer_Tank::update(float dt, Bullets *bullets, Tank **tanks, int tank_number, int number_of_all_tanks)
{

    if(life >= 0)
    {
        any_gun->timeAfterLastFire += dt ;
        yRoateBarrel = degrees(atan((float)(tanks[0]->position.x()-position.x())/(float)(tanks[0]->position.z()-position.z())));
        if(tanks[0]->position.z()-position.z()<0)
        {
            yRoateBarrel +=180;
        }
        float delta_x,delta_z;
        delta_x = (tanks[0]->position.x()-tanks[tank_number]->position.x())*(tanks[0]->position.x()-tanks[tank_number]->position.x());
        delta_z = (tanks[0]->position.z()-tanks[tank_number]->position.z())*(tanks[0]->position.z()-tanks[tank_number]->position.z());
        double distance = sqrt(delta_x+delta_z);
        if(distance < 20)
        {
            QVector3D tmp;
            tmp.setX(0*cos(radians(yRoate+yRoateBarrel))-1.5*sin(radians(-yRoate-yRoateBarrel)));
            tmp.setZ(0*sin(radians(yRoate+yRoateBarrel))+1.5*cos(radians(-yRoate-yRoateBarrel)));
            any_gun->Fire(bullets,position+tmp,yRoate+yRoateBarrel);
        }
    }
    for(int i = 0; i < bullets->bullets.size(); i++)
    {
        if((bullets->bullets[i].is_Anti_Tank && Model::CollisionTest(*bullets->aTank,position-bullets->bullets[i].position,0)) ||
          (!bullets->bullets[i].is_Anti_Tank && Model::CollisionTest(*bullets->aHuman,position-bullets->bullets[i].position,0)))
        {
            if(life >= 0)life-=bullets->bullets[i].damage;
            bullets->bullets.removeAt(i);
        }
    }
}
