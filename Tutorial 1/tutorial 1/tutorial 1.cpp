#include <GL/glut.h>

void display()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, 0.6f);
    glVertex2f(-1.1f, -0.6f);
    glVertex2f(-0.5f, -0.6f);
    glEnd();

    glColor3f(0.2f, 0.9f, 0.3f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(-0.15f, 0.1f);
    glVertex2f(0.15f, 0.1f);
    glVertex2f(-0.15f, -0.5f);
    glVertex2f(0.15f, -0.5f);
    glEnd();

    glColor3f(0.3f, 0.6f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.75f, 0.0f);
    glVertex2f(0.75f, 0.65f);
    glVertex2f(1.15f, 0.32f);
    glVertex2f(1.15f, -0.32f);
    glVertex2f(0.75f, -0.65f);
    glVertex2f(0.35f, -0.32f);
    glVertex2f(0.35f, 0.32f);
    glVertex2f(0.75f, 0.65f);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.4, 1.4, -0.9, 0.9, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Task 1 - Filled Triangles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}