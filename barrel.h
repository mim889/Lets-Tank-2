#ifndef BARREL_H
#define BARREL_H
#include "model.h"

class Barrel
{
public:
    Barrel(QString file_name,QString file_name_mtl);
    ~Barrel();
protected:
    Model *ModelBarrel;
    float yRoateBarrel;
    void Barrel_ChangeYRoate(float roate);
};

#endif // BARREL_H
