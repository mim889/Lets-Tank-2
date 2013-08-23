#ifndef HUMAN_TANK_H
#define HUMAN_TANK_H
#include "tank.h"
#include "model.h"
class Human_Tank : public Tank
{
public:
    Human_Tank(QString file_name, QString file_name_mtl,QString file_name_barrel, QString file_name_mtl_barrel,QVector3D position);
    ~Human_Tank();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event );
    void update(float dt, Camera *camera, Model map, Bullets *bullets, Tank** tanks, int tank_number, int number_of_all_tanks);
    QList<int> KeyStack;
private:
    bool CamChangeMode;
};

#endif // HUMAN_TANK_H
