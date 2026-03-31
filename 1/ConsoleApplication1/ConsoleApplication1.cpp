#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Ensure shapes are filled

    // 1. GL_TRIANGLES (One standalone triangle)
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8, 0.8); glVertex2f(-0.9, 0.5); glVertex2f(-0.7, 0.5);
    glEnd();

    // 2. GL_TRIANGLE_STRIP (2 connected triangles)
    glColor3f(0.0, 1.0, 0.0); // Green
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.4, 0.8); glVertex2f(-0.5, 0.5);
    glVertex2f(-0.2, 0.8); glVertex2f(-0.3, 0.5);
    glEnd();

    // 3. GL_TRIANGLE_FAN (2 connected triangles sharing a center)
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.3, 0.6); // Center point
    glVertex2f(0.1, 0.8); glVertex2f(0.5, 0.8); glVertex2f(0.5, 0.4);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Task 1: Filled Triangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}