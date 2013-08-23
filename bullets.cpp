#include "bullets.h"
#include "tank.h"a
Bullets::Bullets()
{
    aTank = new Model("models/bullet.obj","models/bullet.mtl");
    aHuman = new Model("models/human_bullet.obj","models/human_bullet.mtl");
}
Bullets::~Bullets()
{
    delete aTank;
    delete aHuman;
}

void Bullets::addBullet(QVector3D position, float yRot, float speed,bool is_anty_tank, float damage)
{
    Bullet tmp_bullet;
    tmp_bullet.yRot = yRot;
    tmp_bullet.position = position;
    tmp_bullet.speed = speed;
    tmp_bullet.is_Anti_Tank = is_anty_tank;
    tmp_bullet.damage = damage;

    bullets.push_back(tmp_bullet);
}

void Bullets::update(float dt, CollisionEngine map, Tank **tanks,int num_of_tanks)
{
    for(int i = 0; i < bullets.size(); i++)
    {
        float dx =  bullets[i].speed * sin(radians(bullets[i].yRot)) * dt;      //obliczanie wektorów przesunięcia
        float dz =  bullets[i].speed * cos(radians(bullets[i].yRot)) * dt;

        bullets[i].position.setX(bullets[i].position.x() + dx);           //aktualizacja pozycji
        bullets[i].position.setZ(bullets[i].position.z() + dz);
        if((bullets[i].is_Anti_Tank && aTank->CollisionTest(map,bullets[i].position,bullets[i].yRot)) ||
                (!bullets[i].is_Anti_Tank && aHuman->CollisionTest(map,bullets[i].position,bullets[i].yRot)))
        {
                bullets.removeAt(i);
        }
        //for(int j = 0; j < num_of_tanks; j++)
        //{
        //    if(aTank->CollisionTest(*tanks[j],bullets[i].position,bullets[i].yRot))
         //   {
         //        bullets.removeAt(i);
         //   }
       // }

    }

}
void Bullets::Draw(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QVector3D LightPosition)
{


    for(int i = 0; i < bullets.size(); i++)
    {
            QMatrix4x4 mMatrix;
            mMatrix.translate(bullets[i].position);
            mMatrix.rotate(bullets[i].yRot,0.0,1.0,0.0);

            if(bullets[i].is_Anti_Tank )
            {
                aTank->Draw(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);
            }
            else
            {
                aHuman->Draw(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);
            }
    }
}
