#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "stb_image.h"

GLuint Texture::backgroundTexture = 0;
GLuint Texture::playerTexture = 0;

GLuint Texture::loadTexture(const char *filename) {
  GLuint textureID;
  int width, height, channels;
  unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);

  if (image) {
    std::cout << "Image loaded successfully: " << filename << " Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n"; // FIXME REMOVE LATER
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (channels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    // Set texture parameters
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    // Assign the textureID to the static member variable
    backgroundTexture = textureID;
  } else {
    // Handle error loading image
    std::cerr << "Error loading texture: " << filename << std::endl;
    std::cerr << "STB Image Error: " << stbi_failure_reason() << std::endl;
    textureID = 0; // Set a default texture ID or handle it differently based on your needs
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

  glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0); // Top left
  glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0); // Top right
  glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0); // Bottom right
  glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, -1.0); // Bottom left
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Texture::loadPlayerTexture(const char *filename) {
  playerTexture = loadTexture(filename);
  if (playerTexture == 0) {
    std::cerr << "Failed to load player texture." << std::endl;
  }
}

void Texture::drawPlayer(float x, float y) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, playerTexture);
  glBegin(GL_QUADS);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // White color for player
  glTexCoord2f(0.0, 0.0); glVertex2f(x - 0.1, y + 0.1); // Bottom left
  glTexCoord2f(1.0, 0.0); glVertex2f(x + 0.1, y + 0.1); // Bottom right
  glTexCoord2f(1.0, 1.0); glVertex2f(x + 0.1, y - 0.1); // Top right
  glTexCoord2f(0.0, 1.0); glVertex2f(x - 0.1, y - 0.1); // Top left
  glEnd();
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}