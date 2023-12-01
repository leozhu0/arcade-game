#define GL_SILENCE_DEPRECATION
#ifndef MOB_H
#define MOB_H

#include "player.h"

class Mob {
public:
    Mob(float i_x, float i_y); // Constructor

    // Function to update the game world (including mobs)
    void update();

    // Function to draw the game world (including mobs)
    void draw();

private:
    // Add necessary data members for mobs
    float x, y;
    
    float speed;
    int x_direction, y_direction;

    void handleBoundaryBounce(float &coord, int &direction, float speed);
};

#endif // MOBS_H