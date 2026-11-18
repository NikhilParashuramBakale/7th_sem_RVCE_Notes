#include <cmath>
#include <GL/glut.h>

void drawCircle(int xc, int yc, int r) {
       glBegin(GL_LINE_LOOP);
       for (int i = 0; i < 100; i++) {
              float t = 2 * 3.142 * i / 100;
              glVertex2f(xc + r * cos(t), yc + r * sin(t));
       }
       glEnd();

}

void drawCylinder() {
       int xc = 200, r = 50;
       int y1 = 150, y2 = 350;

       glColor3f(1, 0, 0);

       // Top and bottom circular ends
       drawCircle(xc, y1, r);
       drawCircle(xc, y2, r);

       // Connecting side edges
       glBegin(GL_LINES);

              glVertex2f(xc - r, y1);
              glVertex2f(xc - r, y2);

              glVertex2f(xc + r, y1);
              glVertex2f(xc + r, y2);
       glEnd();
}

void drawRectangle(int x1, int x2, int y1, int y2) {
       glBegin(GL_LINE_LOOP);
              glVertex2f(x1, y1);
              glVertex2f(x2, y1);
              glVertex2f(x2, y2);
              glVertex2f(x1, y2);
       glEnd();
}

void drawParallelepiped() {
       int x1 = 100, x2 = 300;
       int y1 = 100, y2 = 300;
       int offset = 60;

       glColor3f(0, 0, 1);

       // Front and back rectangles
       drawRectangle(x1, x2, y1, y2);
       drawRectangle(x1 + offset, x2 + offset,

                                y1 + offset, y2 + offset);

       // Connect corresponding corners
       glBegin(GL_LINES);

              glVertex2f(x1, y1);
              glVertex2f(x1 + offset, y1 + offset);

              glVertex2f(x2, y1);
              glVertex2f(x2 + offset, y1 + offset);

              glVertex2f(x2, y2);
              glVertex2f(x2 + offset, y2 + offset);

              glVertex2f(x1, y2);
              glVertex2f(x1 + offset, y2 + offset);
       glEnd();
}

void display1() {
       glClear(GL_COLOR_BUFFER_BIT);
       drawCylinder();
       glFlush();

}
void display2() {
       glClear(GL_COLOR_BUFFER_BIT);
       drawParallelepiped();
       glFlush();

}

void myInit() {
       glClearColor(1, 1, 1, 1);
       gluOrtho2D(0, 500, 0, 500);

}

int main(int argc, char** argv) {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);

       glutInitWindowPosition(100, 100);
       glutCreateWindow("Cylinder");
       myInit();
       glutDisplayFunc(display1);

       glutInitWindowPosition(650, 100);
       glutCreateWindow("Parallelepiped");
       myInit();
       glutDisplayFunc(display2);

       glutMainLoop();
       return 0;
}
