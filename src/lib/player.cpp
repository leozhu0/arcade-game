#define STB_IMAGE_IMPLEMENTATION
#include "player.h"
#include <GL/glut.h>
#include "stb_image.h"

Player::Player(float initialX, float initialY) : x(initialX), y(initialY) {
    // Load image using stb_image
    int width, height, channels;
    
    // Load image and check for errors
    unsigned char* image = stbi_load("lib/images/testCannon.png", &width, &height, &channels, STBI_rgb);
    if (!image) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << "\n";
        return;  // Return or handle the error appropriately
    }
    else {
        std::cout << "Image loaded successfully. Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n"; //FIXME
    }

    // Create OpenGL texture
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEAREST = no smoothing
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_NEAREST = no smoothing

    // Free image data
    stbi_image_free(image);
}

void Player::update() {
    // Update player logic here
}

void Player::draw() const {
    // Draw player with texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBegin(GL_QUADS);
    glColor4f(1.0, 1.0, 1.0, 0.5);  // Specify alpha (transparency)

    // Specify texture coordinates for each vertex (in the range [0, 1])
    glTexCoord2f(0.0, 0.0); glVertex2f(x - 0.1, y + 0.1);
    glTexCoord2f(1.0, 0.0); glVertex2f(x + 0.1, y + 0.1);
    glTexCoord2f(1.0, 1.0); glVertex2f(x + 0.1, y - 0.1);
    glTexCoord2f(0.0, 1.0); glVertex2f(x - 0.1, y - 0.1);
    
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void Player::handleMouseMotion(int newX, int newY) {
    // Update player position based on mouse coordinates
    x = (newX - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0);
    y = (glutGet(GLUT_WINDOW_HEIGHT) / 2.0 - newY) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
}