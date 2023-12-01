#define GL_SILENCE_DEPRECATION
#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    void update();
    void draw();
    void handleMouseMotion(int x, int y);
    Bullet(float i_x, float i_y, float rad, float dir);
    bool needsRemoval = false;
private:
    float x, y;
    float radius;
    float direction;
};

#endif 
