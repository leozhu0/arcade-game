#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <iostream>

struct Texture {
  GLuint loadTexture(const char *filename);

  void loadBackgroundTexture(const char *filename);
  void drawBackground(bool isStartScreen);

  void loadPlayerTexture(const char *filename);
  void drawPlayer(float x, float y);

  void loadMobTexture(const char *filename);
  void drawMob(float x, float y);

  static GLuint backgroundTexture; // Declare a texture for the background
  static GLuint playerTexture;     // Declare a texture for the player
  static GLuint mobTexture;        // Declare a texture for the mobs
};
#endif