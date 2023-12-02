#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    void update();
    void draw();
    Bullet(float i_x, float i_y, float rad, float dir);
    bool needsRemoval = false;
    float x, y;
    float radius;
    float direction;
};

#endif 
