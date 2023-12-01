#define GL_SILENCE_DEPRECATION
#include "mobs.h"
#include <GL/glut.h>
#include <iostream>

Mob::Mob(float i_x, float i_y) {
    // Initialize mob positions
    x = i_x;
    y = i_y;

    speed = 0.002; 

    x_direction = 1;
    y_direction = 1;
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

void Mob::update() {
    // Add logic to make mobs move automatically
    x += speed * x_direction;
    y += speed * y_direction;

    // Add logic to handle mob boundaries or reset positions if needed
    handleBoundaryBounce(x, x_direction, speed);
    handleBoundaryBounce(y, y_direction, speed);
}

void Mob::draw() {
    // Draw mobs

    // Mob 1 (Red Triangle)
    //glColor3f(1.0, 0.0, 0.0); // Red color for mob1
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 0.1);
    glVertex2f(x - 0.1, y - 0.1);
    glVertex2f(x + 0.1, y - 0.1);
    glEnd();
}