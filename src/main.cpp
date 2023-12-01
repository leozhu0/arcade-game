#define GL_SILENCE_DEPRECATION
#include "lib/player.h"
#include "lib/mobs.h"
#include "lib/bullet.h"
#include <GL/glut.h>
#include <vector>
#include "lib/stb_image.h"

Player player(0.0f, -0.5f); // Instantiate a player object at the initial position

std::vector<Mob> mobs;
Mob mob1(.1,.1); // Instantiate a Mobs object
Mob mob2(-.1,.1);
Mob mob3(.1,-.1);

// mobs.push_back(mob1);
// mobs.push_back(mob2);
// mobs.push_back(mob3);

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

GLuint backgroundTexture;

void loadBackgroundTexture(const char* filename) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 3); // 3 channels for RGB

    if (image) {
        glGenTextures(1, &backgroundTexture);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        // Set texture parameters (you might need to adjust these based on your needs)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image); // Free the image data after loading
    } else {
        // Handle error loading image
        std::cerr << "Error loading background image." << std::endl;
    }
}

void drawBackground() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, -1.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glLoadIdentity();
    drawBackground();
    // glBegin(GL_QUADS);
    // glColor3f(0.8, 0.5, 0.2); // Set the background color to light brown
    // glVertex2f(-1.0, 1.0);    // Top-left
    // glVertex2f(1.0, 1.0);     // Top-right
    // glVertex2f(1.0, -1.0);    // Bottom-right
    // glVertex2f(-1.0, -1.0);   // Bottom-left
    // glEnd();

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

    mobs.push_back(mob1);
    mobs.push_back(mob2);
    mobs.push_back(mob3);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bullet Hell");
    //glutFullScreen(); // Uncomment this line if you want the window to be fullscreen
    glutDisplayFunc(display);
    glutPassiveMotionFunc(handleMouseMotion);
    glutTimerFunc(25, timer, 0);
    init(); // Call the init function to set the background color

    loadBackgroundTexture("lib/space.jpeg");
    drawBackground();

    glutMainLoop();
    return 0;
}
