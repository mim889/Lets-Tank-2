#include "tank.h"

Tank::Tank(QString file_name, QString file_name_mtl,QString file_name_barrel, QString file_name_mtl_barrel,QVector3D position) :
    Model(file_name,file_name_mtl),Barrel(file_name_barrel,file_name_mtl_barrel),yRoate(0.0),life(100), is_Anti_Tank_Gun_En(true),aHuman_Gun()
  ,aTank_Gun()
{
    this->position = position;

}
Tank::~Tank()
{

}
void Tank::Draw(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QVector3D LightPosition)
{
    QMatrix4x4 mMatrix;                     //macierz model
    mMatrix.translate(position);            //przesuwamy model na tą pozycje na której się aktualnie znajduje
    mMatrix.rotate(yRoate,0.0,1.0,0.0);  //obraca model

    Model::Draw(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);     //rysujemy model czołgu bez lufy
    mMatrix.rotate(yRoateBarrel,0.0,1.0,0.0);
    ModelBarrel->Draw(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);      //rysujemy samą lufę
}

void Tank::update(float dt, Camera *camera, Model map, Bullets *bullets, Tank** tanks, int tank_number, int number_of_all_tanks)
{

}
void Tank::update(float dt, Bullets *bullets, Tank **tanks, int tank_number, int number_of_all_tanks)
{

}
void Tank::keyPressEvent(QKeyEvent* event)
{

}
void Tank::keyReleaseEvent(QKeyEvent *event )
{

}
