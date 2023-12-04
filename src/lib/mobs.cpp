#include "mobs.h"
#include "bullet.h"
#include <GL/glut.h>
#include <iostream>

Mob::Mob(float i_x, float i_y, float x_dir, float y_dir) {
    // Initialize mob positions
    x = i_x;
    y = i_y;

    speed = 0.00002; 

    x_direction = x_dir;
    y_direction = y_dir;

    shootCooldown = 100;
}

bool Mob::isAlive() const {
    return health > 0; 
}

void Mob::handleBoundaryBounce(float &position, int &direction, float speed) {
    if (position > 1.0 || position < -1.0) {
        direction = -direction; // Reverse direction
        position += speed * direction; // Move away from the border
    }
    else {
        position += speed * direction; // Continue moving in the current direction
    }
}

void Mob::update(std::vector<Bullet>& bullets) {
    // Add logic to make mobs move automatically
    x += speed * x_direction;
    y += speed * y_direction;

    // Add logic to handle mob boundaries or reset positions if needed
    handleBoundaryBounce(x, x_direction, speed);
    handleBoundaryBounce(y, y_direction, speed);

    // Shooting logic
    // FIXME THEY KILL THEMSELVES CURRENTLY
    if (isAlive() && shootCooldown == 0) {
        bullets.push_back(Bullet(x, y, 0.01, 3.0 * M_PI / 2.0, false)); // Create a new bullet with a downward direction
        shootCooldown = 100; // Reset cooldown
    } else {
        shootCooldown--;
    }
}

void Mob::draw() {
    if (isAlive()) {
        glColor3f(1.0, 0.0, 0.0); // Red color for mob1
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y + 0.1);
        glVertex2f(x - 0.1, y - 0.1);
        glVertex2f(x + 0.1, y - 0.1);
        glEnd();
    }
}