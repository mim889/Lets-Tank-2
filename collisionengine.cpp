#include "collisionengine.h"
#include <QVector2D>
#include <QtCore/qmath.h>
#define PI 3.14159265359
CollisionEngine::CollisionEngine(QString file_name)
{
    QString bufor;  //bufor do danych z QTextStream plików tekstowych
    QVector <QVector3D> vertices_tmp;       //tymczasowe wierzchołki
    QVector <QVector3D> triangles;          // w piliku obj jest f nr.wierzchołek/nr.tekstura/nr.normalna dlatego QVector3D.x to położenie, QVector3D.y to kolor, QVector3D.z to wektor normalny
    bool ColisionRead = false;

    QFile file(file_name);                         //otwieranie pliku *.obj
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream txtstr(&file);

    if(!file.isReadable())
    {
        qWarning() << "nie mozna czytac z pliku " << file_name;
    }
    while(!txtstr.atEnd())              //czytanie pliku obj
    {
        txtstr >> bufor;
        if(bufor == "v" && bufor != "vt" )                 //trafiliśmy na v czyli wczytujemy wierzchołek
        {
            QVector3D tmp_vec;
            float tmp_data;

            txtstr >> tmp_data;
            tmp_vec.setX(tmp_data);

            txtstr >> tmp_data;
            tmp_vec.setY(tmp_data);

            txtstr >> tmp_data;
            tmp_vec.setZ(tmp_data);

            vertices_tmp << tmp_vec;

        }
        else if(bufor == "f" && ColisionRead)        //trójkąty np 1/2/3 4/5/6 7/8/9 oznacza że wierzchołki trójkąta to 1,4,7 wektory teksturowe to 2,5,8, wektory normalne to 3,6,9
        {
            int tmp_data;
            QVector3D tmp_vec;
            char div;  // znak "/"

            for(int i =0;i<3;i++)
            {
                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setX(tmp_data);

                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setY(tmp_data);

                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setZ(tmp_data);
                triangles << tmp_vec;

            }

        }
        else if(bufor == "usemtl")
        {
            txtstr >> bufor;
            if(bufor == "Collision" || bufor == "Colision" )
            {
                ColisionRead = true;
            }
            else
            {
               ColisionRead = false;
            }
        }
        else
        {
            txtstr.readLine();
        }

    }
    for(int i =0; i < triangles.size();i++)         //finalne tworzenie "zbiorów" wierzchołków, kolorów wierzchołków, wektorów tekstur, wektorów normalnych
    {
        vertices << vertices_tmp[triangles[i].x()-1];
    }

    file.close();           //zamykamy pliki *.obj

}

CollisionEngine::~CollisionEngine()
{

}

bool CollisionEngine::TriangleColision(QVector3D point, QVector3D triangle1, QVector3D triangle2, QVector3D triangle3)
{
    double total_angles = 0.0f;
    QVector3D v1,v2,v3;

    v1.setX(point.x()-triangle1.x());       //algorytm sprawdzania czy punkt leży w trójkącie czy poza nim
    v1.setY(0);
    v1.setZ(point.z()-triangle1.z());

    v2.setX(point.x()-triangle2.x());
    v2.setY(0);
    v2.setZ(point.z()-triangle2.z());

    v3.setX(point.x()-triangle3.x());
    v3.setY(0);
    v3.setZ(point.z()-triangle3.z());

    v1.normalize();
    v2.normalize();
    v3.normalize();
    total_angles += qAcos(QVector3D::dotProduct(v1,v2));
    total_angles += qAcos(QVector3D::dotProduct(v2,v3));
    total_angles += qAcos(QVector3D::dotProduct(v3,v1));

    if (fabs(total_angles-2*PI) <= 0.0005)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CollisionEngine::CollisionTest(QVector3D v0, QVector3D v1, QVector3D v2, QVector3D position, float yRoate)
{
    QVector3D vec;
    for(int i = 0; i < vertices.size(); i ++)
    {
        vec = vertices[i];
        vec.setX(vertices[i].x()*cos(radians(yRoate))-vertices[i].z()*sin(radians(yRoate)));
        vec.setZ(vertices[i].x()*sin(radians(yRoate))+vertices[i].z()*cos(radians(yRoate)));
        vec += position;
        if(TriangleColision(vec, v0, v1, v2))
        {
            return true;

        }
    }
    return false;
}

bool CollisionEngine::CollisionTest(CollisionEngine eng, QVector3D position, float yRoate)
{
    for(int i = 0; i < eng.vertices.size();i+=3)
    {
        if(CollisionTest(eng.vertices[i],eng.vertices[i+1],eng.vertices[i+2],position,yRoate))
        {
            return true;
        }
    }
    return false;
}

