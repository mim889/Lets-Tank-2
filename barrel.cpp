#include "barrel.h"

Barrel::Barrel(QString file_name,QString file_name_mtl)
{
    ModelBarrel= new Model(file_name,file_name_mtl);
    yRoateBarrel = 0;
}
void Barrel::Barrel_ChangeYRoate(float roate)
{
    yRoateBarrel += roate;
}
Barrel::~Barrel()
{
    delete ModelBarrel;
}
