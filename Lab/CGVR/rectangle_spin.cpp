#include <GL/glut.h>

int spinWin;
float angle = 0.0;

void display() {
       glClear(GL_COLOR_BUFFER_BIT);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       // Rotate only the rectangle in the second window
       if (glutGetWindow() == spinWin)

              glRotatef(angle, 0, 0, 1);

       glBegin(GL_POLYGON);
              glColor3f(1, 0, 0);
              glVertex2f(-150, -150);

              glColor3f(0, 1, 0);
              glVertex2f(-150, 150);

              glColor3f(0, 0, 1);
              glVertex2f(150, 150);

              glColor3f(1, 1, 0);
              glVertex2f(150, -150);
       glEnd();

       glutSwapBuffers();
}

void idle() {
       angle += 0.1;

       if (angle >= 360)
              angle -= 360;

       glutSetWindow(spinWin);
       glutPostRedisplay();
}

void myInit() {
       glClearColor(1, 1, 1, 1);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(-250, 250, -250, 250);
       glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv) {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
       glutInitWindowSize(500, 500);

       // First window: stationary rectangle
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Rect 1");
       myInit();
       glutDisplayFunc(display);

       // Second window: rotating rectangle
       glutInitWindowPosition(600, 100);
       spinWin = glutCreateWindow("Rect 2");
       myInit();
       glutDisplayFunc(display);
       glutIdleFunc(idle);

       glutMainLoop();
       return 0;
}
