#ifndef COMPUTER_TANK_H
#define COMPUTER_TANK_H
#include "tank.h"
 #include <QGLWidget>
class Computer_Tank : public Tank
{
public:
    Computer_Tank(QString file_name, QString file_name_mtl, QString file_name_barrel, QString file_name_mtl_barrel, QVector3D position);
    ~Computer_Tank();
    void update(float dt, Bullets *bullets, Tank** tanks, int tank_number, int number_of_all_tanks);
};

#endif // COMPUTER_TANK_H
