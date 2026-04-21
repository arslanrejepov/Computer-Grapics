#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

struct vectr
{
    float row[3];
};

const int numVertices = 4;

vectr vertices[numVertices] = {
    {-0.5, -0.5, 1},
    {0.5, -0.5, 1},
    {0.5, 0.5, 1},
    {-0.5, 0.5, 1}
};

float angle = 1.0f;

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++)
    {
        glColor3f((i == 0), (i == 1), (i == 2));
        glVertex2f(vertices[i].row[0], vertices[i].row[1]);
    }
    glEnd();

    glFlush();
}

void animate(void)
{
    glMatrixMode(GL_MODELVIEW);

    glTranslatef(0.5f, -0.5f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.5f, 0.5f, 0.0f);

    drawScene();
}

void timer(int)
{
    animate();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init(void)
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotation around (0.5, -0.5)");

    init();

    glutDisplayFunc(drawScene);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}