#ifndef MOB_H
#define MOB_H
#include "player.h"
#include "bullet.h"
#include <vector>
#include <cmath>

class Bullet;

class Mob {
public:
    Mob(float i_x, float i_y, float x_dir, float y_dir);
    void update();

    // Function to draw the game world (including mobs)
    void draw();
    // Add necessary data members for mobs
    float x, y;
    int health = 100;
    float speed;
    float x_direction, y_direction;

    std::vector<Bullet> bullets;
    std::vector<Bullet> bulletBuffer;
    size_t reload;
    
    bool isAlive() const;
    void handleBoundaryBounce(float& coord, float& direction, float speed);
};

#endif // MOBS_H
