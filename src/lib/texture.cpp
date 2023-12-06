#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "texture.h"
#include "stb_image.h"



GLuint Texture::backgroundTexture = 1;
GLuint Texture::playerTexture = 1;
GLuint Texture::mobTexture = 1;

GLuint Texture::loadTexture(const char *filename) {
  GLuint textureID;
  int width, height, channels;
  unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);

  if (image) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (channels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    // Set texture parameters
    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(image);

  } else {
    textureID = 5; // Set a default texture ID
  }

  return textureID;
}

void Texture::loadBackgroundTexture(const char *filename) {
  backgroundTexture = loadTexture(filename);
}

void Texture::drawBackground(bool isStartScreen) {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, backgroundTexture);

  glBegin(GL_QUADS);

  if (isStartScreen) {
    glColor3f(0.0, 0.0, 0.0); // Black color for background
  } else {
    glColor3f(1.0, 1.0, 1.0); // White color for background
  }

  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.0, 1.0); // bottom left
  glTexCoord2f(1.0, 0.0);
  glVertex2f(1.0, 1.0); // bottom right
  glTexCoord2f(1.0, 1.0);
  glVertex2f(1.0, -1.0); // top right
  glTexCoord2f(0.0, 1.0);
  glVertex2f(-1.0, -1.0); // top left
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Texture::loadPlayerTexture(const char *filename) {
  playerTexture = loadTexture(filename);
}

void Texture::drawPlayer(float x, float y) {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, playerTexture);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glColor4f(1.0, 1.0, 1.0, 1.0); // White color for background

  glTexCoord2f(0.0, 0.0);
  glVertex2f(x - 0.1, y + 0.1); // bottom left
  glTexCoord2f(1.0, 0.0);
  glVertex2f(x + 0.1, y + 0.1); // bottom right
  glTexCoord2f(1.0, 1.0);
  glVertex2f(x + 0.1, y - 0.1); // top right
  glTexCoord2f(0.0, 1.0);
  glVertex2f(x - 0.1, y - 0.1); // top left
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

void Texture::loadMobTexture(const char *filename) {
  mobTexture = loadTexture(filename);
}

void Texture::drawMob(float x, float y) {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, mobTexture);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glColor4f(1.0, 1.0, 1.0, 1.0); // White color for background

  glTexCoord2f(0.0, 0.0);
  glVertex2f(x - 0.1, y + 0.1); // bottom left
  glTexCoord2f(1.0, 0.0);
  glVertex2f(x + 0.1, y + 0.1); // bottom right
  glTexCoord2f(1.0, 1.0);
  glVertex2f(x + 0.1, y - 0.1); // top right
  glTexCoord2f(0.0, 1.0);
  glVertex2f(x - 0.1, y - 0.1); // top left
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}