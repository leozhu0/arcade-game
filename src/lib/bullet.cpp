#include "bullet.h"
#include <GL/glut.h>
#include <cmath>

Bullet::Bullet(float i_x, float i_y, float dir) : x(i_x), y(i_y), direction(dir) {}

void Bullet::update() {
    // Update player logic here
    x += 0.005 * cosf(direction); 
    y += 0.005 * sin(direction);
}

void Bullet::draw() {
    // Draw bullet
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);

    float radius = 0.01;
    int numSegments = 100;

    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float xCircle = radius * cosf(theta);
        float yCircle = radius * sinf(theta);

        glVertex2f(x + xCircle, y + yCircle);
    }

    glEnd();
}

