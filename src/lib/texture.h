#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <iostream>

struct Texture {
  GLuint loadTexture(const char *filename);
  static GLuint backgroundTexture; // Declare a texture for the background
  void loadBackgroundTexture(const char *filename);
  void drawBackground(bool isStartScreen);

  static GLuint playerTexture; // Declare a texture for the player
  void loadPlayerTexture(const char *filename);
  void drawPlayer(float x, float y);
};
#endif