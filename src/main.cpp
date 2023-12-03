#include "lib/bullet.h"
#include "lib/mobs.h"
#include "lib/player.h"
#include "lib/stb_image.h"
#include <GL/glut.h>
#include <vector>

enum GameState {
  START_SCREEN,
  PLAYING,
  GAME_OVER
};

GameState gameState = START_SCREEN;
int windowWidth = 1920;
int windowHeight = 1080;
int prevMouseX = windowWidth / 2;
int prevMouseY = windowHeight / 2;
GLuint backgroundTexture; // Declare a texture for the background

Player player(0.0f, -0.5f);  // Instantiate a player object at the initial position
std::vector<Mob> mobs;       // Instantiate Mobs
Mob mob1(-0.9, 0.9, 1, -1);  // Left corner
Mob mob2(0.9, 0.9, 1, 1);    // Right corner
Mob mob3(0.0, -0.0, -1, -1); // Middle

// Predeclares vector of bullets to be used later
std::vector<Bullet> bullets;
std::vector<Bullet> bulletBuffer;

// bullets.push_back(Bullet(0.1f,0.1f,1.7f));
bool isSpacePressed = false;
void handleKeypress(unsigned char key, int x, int y) {
  if (gameState == START_SCREEN && key == ' ') {
    gameState = PLAYING;
  } else if (gameState == PLAYING && key == ' ') {
    isSpacePressed = true;
  }
}

void handleKeyRelease(unsigned char key, int x, int y) {
  if (key == ' ') {
    isSpacePressed = false;
  }
}
void drawStartMessage(const char *message, void *font, float fontSize) {
    // Calculate the width of the text string
    int stringWidth = glutBitmapLength(font, (unsigned char *)message);

    // Calculate the starting position to center the text horizontally
    float x = -0.5 + (static_cast<float>(glutGet(GLUT_WINDOW_WIDTH)) - stringWidth) / (2.0 * glutGet(GLUT_WINDOW_WIDTH));

    // Adjust the font size
    glPointSize(fontSize);

    glColor3f(1.0, 1.0, 1.0); // White color for text
    glRasterPos2f(x, 0.0);

    while (*message) {
        glutBitmapCharacter(font, *message);
        message++;
    }
}

void init() {
  // Set up the initial orthographic projection
  int windowWidth = 1920;
  int windowHeight = 1080;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Calculate aspect ratio
  float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

  // Adjust the orthographic projection matrix
  if (aspectRatio >= 1.0) {
    glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0, 1.0);
  } else {
    glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1.0, 1.0);
  }

  glMatrixMode(GL_MODELVIEW);

  glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
}

// Updates the position and values of objects then redraws
void update(int value) {
  glutKeyboardFunc(handleKeypress);
  glutKeyboardUpFunc(handleKeyRelease);

  if (gameState == PLAYING && isSpacePressed && player.reload == 0) {
    bullets.push_back(Bullet(player.x, player.y, 0.01, 1.5707964));
    player.reload = 10;
  }

  player.update();

  for (Mob &mob : mobs) {
    mob.update(bullets); // Pass the bullets vector to the update function
  }

  for (Bullet &bullet : bullets) {
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

void loadBackgroundTexture(const char *filename) {
  int width, height, channels;
  unsigned char *image = stbi_load(filename, &width, &height, &channels, 3); // 3 channels for RGB

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

  if (gameState == START_SCREEN) {
    glColor3f(0.0, 0.0, 0.0); // Black color for background
  } else {
    glColor3f(1.0, 1.0, 1.0); // White color for background
  }
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.0, 1.0);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(1.0, 1.0);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(1.0, -1.0);
  glTexCoord2f(0.0, 1.0);
  glVertex2f(-1.0, -1.0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void handleBulletMobsCollision() {
  auto bulletIt = bullets.begin();
  while (bulletIt != bullets.end()) {
    bool collision = false;

    for (auto &mob : mobs) {
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

  if (gameState == START_SCREEN) {
    // Draw start screen content
    glColor3f(1.0, 1.0, 1.0); // White color for text
    drawStartMessage("Press SPACE to start the game", GLUT_BITMAP_HELVETICA_18, 30.0f);
    // Add any other start screen content here
  } else if (gameState == PLAYING) {
    // Draw the player
    player.draw();

    for (size_t i = 0; i < bullets.size(); i++) {
      for (size_t j = 0; j < mobs.size(); j++) {
        if ((bullets[i].x > mobs[j].x - 0.1) &&
            (bullets[i].x < mobs[j].x + 0.1) &&
            (bullets[i].y > mobs[j].y - 0.1) &&
            (bullets[i].y < mobs[j].y + 0.1)) {
          // Collision with enemy
          mobs[j].health -= 1;
          bullets.erase(bullets.begin() + i);
        }
      }
      bullets[i].draw();
    }

    // Draw the mobs
    for (Mob &mob : mobs) {
      mob.update(bullets); // Update the mobs object
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
  }

  glutSwapBuffers(); // Use double buffering
}

void timer(int value) {
  update(value);
  glutPostRedisplay();             // Request a redraw
  glutTimerFunc(16, timer, value); // Schedule the next update after 16 milliseconds
}

void handleMouseMotion(int newX, int newY) {
  // Update player position based on mouse coordinates
  player.handleMouseMotion(newX, newY);

  // Check if the mouse position is beyond the window boundaries
  if (newX < 0 || newX >= windowWidth || newY < 0 || newY >= windowHeight) {
    // Reset the mouse position to the center of the window
    glutWarpPointer(prevMouseX, prevMouseY);
  } else {
    // Update the previous mouse position
    prevMouseX = newX;
    prevMouseY = newY;
  }
}

int main(int argc, char **argv) {
  mobs.push_back(mob1);
  mobs.push_back(mob2);
  mobs.push_back(mob3);

  glutInit(&argc, argv);

  // Set the initial window size
  glutInitWindowSize(1920, 1080); // Set width and height
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("Bullet Hell");
  // glutFullScreen(); // Uncomment this line if you want the window to be fullscreen
  glutDisplayFunc(display);
  glutPassiveMotionFunc(handleMouseMotion);
  glutSetCursor(GLUT_CURSOR_NONE);
  glutTimerFunc(25, timer, 0);
  init(); // Call the init function to set the background color
  loadBackgroundTexture("lib/images/space.jpeg");
  drawBackground();

  glutMainLoop();
  return 0;
}