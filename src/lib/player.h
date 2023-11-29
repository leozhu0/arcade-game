#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(float initialX, float initialY);
    void update();
    void draw();
    void handleMouseMotion(int x, int y);

private:
    float x, y;
};

#endif // PLAYER_H