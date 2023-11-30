#define GL_SILENCE_DEPRECATION
#include "bullet.h"
#include <GL/glut.h>
#include <cmath>

Bullet::Bullet(float i_x, float i_y, float rad, float dir) : x(i_x), y(i_y), radius(rad), direction(dir) {}

void Bullet::update() {
    // Update player logic here
    x += 0.005 * cosf(direction); 
    y += 0.005 * sin(direction);

    if (std::abs(x) > 1.0 || std::abs(y) > 1.0) needsRemoval = true;
}

void Bullet::draw() {
    // Draw bullet
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);

    int numSegments = 100;

    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float xCircle = radius * cosf(theta);
        float yCircle = radius * sinf(theta);

        glVertex2f(x + xCircle, y + yCircle);
    }

    glEnd();
}

