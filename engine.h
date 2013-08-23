#ifndef ENGINE_H
#define ENGINE_H

#include "helpfun.h"

class Engine
{
public:
    Engine();
    virtual ~Engine();
private:
    float acceleration;
    float power;
    float maxSpeed;
    float brakeForce;

protected:
    void Accelerate();
    void NoGas();
    void Brake();
    float speed;

};

#endif // ENGINE_H
