#include "player.h"
#include "texture.h"
#include <GL/glut.h>

Texture texture;

Player::Player(float initialX, float initialY) : x(initialX), y(initialY), reload(0), health(3) {
    texture.loadPlayerTexture("lib/images/testCannon.png");
}

void Player::update() {
  if (reload != 0)
    --reload;
}

void Player::draw() const {
  texture.drawPlayer(x, y);
}

void Player::handleMouseMotion(int newX, int newY) {
  // Update player position based on mouse coordinates
  x = (newX - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0);
  y = (glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - newY) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
}