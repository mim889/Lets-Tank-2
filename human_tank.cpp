#include "human_tank.h"

Human_Tank::Human_Tank(QString file_name, QString file_name_mtl,QString file_name_barrel, QString file_name_mtl_barrel,QVector3D position):
                       Tank(file_name, file_name_mtl,file_name_barrel, file_name_mtl_barrel, position),CamChangeMode(false)
{
    any_gun = &aTank_Gun;
}
Human_Tank::~Human_Tank()
{

}

void Human_Tank::keyPressEvent(QKeyEvent* event)
{
    bool find = false;                    //zmienna potrzeba do sprawdzania czy klawisz jest na "stosie" klawiszy
    for(int i = 0; i < KeyStack.size();i++)
    {
        if(KeyStack[i]==event->key())
            find = true;
    }
    if(!find) KeyStack << event->key(); //jak klawisza nie ma na "stosie" to go tam wrzucamy
    event->accept();
}
void Human_Tank::keyReleaseEvent(QKeyEvent *event )
{
    int number = 0;
    for(int i = 0; i < KeyStack.size();i++)
    {
        if(KeyStack[i]==event->key())
            number = i;
        if(KeyStack[i] == Qt::Key_F1)
        {
            CamChangeMode = true;
        }
    }
    KeyStack.removeAt(number);        //usuwamy klawisz który został naciśnięty z KeyStack
    event->accept();
}
void Human_Tank::update(float dt, Camera *camera, Model map, Bullets *bullets, Tank **tanks, int tank_number,int number_of_all_tanks)
{
    float tmp_roate = 0;
    float tmp_barrel_roate = 0;
    bool no_key = true;
    if(CamChangeMode)
    {
        camera->Cam2D = !camera->Cam2D;
        CamChangeMode = false;
    }
    if(life >= 0)
    {
        for(int i = 0;i < KeyStack.size();i++)      //przeglądamy wszystkie klawisze po kolei
        {
            if(KeyStack[i] == Qt::Key_W)        //jeśli kalwisz w został naciśnięty to czołg jedzie do przodu
            {
                Accelerate();
                no_key = false;
            }
            if(KeyStack[i] ==  Qt::Key_S)           //jazda do tyłu
            {
                Brake();
                no_key = false;
            }
            if(KeyStack[i] == Qt::Key_A)            //skręt w lewo
            {
                tmp_roate += dt*30;
            }
            if(KeyStack[i] == Qt::Key_D)            //skręt w prawo
            {
                tmp_roate -= dt*30;
            }
            if(KeyStack[i] == Qt::Key_Q)            //skręt lufy w lewo
            {
                tmp_barrel_roate = dt*30;
            }
            if(KeyStack[i] == Qt::Key_E)            //skręt lufy w prawo
            {
                tmp_barrel_roate -= dt*30;
            }
            if(KeyStack[i] == Qt::Key_Shift)            //zmiana broni na przeciw czołgową
            {
                any_gun = &aTank_Gun;
            }
            if(KeyStack[i] == Qt::Key_Tab)            //zmiana broni na przeciw piechocie
            {
                any_gun = &aHuman_Gun;
            }
            if(KeyStack[i] == Qt::Key_Space)
            {
                QVector3D tmp;
                tmp.setX(0*cos(radians(yRoate+yRoateBarrel))-1.5*sin(radians(-yRoate-yRoateBarrel)));
                tmp.setZ(0*sin(radians(yRoate+yRoateBarrel))+1.5*cos(radians(-yRoate-yRoateBarrel)));
                any_gun->Fire(bullets,position+tmp,yRoate+yRoateBarrel);
            }
        }
        any_gun->Update(dt);
        if(no_key)NoGas();
        float dx = speed*sin(radians(yRoate))*dt;      //obliczanie wektorów przesunięcia
        float dz = speed*cos(radians(yRoate))*dt;
        position.setX(position.x() + dx);           //aktualizacja pozycji
        position.setZ(position.z() + dz);
        yRoate += tmp_roate;
        camera->alpha+= radians(tmp_roate);
        Barrel_ChangeYRoate(tmp_barrel_roate);


        bool body_collision = false;            //czy nastąpiła kolizja karoserii czołgu?
        if(Model::CollisionTest(map,position,yRoate))
        {
            position.setX(position.x() - dx);
            position.setZ(position.z() - dz);
            yRoate -= tmp_roate;
            camera->alpha-= radians(tmp_roate);
            body_collision = true;
            speed = 0;
        }
        for(int i = 1; i <  number_of_all_tanks; i++)
        {
            if(Model::CollisionTest(*tanks[i],position-tanks[i]->position,yRoate+180))
            {
                position.setX(position.x() - dx);
                position.setZ(position.z() - dz);
                yRoate -= tmp_roate;
                camera->alpha-= radians(tmp_roate);
                body_collision = true;
                speed = 0;
            }
        }
        if(ModelBarrel->CollisionTest(map,position,yRoateBarrel+yRoate+180))
        {
            if(!body_collision)
            {
                position.setX(position.x() - dx);
                position.setZ(position.z() - dz);
                yRoate -= tmp_roate;
                camera->alpha-= radians(tmp_roate);
                speed = 0;
            }
            Barrel_ChangeYRoate(-tmp_barrel_roate);
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

    if(yRoate < -360 || yRoate > 360)
    {
        yRoate = 0;
    }
}
