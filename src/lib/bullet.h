#ifndef BULLET_H
#define BULLET_H
#include <cmath>

class Bullet {
public:
  void update();
  void draw();
  Bullet(float i_x, float i_y, float rad, float dir, float i_speed, bool playerBullet);
  bool needsRemoval = false;
  bool belongsToPlayer;
  float x, y, radius, direction, speed;
};

#endif
