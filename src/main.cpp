#include "lib/player.h"
#include "lib/mobs.h"
#include "lib/bullet.h"
#include <GL/glut.h>
#include "lib/stb_image.h"
#include <vector>

Player player(0.0f, -0.5f); // Instantiate a player object at the initial position

std::vector<Mob> mobs; // Instantiate Mobs
Mob mob1(.1,.1,1,-1);
Mob mob2(-.1,.1,1,1);
Mob mob3(.1,-.1,-1,-1);

// Predeclares vector of bullets to be used later
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

// Updates the position and values of objects then redraws
void update(int value) {
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease);

    if (isSpacePressed && player.reload == 0) {
        bullets.push_back(Bullet(player.x, player.y, 0.01, 1.5707964));
        player.reload = 10;
    }

    player.update();

    for (Mob& mob : mobs) {
        mob.update(bullets); // Pass the bullets vector to the update function
    }

    for (Bullet& bullet : bullets) {
        bullet.update();
        if (!bullet.needsRemoval) {
            bulletBuffer.push_back(bullet);
        }
    }

    bullets = bulletBuffer;
    bulletBuffer.clear();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
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
    } 
    else {
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

void handleBulletMobsCollision() {
    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        bool collision = false;

        for (auto& mob : mobs) {
            if ((bulletIt->x > mob.x - 0.1) &&
                (bulletIt->x < mob.x + 0.1) &&
                (bulletIt->y > mob.y - 0.1) &&
                (bulletIt->y < mob.y + 0.1)) {
                // Collision with enemy
                mob.health -= 1;
                collision = true;
                break;
            }
        }

        if (collision) {
            bulletIt = bullets.erase(bulletIt);
        } else {
            bulletIt++;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glLoadIdentity();
    drawBackground();

    // Draw the player
    player.draw();

    for(size_t i = 0; i < bullets.size();  i++){
	
	for(size_t j = 0; j < mobs.size(); j++){
		if((bullets[i].x > mobs[j].x-0.1) && 
		(bullets[i].x < mobs[j].x + 0.1) && 
		(bullets[i].y > mobs[j].y-0.1) && 
		(bullets[i].y < mobs[j].y + 0.1)){
		   //Collison with enemy
		   mobs[j].health -= 1;
		   bullets.erase(bullets.begin() + i);
		}
	}
	
        bullets[i].draw();
	
    }

    // Draw the mobs
for (Mob& mob : mobs) {
    mob.update(bullets);   // Update the mobs object
    if (mob.health > 0) {
        mob.draw();
    }
}

// Erase bullets marked for removal
auto it = bullets.begin();
while (it != bullets.end()) {
    if (it->needsRemoval) {
        it = bullets.erase(it);
    } else {
        it++;
    }
}

    handleBulletMobsCollision();

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

    loadBackgroundTexture("lib/images/space.jpeg");
    drawBackground();
    
    glutMainLoop();
    return 0;
}
