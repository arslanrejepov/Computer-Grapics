#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Change mode to LINE for wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0, 1.0, 1.0); // White lines

    // GL_TRIANGLES
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8, 0.2); glVertex2f(-0.9, -0.1); glVertex2f(-0.7, -0.1);
    glEnd();

    // GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.4, 0.2); glVertex2f(-0.5, -0.1);
    glVertex2f(-0.2, 0.2); glVertex2f(-0.3, -0.1);
    glEnd();

    // GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.3, 0.0);
    glVertex2f(0.1, 0.2); glVertex2f(0.5, 0.2); glVertex2f(0.5, -0.2);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Task 2: Wired Triangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}