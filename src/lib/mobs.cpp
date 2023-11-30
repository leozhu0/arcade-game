#define GL_SILENCE_DEPRECATION
#include "mobs.h"
#include <GL/glut.h>
#include <iostream>

Mob::Mob(float i_x, float i_y) {
    // Initialize mob positions
    x = i_x;
    y = i_y;

    speed = 0.00002; 

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
    glColor3f(1.0, 0.0, 0.0); // Red color for mob1
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 0.1);
    glVertex2f(x - 0.1, y - 0.1);
    glVertex2f(x + 0.1, y - 0.1);
    glEnd();

    // // Mob 2 (Green Triangle)
    // glColor3f(0.0, 1.0, 0.0); // Green color for mob2
    // glBegin(GL_TRIANGLE_FAN);
    // glVertex2f(mob2_x, mob2_y + 0.1);
    // glVertex2f(mob2_x - 0.1, mob2_y - 0.1);
    // glVertex2f(mob2_x + 0.1, mob2_y - 0.1);
    // glEnd();

    // // Mob 3 (Blue Triangle)
    // glColor3f(0.0, 0.0, 1.0); // Blue color for mob3
    // glBegin(GL_TRIANGLE_FAN);
    // glVertex2f(mob3_x, mob3_y + 0.1);
    // glVertex2f(mob3_x - 0.1, mob3_y - 0.1);
    // glVertex2f(mob3_x + 0.1, mob3_y - 0.1);
    // glEnd();

    // // Draw name tags
    // glColor3f(1.0, 1.0, 1.0); // White color for text

    // glRasterPos2f(mob1_x - 0.05, mob1_y + 0.15);
    // for (const char *c = "Mob 1"; *c != '\0'; c++) {
    //     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    // }

    // glRasterPos2f(mob2_x - 0.05, mob2_y + 0.15);
    // for (const char *c = "Mob 2"; *c != '\0'; c++) {
    //     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    // }

    // glRasterPos2f(mob3_x - 0.05, mob3_y + 0.15);
    // for (const char *c = "Mob 3"; *c != '\0'; c++) {
    //     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    // }
}