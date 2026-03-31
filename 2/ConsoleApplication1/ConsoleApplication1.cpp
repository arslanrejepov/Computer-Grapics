#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. GL_QUADS (Filled)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0, 0.5, 0.0); // Orange
    glBegin(GL_QUADS);
    glVertex2f(-0.8, 0.5); glVertex2f(-0.4, 0.5);
    glVertex2f(-0.4, 0.2); glVertex2f(-0.8, 0.2);
    glEnd();

    // 2. GL_QUAD_STRIP (Wired)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glBegin(GL_QUAD_STRIP);
    glVertex2f(0.1, 0.5); glVertex2f(0.1, 0.2); // First edge
    glVertex2f(0.4, 0.5); glVertex2f(0.4, 0.2); // Second edge
    glVertex2f(0.7, 0.5); glVertex2f(0.7, 0.2); // Third edge
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Task 3: Quads");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}