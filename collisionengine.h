#ifndef COLLIONENGINE_H
#define COLLIONENGINE_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMatrix4x4>

#include "helpfun.h"

class CollisionEngine
{
public:
    CollisionEngine(QString file_name);
    virtual ~CollisionEngine();
    bool CollisionTest(QVector3D v0, QVector3D v1, QVector3D v2, QVector3D position, float yRoate);
    bool CollisionTest(CollisionEngine eng, QVector3D position1, float yRoate1);
private:
    bool TriangleColision(QVector3D point, QVector3D triangle1, QVector3D triangle2, QVector3D triangle3);
protected:
    QVector <QVector3D> vertices;



};

#endif // COLLIONENGINE_H
