#include "main.h"

void scoreAllianceStake()
{
    arm.move_velocity(600);
    while (true)
    {
        if (armsensor.get_position() > 11650)
        {
            arm.move_velocity(-600);
            break;
        }
    }
    pros::delay(300);
    while (true)
    {
         if (armsensor.get_velocity() > -50)
         {
            arm.move_velocity(0);
            break;
         }
    }
}