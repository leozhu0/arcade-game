#include "lib/player.h"
#include "lib/mobs.h"
#include "lib/bullet.h"
#include <GL/glut.h>
#include <vector>

Player player(0.0f, -0.5f); // Instantiate a player object at the initial position
Mobs mobs; // Instantiate a Mobs object
std::vector<Bullet> bullets;

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

    if(isSpacePressed){
	bullets.push_back(Bullet(player.x,player.y,1.7));
    }
    player.update(); // Update the player object
    mobs.update();   // Update the mobs object
    for(size_t i = 0; i < bullets.size();  i++){
    	bullets[i].update();
    }
    
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, update, 0); // Schedule the next update after 16 milliseconds
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.5, 0.2); // Set the background color to light brown
    glVertex2f(-1.0, 1.0);    // Top-left
    glVertex2f(1.0, 1.0);     // Top-right
    glVertex2f(1.0, -1.0);    // Bottom-right
    glVertex2f(-1.0, -1.0);   // Bottom-left
    glEnd();

    // Draw the player
    player.draw();

    for(size_t i = 0; i < bullets.size();  i++){
        bullets[i].draw();
    }

    // Draw the mobs
    mobs.draw();

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bullet Hell");
    glutFullScreen(); // Uncomment this line if you want the window to be fullscreen
    glutDisplayFunc(display);
    glutPassiveMotionFunc(handleMouseMotion);
    glutTimerFunc(25, timer, 0);
    init(); // Call the init function to set the background color
    glutMainLoop();
    return 0;
}
