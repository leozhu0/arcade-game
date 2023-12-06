#include "bullet.h"
#include <GL/glut.h>
#include <cmath>

Bullet::Bullet(float i_x, float i_y, float rad, float dir, float i_speed, bool playerBullet)
    : x(i_x), y(i_y), radius(rad), direction(dir), speed(i_speed), needsRemoval(false), belongsToPlayer(playerBullet) {}

void Bullet::update() {
    x += speed * cosf(direction);
    y += speed * sinf(direction);

    if (std::abs(x) > 1.0 || std::abs(y) > 1.0) {
        needsRemoval = true; // Set the flag to true when the bullet is out of bounds
    }
}

void Bullet::draw() {
    // Draw bullet
    glBegin(GL_POLYGON);
    if (belongsToPlayer) {
        glColor3f(1.0, 1.0, 1.0); // Set color for player bullets
    } else {
        glColor3f(1.0, 0.0, 0.0); // Set color for other bullets
    }

    int numSegments = 100;

    // Circle calculations
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float xCircle = radius * cosf(theta);
        float yCircle = radius * sinf(theta);

        glVertex2f(x + xCircle, y + yCircle);
    }

    glEnd();
}