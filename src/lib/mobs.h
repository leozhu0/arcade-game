#ifndef MOB_H
#define MOB_H

#include "player.h"

class Bullet;

class Mob {
public:
    Mob(float i_x, float i_y, float x_dir, float y_dir);
    void update(std::vector<Bullet>& bullets);

    // Function to draw the game world (including mobs)
    void draw();
    // Add necessary data members for mobs
    float x, y;
    int health = 100;
    float speed;
    int x_direction, y_direction;
    int shootCooldown;
    bool isAlive() const;
    void handleBoundaryBounce(float &coord, int &direction, float speed);
};

#endif // MOBS_H
