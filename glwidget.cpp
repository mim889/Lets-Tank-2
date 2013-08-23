#include "glwidget.h"
#include <QGLFunctions>
GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(QGLFormat(/* Additional format options */), parent)
{
    timer = new QTimer();
    timer->start(5);
    connect(timer ,SIGNAL(timeout()),this,SLOT(timeout()));
    dttimer = QTime::currentTime();

}
GlWidget::~GlWidget()
{
    delete timer;
    delete lifeBar;
    for(int i = 0; i < num_tanks;i++)
        delete tanks[i];
    delete []tanks;
    delete track;
    delete bullets;
}
QSize GlWidget::sizeHint() const
{

    return QSize(640, 480);
}

void GlWidget::mousePressEvent(QMouseEvent *event)
{
    camera.mousePressEvent(event);
}
void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    camera.mouseMoveEvent(event);
}
void GlWidget::wheelEvent(QWheelEvent *event)
{
    camera.wheelEvent(event);
}
void GlWidget::keyPressEvent(QKeyEvent* event)
{
    tanks[0]->keyPressEvent(event);
}
void GlWidget::keyReleaseEvent(QKeyEvent *event )
{
    tanks[0]->keyReleaseEvent(event);
    camera.keyPressEvent(event);
}

void GlWidget::timeout()
{
    for(int i =1; i < num_tanks;i++)
    {
        tanks[i]->update(dt,bullets,tanks,i,3);    //aktualizujemy czołgi przeciwników
    }
    bullets->update(dt,*track,tanks,3);
    tanks[0]->update(dt,&camera,*track,bullets,tanks,0,3);    //aktualizujemy czołg gracza
    camera.CamSetPosition(tanks[0]->position);                   //ustawianie kamery względem czołgu
    updateGL();
    dt = dttimer.elapsed()/(double)1000;
    dttimer = QTime::currentTime();
}
void GlWidget::LoadShaderPorgram()
{
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "vertexShader.vsh");       //ładowanie i kompilowanie shaderów
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "fragmentShader.fsh");
    shaderProgram.link();
    if(!shaderProgram.isLinked())
    {
        std::string wyjatek = "Shader nie zliknowany poprawnie!";
        throw wyjatek;  //rzucamy wyjątek
    }
    lifeBarShaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "vertexShaderlife.vsh");       //ładowanie i kompilowanie shaderów
    lifeBarShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "fragmentShaderlife.fsh");
    lifeBarShaderProgram.link();
    if(!lifeBarShaderProgram.isLinked())
    {
        std::string wyjatek = "Shader nie zliknowany poprawnie!";
        throw wyjatek;  //rzucamy wyjątek
    }
}


void GlWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);        //włączamy testowanie głębokości
    glEnable(GL_CULL_FACE);         //włączamy obcinanie płaszczyzn tylnych
    glClearColor(0.3,0.7,0.8,1.0);       //ustawiamy czyszczenie bufora koloru na biały kolor
    try
    {
        LoadShaderPorgram();
    }
    catch(std::string str)
    {
        qCritical() << str.c_str();
    }
    track = new Model("models/map.obj","models/map.mtl");
    num_tanks = 3;
    tanks = new Tank*[num_tanks];
    tanks[0] = new Human_Tank("models/tank.obj","models/tank.mtl","models/barrel.obj","models/barrel.mtl",QVector3D(0.0,0.0,0.0));
    tanks[1] = new Computer_Tank("models/Tank1.obj","models/Tank1.mtl","models/barrel1.obj","models/barrel1.mtl",QVector3D(10.0,0.0,50.0));
    tanks[2] = new Computer_Tank("models/Tank1.obj","models/Tank1.mtl","models/barrel1.obj","models/barrel1.mtl",QVector3D(20.0,0.0,21.0));
    bullets = new Bullets;
    lifeBar = new Model("models/lifebar.obj","models/lifebar.mtl");

}
void GlWidget::resizeGL(int width, int height)
{

    if (height == 0)
    {
        height = 1;
    }
    this->height = height;
    this->width = width;
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.1, 1000);     //ustawianie macierzy projekcji
    glViewport(0, 0, width, height);
}
void GlWidget::paintGL()
{
    static double yRot = 0;
    yRot += dt/10;
    QMatrix4x4 mMatrix;                                     //macierz model

    QMatrix4x4 vMatrix= camera.CamLookAt();                 //macierz widoku
    QVector3D LightPosition(sin(yRot)*200,100.0,cos(yRot)*200);                 //obliczamy położenie słońca


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //czyścimy bufor koloru i głębi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    bullets->Draw(&shaderProgram,pMatrix,vMatrix,LightPosition);
    track->Draw(&shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);       //rysujemy teren

    for(int i =0; i < num_tanks;i++)
    {
        QMatrix4x4 mMatrix2;
        tanks[i]->Draw(&shaderProgram,pMatrix,vMatrix,LightPosition);
        if(i !=0)
        {
            mMatrix2.translate(tanks[i]->position);
            mMatrix2.rotate(tanks[i]->yRoate+90,0.0,1.0,0.0);
        }
        else
        {
            mMatrix2.translate(tanks[i]->position);
            mMatrix2.rotate(tanks[i]->yRoate+90,0.0,1.0,0.0);
            mMatrix2.translate(QVector3D(1.0,0.0,0.0));
        }

        lifeBar->DrawLifeBar(&lifeBarShaderProgram, pMatrix,vMatrix, mMatrix2,LightPosition,tanks[i]->life/100.0f);
        renderText(0,36+i*12,QString("zycie z: " + QString::number(tanks[i]->life/100.0f)));
    }
    glDisable(GL_BLEND);


}















