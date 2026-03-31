#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Rotate the entire scene slightly to see 3D depth
    glRotatef(25, 1.0, 1.0, 0.0);

    // 1. Solid Cube
    glColor3f(0.5, 0.0, 0.8); // Purple
    glPushMatrix();
    glTranslatef(-0.4, 0.0, 0.0);
    glutSolidCube(0.4);
    glPopMatrix();

    // 2. Wired Teapot
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.0);
    glutWireTeapot(0.3);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Task 4: 3D Figures");
    glEnable(GL_DEPTH_TEST); // Vital for 3D!
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}