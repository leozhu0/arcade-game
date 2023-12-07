#include "lib/bullet.h"
#include "lib/mobs.h"
#include "lib/player.h"
#include "lib/texture.h"
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

enum GameState {
  START_SCREEN,
  PLAYING,
  GAME_OVER,
  GAME_WON
};

static int currentTime = 0;
static int score = 0;
GameState gameState = START_SCREEN;
int windowWidth = 1920;
int windowHeight = 1080;
int prevMouseX = windowWidth / 2;
int prevMouseY = windowHeight / 2;
Texture textureLoader;

Player player(0.0f, -0.5f); // Instantiate a player object at the initial position
std::vector<Mob> mobs;      // Instantiate Mobs
std::vector<Mob> mobBuffer;
Mob mob1(-0.9, 0.9, 1, -1);   // Left corner
Mob mob2(0.9, 0.9, -1, -1);   // Right corner
Mob mob3(0.0, 0.0, 0, 1);     // Middle
Mob mob4(-0.45, 0.45, 1, 1);  // Between mob1 and mob3
Mob mob5(0.45, 0.45, -1, 1);  // Between mob2 and mob3

// Predeclares vector of bullets to be used later
std::vector<Bullet> bullets;
std::vector<Bullet> bulletBuffer;

bool isSpacePressed = false;
void handleKeypress(unsigned char key, int x, int y) {
  if (gameState == START_SCREEN && key == char(13) || gameState == GAME_OVER && key == char(13) || gameState == GAME_WON && key == char(13)) {
    gameState = PLAYING;
    // Reset game-related variables when transitioning to the PLAYING state
    score = 0;
    currentTime = 0;
    mobs.clear(); // Clear existing mobs
    mobs.push_back(mob1);
    mobs.push_back(mob2);
    mobs.push_back(mob3);
    mobs.push_back(mob4);
    mobs.push_back(mob5);
    glutPostRedisplay();
  } else if (gameState == PLAYING && key == ' ') {
    isSpacePressed = true;
  }
}

void handleKeyRelease(unsigned char key, int x, int y) {
  if (key == ' ') {
    isSpacePressed = false;
  }
}

void drawStar(float x, float y, float size) {
  glPointSize(size);

  // Set color for the star (e.g., yellow)
  glColor3f(1.0, 1.0, 0.0);

  glBegin(GL_LINE_LOOP);

  for (int i = 0; i < 10; ++i) {
    float angle = i * M_PI / 5.0;            // Use M_PI for more accurate calculation
    float radius = (i % 2 == 0) ? 0.2 : 0.1; // Alternate between two radii
    float px = x + radius * std::cos(angle);
    float py = y + radius * std::sin(angle);
    glVertex2f(px, py);
  }

  glEnd();
}

void startDisplay() {
  glColor3f(1.0, 0.0, 0.0); // Red color for text
  glRasterPos2f(-0.33, 0.5);

  char gameName[] = "WELCOME TO BULLET HELL";

  for (char character : gameName) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  glColor3f(0.0, 0.0, 1.0); // Blue color for text
  glRasterPos2f(-0.38, 0.4);

  char createdBy[] = "By: Leo Z, John L, Kevin L, Jennifer L";

  for (char character : createdBy) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  glColor3f(1.0, 1.0, 1.0); // White color for text
  glRasterPos2f(-0.3, -0.2);

  char space[] = "Press ENTER to start the game";

  for (char character : space) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  drawStar(0.8, 0.5, 10.0);
  drawStar(-0.8, -0.2, 10.0);

  // glutSwapBuffers;
}

// Calculating and displaying score
void drawScore() {

  score = 120000 - (currentTime);

  if (score == 0) {
    gameState = GAME_OVER;
  }

}

void endDisplay() {
  glColor3f(1.0, 0.0, 0.0); // Red color for text
  glRasterPos2f(-0.3, 0.5);

  char gameOverText[] = "GAME OVER YOU LOST!";
  for (char character : gameOverText) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  glColor3f(1.0, 1.0, 1.0); // White color for text
  glRasterPos2f(-0.35, -0.2);

  char space[] = "Press ENTER to start the game";

  for (char character : space) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }
}

void winDisplay() {
  glColor3f(1.0, 0.0, 0.0); // Red color for text
  glRasterPos2f(-0.3, 0.5);

  char gameWinText[] = "YOU WON!! SCORE:";
  for (char character : gameWinText) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  // Display the actual score
  std::string scoreText = std::to_string(score);
  glColor3f(1.0, 1.0, 1.0); // White color for text

  for (char character : scoreText) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
  }

  glColor3f(1.0, 1.0, 1.0); // White color for text
  glRasterPos2f(-0.35, -0.2);

  char space[] = "Press ENTER to start the game";

  for (char character : space) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
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
  textureLoader.loadPlayerTexture("src/lib/images/testCannon.png");
  textureLoader.loadMobTexture("src/lib/images/mobs.png");
}

// Updates the position and values of objects then redraws
void update(int value) {
  glutKeyboardFunc(handleKeypress);
  glutKeyboardUpFunc(handleKeyRelease);

  // spawning player's bullets
  if (gameState == PLAYING && isSpacePressed && player.reload == 0) {
    bullets.push_back(Bullet(player.x, player.y, 0.01, 1.5707964, 0.015, true));
    player.reload = 10;
  }

  player.update();

  for (Bullet &bullet : bullets) {

    // Checking if a bulelt has hit a mob
    for (Mob &mob : mobs) {
      if ((bullet.x > mob.x - 0.1) &&
          (bullet.x < mob.x + 0.1) &&
          (bullet.y > mob.y - 0.1) &&
          (bullet.y < mob.y + 0.1)) {

        --mob.health;
        bullet.needsRemoval = true;
      }
    }

    // Removes a bullet that is out of bounds or hit a mob
    bullet.update();
    if (!bullet.needsRemoval) {
      bulletBuffer.push_back(bullet);
    }
  }

  // Additional bullet logic to improve runtime
  bullets = bulletBuffer;
  bulletBuffer.clear();

  for (Mob &mob : mobs) {
    mob.update();

    // Same bullet logic for the bullets of the mobs 
    for (Bullet &bullet : mob.bullets) {
      bullet.update();

      // Checking if the player has been hit by a mobs' bullet
      float distance = sqrtf(powf(player.x - bullet.x, 2) + powf(player.y - bullet.y, 2));

      if (distance <= bullet.radius) {
        // GAME OVER
        gameState = GAME_OVER;
      }

      if (!bullet.needsRemoval) {
        mob.bulletBuffer.push_back(bullet);
      }
    }

    mob.bullets = mob.bulletBuffer;
    mob.bulletBuffer.clear();

    // Only keeps around the mobs that are still alive
    if (mob.health > 0) {
      mobBuffer.push_back(mob);
    }
  }

  mobs = mobBuffer;
  mobBuffer.clear();

  if (mobs.empty()) {
    // Transition to GAME_OVER state
    gameState = GAME_WON;
  }

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);

  currentTime += 16;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw background
  glLoadIdentity();
  textureLoader.drawBackground(gameState == START_SCREEN);

  if (gameState == START_SCREEN) {

    // Draw start screen content
    glColor3f(1.0, 1.0, 1.0); // White color for text
    // drawStartMessage("Press SPACE to start the game", GLUT_BITMAP_HELVETICA_18, 30.0f, 0.0);
    startDisplay();
    // Add any other start screen content here

  } else if (gameState == PLAYING) {

    // Draw the player
    player.draw();
    glColor3f(1.0, 1.0, 1.0); // White color for text
    drawScore();

    // Drawing the bullets
    for (Bullet &bullet : bullets) {
      bullet.draw();
    }

    // Drawing the mobs and their respective bullets
    for (Mob &mob : mobs) {
      mob.draw();

      for (Bullet &bullet : mob.bullets) {
        bullet.draw();
      }
    }

    // Below are checks for the game state
  } else if (gameState == GAME_OVER) {
    score = 0;
    endDisplay();
  } else if (gameState == GAME_WON) {
    winDisplay();
  }

    glutSwapBuffers(); // Use double buffering
}

void timer(int value) {
  update(value);
  glutPostRedisplay(); // Request a redraw
  // glutTimerFunc(16, timer, value); // Schedule the next update after 16 milliseconds
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
  mobs.push_back(mob4);
  mobs.push_back(mob5);

  glutInit(&argc, argv);

  // Set the initial window size
  glutInitWindowSize(1920, 1080); // Set width and height
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutCreateWindow("Bullet Hell");
  glutDisplayFunc(display);
  textureLoader.loadBackgroundTexture("src/lib/images/space.jpeg");
  textureLoader.drawBackground(gameState == START_SCREEN);
  glutPassiveMotionFunc(handleMouseMotion);
  glutSetCursor(GLUT_CURSOR_NONE); // hides cursor
  glutTimerFunc(25, timer, 0);
  init();

  glutMainLoop();
  return 0;
}