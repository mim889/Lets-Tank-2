#include "engine.h"

Engine::Engine()
{
    speed = 0;
    power = 0.2;
    brakeForce = 0.2;
}
Engine::~Engine()
{

}
void Engine::Accelerate()
{
    if(speed < 5 && speed > -5 )
    {
        acceleration = cos(radians(speed))*power;
        speed += acceleration;
    }
}
void Engine::NoGas()
{
    acceleration = -speed*0.01;
    speed += acceleration;
}
void Engine::Brake()
{
    if(speed < 5 && speed > 0 )
    {
        acceleration = cos(radians(speed))*brakeForce;
        speed -= acceleration;
    }
    else if (speed > -5)
    {
        acceleration = cos(radians(speed))*brakeForce*0.3;
        speed -= acceleration;
    }
}

