#include "helpfun.h"

float degrees(float radian )            //funkcja zamieniająca kąt w radnianach na stopnie
{
    return ( 180*radian ) / 3.14159265359;
}


float radians(float degrees )       //funkcja zamieniająca kąt w stopniach na radiany
{
    return ( 3.14159265359*degrees ) / 180;
}
