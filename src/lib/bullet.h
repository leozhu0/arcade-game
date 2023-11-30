#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    void update();
    void draw();
    void handleMouseMotion(int x, int y);
    Bullet(float i_x, float i_y, float dir);
private:
    float x, y;
    float direction;
};

#endif 
