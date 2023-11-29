#ifndef MOBS_H
#define MOBS_H

#include "player.h"

class Mobs {
public:
    Mobs(); // Constructor

    // Function to update the game world (including mobs)
    void update();

    // Function to draw the game world (including mobs)
    void draw();

private:
    // Add necessary data members for mobs
    float mob1_x, mob1_y;
    float mob2_x, mob2_y;
    float mob3_x, mob3_y;
    
    float mob1_speed, mob2_speed, mob3_speed;
    int mob1_direction_x, mob1_direction_y;
    int mob2_direction_x, mob2_direction_y;
    int mob3_direction_x, mob3_direction_y;

    void handleBoundaryBounce(float &coord, int &direction, float speed);
};

#endif // MOBS_H