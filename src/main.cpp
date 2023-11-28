#include <GL/glut.h>

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  // Drawing code goes here
  // For example, you can draw a triangle, a square, etc.

  glFlush(); // Ensures that the drawing commands are actually executed
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); // Initialize GLUT
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the display mode
  glutInitWindowSize(800, 600); // Set the window size
  glutInitWindowPosition(100, 100); // Set the window position
  glutCreateWindow("OpenGL GLUT Window"); // Create the window with a title

  init(); // Call the initialization function

  glutDisplayFunc(display); // Tell GLUT to use the display function defined above

  glutMainLoop(); // Start GLUT's main loop
  return 0;
}
