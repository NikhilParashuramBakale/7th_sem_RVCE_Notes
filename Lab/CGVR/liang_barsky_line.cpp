#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glut.h>

using namespace std;
struct Line {
       float x0, y0, x1, y1;

};

float xmin, ymin, xmax, ymax;
float vxmin, vymin, vxmax, vymax;
vector<Line> lines;

bool cliptest(float p, float q, float &t1, float &t2) {
       if (p == 0) {
              if (q < 0) return false;
       }
       else {
              float r = q / p;
              if (p < 0) {
                     t1 = max(t1, r);
                     if (r > t2) return false;
              }
              else {
                     t2 = min(t2, r);
                     if (r < t1) return false;
              }
       }
       return true;

}

bool liangBarsky(float &x0, float &y0, float &x1, float &y1) {
       float dx = x1 - x0, dy = y1 - y0;
       float t1 = 0, t2 = 1;

       if (cliptest(-dx, x0-xmin, t1, t2) &&
              cliptest(dx, xmax-x0, t1, t2) &&
              cliptest(-dy, y0-ymin, t1, t2) &&
              cliptest(dy, ymax-y0, t1, t2)) {

              float x = x0, y = y0;

              x0 = x + t1 * dx;
              y0 = y + t1 * dy;
              x1 = x + t2 * dx;
              y1 = y + t2 * dy;

              return true;
       }
       return false;
}

float mapX(float x) {
       return vxmin + (x-xmin)*(vxmax-vxmin)/(xmax-xmin);

}

float mapY(float y) {
       return vymin + (y-ymin)*(vymax-vymin)/(ymax-ymin);

}

void display() {
       glClear(GL_COLOR_BUFFER_BIT);

       // Original lines and clipping window
       glViewport(0, 0, 500, 500);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(-250, 250, -250, 250);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       glColor3f(1, 0, 0);
       glBegin(GL_LINES);
       for (auto l : lines) {

              glVertex2f(l.x0, l.y0);
              glVertex2f(l.x1, l.y1);
       }
       glEnd();

       glColor3f(0, 1, 0);
       glBegin(GL_LINE_LOOP);
       glVertex2f(xmin, ymin);
       glVertex2f(xmax, ymin);
       glVertex2f(xmax, ymax);
       glVertex2f(xmin, ymax);
       glEnd();

       // Clipped lines in viewport
       glViewport(500, 0, 500, 500);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(vxmin-50, vxmax+50, vymin-50, vymax+50);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       glColor3f(0, 1, 0);
       glBegin(GL_LINE_LOOP);
       glVertex2f(vxmin, vymin);
       glVertex2f(vxmax, vymin);
       glVertex2f(vxmax, vymax);
       glVertex2f(vxmin, vymax);
       glEnd();

       glColor3f(0, 0, 1);
       glBegin(GL_LINES);

       for (auto l : lines) {
              float x0=l.x0, y0=l.y0, x1=l.x1, y1=l.y1;

              if (liangBarsky(x0, y0, x1, y1)) {
                     glVertex2f(mapX(x0), mapY(y0));
                     glVertex2f(mapX(x1), mapY(y1));

              }
       }

       glEnd();
       glFlush();
}

int main(int argc, char **argv) {
       int n;

       cout << "Enter clipping window: ";
       cin >> xmin >> ymin >> xmax >> ymax;
       cout << "Enter viewport: ";
       cin >> vxmin >> vymin >> vxmax >> vymax;

       cout << "Enter number of lines: ";
       cin >> n;

       for (int i=0; i<n; i++) {
              Line l;
              cout << "Enter x0 y0 x1 y1: ";
              cin >> l.x0 >> l.y0 >> l.x1 >> l.y1;
              lines.push_back(l);

       }

       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(1000, 500);
       glutCreateWindow("Liang Barsky Line Clipping");

       glClearColor(1, 1, 1, 1);
       glutDisplayFunc(display);
       glutMainLoop();

       return 0;
}
