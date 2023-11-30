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
    float x;
    float y;
    GLuint textureID;
};

#endif 
