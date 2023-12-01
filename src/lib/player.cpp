#define STB_IMAGE_IMPLEMENTATION
#include "player.h"
#include "stb_image.h"
#include <GL/glut.h>

Player::Player(float initialX, float initialY) : x(initialX), y(initialY) {
  // Load image using stb_image
  int width, height, channels;

  // Load image and check for errors
  unsigned char *image = stbi_load("lib/images/testCannon.png", &width, &height, &channels, STBI_rgb);
  if (!image) {
    std::cerr << "Error loading image: " << stbi_failure_reason() << "\n";
    return; // Return or handle the error appropriately
  } else {
    std::cout << "Image loaded successfully. Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n";
  }

  // Create OpenGL texture
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  //glGenerateMipmap(GL_TEXTURE_2Dp

  // Set texture parameters (you can experiment with these)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Free image data
  stbi_image_free(image);
}

void Player::update() {
    if (reload != 0) --reload;
}

void Player::draw() const {
  // Draw player with texture
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glBegin(GL_QUADS);
  glColor3f(1.0, 1.0, 1.0); // Specify color without alpha

  glTexCoord2f(0.0, 0.0);
  glVertex2f(x - 0.1, y + 0.1);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(x + 0.1, y + 0.1);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(x + 0.1, y - 0.1);
  glTexCoord2f(0.0, 1.0);
  glVertex2f(x - 0.1, y - 0.1);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void Player::handleMouseMotion(int newX, int newY) {
  // Update player position based on mouse coordinates
  x = (newX - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0);
  y = (glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - newY) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
}