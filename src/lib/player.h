#define GL_SILENCE_DEPRECATION
#ifndef PLAYER_H
#define PLAYER_H
#include <GL/glut.h>
#include <iostream>

class Player {
public:
    Player(float initialX, float initialY);

    void update();
    void draw() const;  
    void handleMouseMotion(int newX, int newY);
    GLuint textureID;
    float x, y;
    int reload; // in units of frame
};

#endif
