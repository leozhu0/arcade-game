#define GL_SILENCE_DEPRECATION
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(float initialX, float initialY);
    void update();
    void draw();
    void handleMouseMotion(int x, int y);

    float x, y;
    int reload; // in units of frame
};

#endif // PLAYER_H
