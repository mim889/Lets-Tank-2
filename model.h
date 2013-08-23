#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QGLShaderProgram>
#include <QGLBuffer>

#include "errorlog.h"
#include "collisionengine.h"

class Model : public CollisionEngine
{
public:
    Model(QString file_name,QString file_name_mtl);
    virtual ~Model();

    virtual void Draw(QGLShaderProgram *shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition);
    void DrawLifeBar(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition,float life);
    QGLBuffer *buffer;

private:
    void Load(QString file_name,QString file_name_mtl);
    unsigned int vertexCount;
};

#endif // MODEL_H
