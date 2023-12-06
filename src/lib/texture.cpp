#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "stb_image.h"

GLuint Texture::backgroundTexture = 1;
GLuint Texture::playerTexture = 1;

GLuint Texture::loadTexture(const char *filename) {
  GLuint textureID;
  int width, height, channels;
  unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);

  if (image) {
    std::cout << "Image loaded successfully: " << filename << " Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n"; // FIXME REMOVE LATER
    glGenTextures(1, &textureID);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL Error after glGenTextures: " << error << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (channels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    // Set texture parameters
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

  } else {
    // Handle error loading image
    std::cerr << "Error loading texture: " << filename << std::endl;
    std::cerr << "STB Image Error: " << stbi_failure_reason() << std::endl;

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