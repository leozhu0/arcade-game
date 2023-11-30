#include "player.h"
#include <GL/glut.h>

Player::Player(float initialX, float initialY) : x(initialX), y(initialY) {}

void Player::update() {
    if (reload != 0) --reload;
}

void Player::draw() {
    // Draw player here
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(x - 0.1, y + 0.1);
    glVertex2f(x + 0.1, y + 0.1);
    glVertex2f(x + 0.1, y - 0.1);
    glVertex2f(x - 0.1, y - 0.1);
    glEnd();
}

void Player::handleMouseMotion(int newX, int newY) {
    // Update player position based on mouse coordinates
    x = (newX - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0);
    y = (glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - newY) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
}