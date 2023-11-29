#include "mobs.h"
#include <GL/glut.h>
#include <iostream>

Mobs::Mobs() {
    // Initialize mob positions
    mob1_x = 0.0;
    mob1_y = 0.5;

    mob2_x = 0.5;
    mob2_y = -0.5;

    mob3_x = -0.5;
    mob3_y = -0.2;

    mob1_speed = 0.00002; 
    mob2_speed = 0.00004; 
    mob3_speed = 0.00007; 

    mob1_direction_x = 1;
    mob1_direction_y = 1;
    mob2_direction_x = 1;
    mob2_direction_y = -1;
    mob3_direction_x = -1;
    mob3_direction_y = -1;
}

void Mobs::handleBoundaryBounce(float &position, int &direction, float speed) {
    if (position > 1.0 || position < -1.0) {
        direction = -direction; // Reverse direction
        position += speed * direction; // Move away from the border
    }
    else {
        position += speed * direction; // Continue moving in the current direction
    }
}

void Mobs::update() {
    // Add logic to make mobs move automatically
    mob1_x += mob1_speed * mob1_direction_x;
    mob1_y += mob1_speed * mob1_direction_y;

    mob2_x += mob2_speed * mob2_direction_x;
    mob2_y += mob2_speed * mob2_direction_y;

    mob3_x += mob3_speed * mob3_direction_x;
    mob3_y += mob3_speed * mob3_direction_y;

    // Add logic to handle mob boundaries or reset positions if needed
    handleBoundaryBounce(mob1_x, mob1_direction_x, mob1_speed);
    handleBoundaryBounce(mob1_y, mob1_direction_y, mob1_speed);

    handleBoundaryBounce(mob2_x, mob2_direction_x, mob2_speed);
    handleBoundaryBounce(mob2_y, mob2_direction_y, mob2_speed);

    handleBoundaryBounce(mob3_x, mob3_direction_x, mob3_speed);
    handleBoundaryBounce(mob3_y, mob3_direction_y, mob3_speed);
}

void Mobs::draw() {
    // Draw mobs

    // Mob 1 (Red Triangle)
    glColor3f(1.0, 0.0, 0.0); // Red color for mob1
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(mob1_x, mob1_y + 0.1);
    glVertex2f(mob1_x - 0.1, mob1_y - 0.1);
    glVertex2f(mob1_x + 0.1, mob1_y - 0.1);
    glEnd();

    // Mob 2 (Green Triangle)
    glColor3f(0.0, 1.0, 0.0); // Green color for mob2
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(mob2_x, mob2_y + 0.1);
    glVertex2f(mob2_x - 0.1, mob2_y - 0.1);
    glVertex2f(mob2_x + 0.1, mob2_y - 0.1);
    glEnd();

    // Mob 3 (Blue Triangle)
    glColor3f(0.0, 0.0, 1.0); // Blue color for mob3
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(mob3_x, mob3_y + 0.1);
    glVertex2f(mob3_x - 0.1, mob3_y - 0.1);
    glVertex2f(mob3_x + 0.1, mob3_y - 0.1);
    glEnd();

    // Draw name tags
    glColor3f(1.0, 1.0, 1.0); // White color for text

    glRasterPos2f(mob1_x - 0.05, mob1_y + 0.15);
    for (const char *c = "Mob 1"; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }

    glRasterPos2f(mob2_x - 0.05, mob2_y + 0.15);
    for (const char *c = "Mob 2"; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }

    glRasterPos2f(mob3_x - 0.05, mob3_y + 0.15);
    for (const char *c = "Mob 3"; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }
}