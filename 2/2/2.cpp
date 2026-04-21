#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

struct vectr
{
    float row[3];
};

struct matrix
{
    float mat[3][3];
};

const int numVertices = 4;

vectr vertices[numVertices] = {
    {-0.5, -0.5, 1},
    {0.5, -0.5, 1},
    {0.5, 0.5, 1},
    {-0.5, 0.5, 1}
};

float scaleFactor = 1.01f;

matrix translatePlusPoint5Matrix = {
    1, 0, 0.5,
    0, 1, 0.5,
    0, 0, 1
};

matrix translateMinusPoint5Matrix = {
    1, 0, -0.5,
    0, 1, -0.5,
    0, 0, 1
};

matrix scaleMatrix;

void multMatrixByVector(matrix& m, vectr& v)
{
    vectr tempVector;

    for (int i = 0; i < 3; i++)
    {
        tempVector.row[i] =
            m.mat[i][0] * v.row[0] +
            m.mat[i][1] * v.row[1] +
            m.mat[i][2] * v.row[2];
    }

    v = tempVector;
}

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
    scaleMatrix = {
        scaleFactor, 0, 0,
        0, scaleFactor, 0,
        0, 0, 1
    };

    for (int i = 0; i < numVertices; i++)
    {
        multMatrixByVector(translatePlusPoint5Matrix, vertices[i]);
        multMatrixByVector(scaleMatrix, vertices[i]);
        multMatrixByVector(translateMinusPoint5Matrix, vertices[i]);
    }

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
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Scaling around (-0.5, -0.5)");

    init();

    glutDisplayFunc(drawScene);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}