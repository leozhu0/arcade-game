#define GL_SILENCE_DEPRECATION
#include "lib/player.h"
#include "lib/mobs.h"
#include "lib/bullet.h"
#include <GL/glut.h>
#include <vector>

Player player(0.0f, -0.5f); // Instantiate a player object at the initial position

std::vector<Mob> mobs;
Mob mob1(.1,.1); // Instantiate a Mobs object
Mob mob2(-.1,.1);
Mob mob3(.1,-.1);

mobs.push_back(mob1);
mobs.push_back(mob2);
mobs.push_back(mob3);

// = {Mob(.1,.1), Mob(-.1,.1), Mob(.1,-.1)};

std::vector<Bullet> bullets;
std::vector<Bullet> bulletBuffer;

//bullets.push_back(Bullet(0.1f,0.1f,1.7f));
bool isSpacePressed = false;
void handleKeypress(unsigned char key, int x, int y) {
    if (key == ' ') {
        isSpacePressed = true;
    }
}

void handleKeyRelease(unsigned char key, int x, int y) {
    if (key == ' ') {
        isSpacePressed = false;
    }
}
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
   // glutKeyboardFunc(handleKeypress);
   // glutKeyboardUpFunc(handleKeyRelease);
    //glutTimerFunc(0, update, 0);
}

void update(int value) {
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease);

//bullets.push_back(Bullet(0.1f,0.1f,1.7f));

    if (isSpacePressed && player.reload == 0) {
        bullets.push_back(Bullet(player.x,player.y,.01,1.5707964));
        player.reload = 10;
    }

    player.update(); // Update the player object

    for (Mob mob : mobs) {
        mob.update();   // Update the mobs object
    }

    // for (size_t i = 0; i < bullets.size();  i++) {
    // 	bullets[i].update();
    // }
    for (Bullet bullet : bullets) {
        bullet.update();
        if (!(bullet.needsRemoval)) bulletBuffer.push_back(bullet);
    }

    bullets = bulletBuffer;
    bulletBuffer.clear();
    
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, update, 0); // Schedule the next update after 16 milliseconds
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0); // Set the background color to black
    glVertex2f(-1.0, 1.0);    // Top-left
    glVertex2f(1.0, 1.0);     // Top-right
    glVertex2f(1.0, -1.0);    // Bottom-right
    glVertex2f(-1.0, -1.0);   // Bottom-left
    glEnd();

    // Draw the player
    player.draw();

    // Draw the bullets
    for(Bullet bullet : bullets){
        bullet.draw();
    }

    // Draw the mobs
    for (Mob mob : mobs) {
        mob.draw();
    }

    glutSwapBuffers(); // Use double buffering
}

void timer(int value) {
    update(value);
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, timer, value); // Schedule the next update after 16 milliseconds
}

void handleMouseMotion(int newX, int newY) {
    // Update player position based on mouse coordinates
    player.handleMouseMotion(newX, newY);
}

int main(int argc, char** argv) {
    // Mob mob1(.1,.1); // Instantiate a Mobs object
    // Mob mob2(-.1,.1);
    // Mob mob3(.1,-.1);

    // mobs.push_back(mob1);
    // mobs.push_back(mob2);
    // mobs.push_back(mob3);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bullet Hell");
    //glutFullScreen(); // Uncomment this line if you want the window to be fullscreen
    glutDisplayFunc(display);
    glutPassiveMotionFunc(handleMouseMotion);
    glutTimerFunc(25, timer, 0);
    glutMainLoop();
    return 0;
}
