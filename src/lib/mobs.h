#ifndef MOB_H
#define MOB_H

#include "player.h"

class Mob {
public:
    Mob(float i_x, float i_y, float x_dir, float y_dir); // Constructor

    // Function to update the game world (including mobs)
    void update();

    // Function to draw the game world (including mobs)
    void draw();
    // Add necessary data members for mobs
    float x, y;
    int health = 100;
    float speed;
    int x_direction, y_direction;

    void handleBoundaryBounce(float &coord, int &direction, float speed);
};

#endif // MOBS_H
