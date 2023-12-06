#include "mobs.h"
#include "bullet.h"
#include "texture.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
Texture textureMob;

Mob::Mob(float i_x, float i_y, float x_dir, float y_dir) {
    // Initialize mob positions
    x = i_x;
    y = i_y;

    speed = 0.002; 

    x_direction = x_dir;
    y_direction = y_dir;
}

bool Mob::isAlive() const {
    return health > 0; 
}

void Mob::handleBoundaryBounce(float& position, float& direction, float speed) {
    if (position > 1.0 || position < -1.0) {
        direction = -direction; // Reverse direction
        position += speed * direction; // Move away from the border
    }
    else {
        position += speed * direction; // Continue moving in the current direction
    }
}

void Mob::update() {
    // Add logic to make mobs move automatically
    x_direction /= sqrtf(powf(x_direction,2.0) + powf(y_direction,2.0));
    y_direction /= sqrtf(powf(x_direction,2.0) + powf(y_direction,2.0));

    x += speed * x_direction;
    y += speed * y_direction;

    // Add logic to handle mob boundaries or reset positions if needed
    handleBoundaryBounce(x, x_direction, speed);
    handleBoundaryBounce(y, y_direction, speed);

    if (reload != 0) --reload;
    else if (isAlive()) {
        bullets.push_back(Bullet(x, y, 0.04, -1.5707964, 0.005, false));
        bullets.push_back(Bullet(x, y, 0.04, 1.5707964, 0.005, false));
        bullets.push_back(Bullet(x, y, 0.04, 0, 0.005, false));
        bullets.push_back(Bullet(x, y, 0.04, 3.141592, 0.005, false));
        reload = 50;
    }

    // Shooting logic
    // FIXME THEY KILL THEMSELVES CURRENTLY, also segfaults?
    // if (isAlive() && shootCooldown == 0) {
    //     bullets.push_back(Bullet(x, y, 0.01, 3.0 * M_PI / 2.0, false)); // Create a new bullet with a downward direction
    //     shootCooldown = 100; // Reset cooldown
    // } else {
    //     shootCooldown--;
    // }
}

void Mob::draw() {
    if (isAlive()) {
        textureMob.drawMob(x, y);
    }
}