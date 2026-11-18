// ============================================================
// bresenham line

#include<iostream>
#include<cmath>
#include<GL/glut.h>

using namespace std;

int xc1, xc2, yc1, yc2;

void drawPixel(int x, int y) {
       glColor3f(0, 0, 1);
       glPointSize(5);
       glBegin(GL_POINTS);
       glVertex2f(x, y);
       glEnd();

}

void drawLine() {
       int dx = abs(xc2 - xc1), dy = abs(yc2 - yc1);

       int incx = xc1 <= xc2 ? 1 : -1;
       int incy = yc1 <= yc2 ? 1 : -1;

       int x = xc1, y = yc1;
       if (dx > dy) {

              int p = 2 * dy - dx;
              int inc1 = 2 * (dy - dx);
              int inc2 = 2 * dy;
              for (int i = 0; i <= dx; i++) {

                     drawPixel(x, y);
                     if (p > 0) {

                             y += incy;
                             p += inc1;
                     } else {
                             p += inc2;
                     }
                     x += incx;
              }
       } else {
              int p = 2 * dx - dy;
              int inc1 = 2 * (dx - dy);
              int inc2 = 2 * dx;
              for (int i = 0; i <= dy; i++) {

                     drawPixel(x, y);
                     if (p > 0) {

                             x += incx;
                             p += inc1;
                     } else {
                             p += inc2;
                     }
                     y += incy;
              }
       }
       glFlush();
}

void mouse(int button, int state, int x, int y) {
       static bool flag = false;
       if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
              if (!flag) {
                     xc1 = x - 250;
                     yc1 = 250 - y;
                     cout << "x1, y1 : " << xc1 << " " << yc1 << " \n";
              } else {
                     xc2 = x - 250;
                     yc2 = 250 - y;
                     cout << "x2, y2 : " << xc2 << " " << yc2 << " \n";
                     drawLine();
              }
              flag = !flag;
       }

}

void display() {}

void myInit() {
       glClearColor(1, 1, 1, 1);
       gluOrtho2D(-250, 250, -250, 250);

}
int main(int argc, char** argv) {
       int choice;
       cout << "Enter 1 for keyboard and 2 for mouse \n";
       cin >> choice;
       if (choice == 1) {
              cout << "Enter x1 : ";
              cin >> xc1;
              cout << "Enter y1 : ";
              cin >> yc1;
              cout << "Enter x2 : ";
              cin >> xc2;
              cout << "Enter y2 : ";
              cin >> yc2;
       }
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Line Drawing");

       if (choice == 2) {
              glutMouseFunc(mouse);
              glutDisplayFunc(display);

       } else {
              glutDisplayFunc(drawLine);

       }
       myInit();
       glutMainLoop();
}

// ============================================================
// bresenham circle

#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;
int xc, yc, r;

void draw8Pixel(int xc, int yc, int x, int y) {
       glColor3f(0, 1, 0);
       glPointSize(3);
       glBegin(GL_POINTS);
       glVertex2f(xc + x, yc + y);
       glVertex2f(xc - x, yc + y);
       glVertex2f(xc + x, yc - y);
       glVertex2f(xc - x, yc - y);
       glVertex2f(xc + y, yc + x);
       glVertex2f(xc - y, yc + x);
       glVertex2f(xc + y, yc - x);
       glVertex2f(xc - y, yc - x);
       glEnd();

}

void drawCircle() {
       int d = 3 - 2 * r;
       int x = 0, y = r;
       while (x <= y) {
              draw8Pixel(xc, yc, x, y);
              if (d < 0) {
                     d += 4 * x + 6;
              } else {
                     d += 4 * (x - y) + 10;
                     y--;
              }
              x++;
       }
       glFlush();

}
void mouse(int button, int state, int x, int y) {

       static bool flag = false;
       if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

              if (!flag) {
                     xc = x - 250;
                     yc = 250 - y;
                     cout << "xc, yc : " << xc << " " << yc << " \n";
              } else {
                     int xb = x - 250;
                     int yb = 250 - y;
                     r = hypot(xb - xc, yb - yc);
                     cout << "xb, yb : " << xb << " " << yb << " \n";
                     drawCircle();

              }
              flag = !flag;
       }
}

void display(){}

void myInit() {
       glClearColor(1, 1, 1, 1);
       gluOrtho2D(-250, 250, -250, 250);

}

int main(int argc, char** argv) {
       int choice;
       cout << "Enter 1 for keyboard and 2 for mouse\n";
       cin >> choice;
       if (choice == 1) {
              cout << "Enter xc : ";
              cin >> xc;
              cout << "Enter yc : ";
              cin >> yc;
              cout << "Enter r : ";
              cin >> r;
       }
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Circle Drawing");

       if (choice == 2) {
              glutMouseFunc(mouse);
              glutDisplayFunc(display);

       } else {
              glutDisplayFunc(drawCircle);
       }
       myInit();
       glutMainLoop();
}

// ============================================================
// rectangle spin

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

// ============================================================
// cylinder and parallelepiped

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

// ============================================================
// sierpinski gasket

#include<iostream>
#include<GL/glut.h>

using namespace std;
typedef GLfloat point[3];

int iter;
point tetra[4]={{0,0,250},{0,250,-250},{250,-250,-250},{-250,-250,-250}};

void drawTriangle(point a, point b, point c){
       glVertex3fv(a);
       glVertex3fv(b);
       glVertex3fv(c);

}

void drawTetrahedron(point a, point b, point c, point d){
       glColor3f(1, 0, 0);
       drawTriangle(a, b, c);
       glColor3f(0, 1, 0);
       drawTriangle(a, b, d);
       glColor3f(0, 0, 1);
       drawTriangle(a, c, d);
       glColor3f(1, 1, 0);
       drawTriangle(b, c, d);

}

void divideTetrahedron(point a, point b, point c, point d, int iter){
       if (iter > 0){
              point ab, ac, ad, bc, bd, cd;
              for(int j = 0; j < 3; j++){
                     ab[j] = (a[j] + b[j]) / 2;
                     ac[j] = (a[j] + c[j]) / 2;
                     ad[j] = (a[j] + d[j]) / 2;
                     bc[j] = (b[j] + c[j]) / 2;
                     bd[j] = (b[j] + d[j]) / 2;
                     cd[j] = (c[j] + d[j]) / 2;

              }
              divideTetrahedron(a, ab, ac, ad, iter-1);
              divideTetrahedron(ab, b, bc, bd, iter-1);
              divideTetrahedron(ac, bc, c, cd, iter-1);
              divideTetrahedron(ad, bd, cd, d, iter-1);
       } else {
              drawTetrahedron(a,b,c,d);
       }
}

void display(){
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glBegin(GL_TRIANGLES);
       divideTetrahedron(tetra[0], tetra[1], tetra[2], tetra[3], iter);
       glEnd();
       glFlush();

}

void myInit(){
       glEnable(GL_DEPTH_TEST);
       glClearColor(1, 1, 1, 1);
       glOrtho(-250, 250, -250, 250, -250, 250);

}

int main(int argc, char **argv){
       cout << "Enter the number of subdivisions:";
       cin >> iter;
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Sierpenski Gasket");

       glutDisplayFunc(display);
       myInit();
       glutMainLoop();
}

// ============================================================
// sphere approximation

#include<cmath>
#include<GL/glut.h>

using namespace std;

void sphere() {
double c = 3.142 / 180;
float x, y, z;

glColor3f(0, 0, 1);
for (int phi = -80; phi < 80; phi += 10) {

       float phir = c * phi;
       float phir2 = c * (phi + 10);

       glBegin(GL_QUAD_STRIP);
       for (int theta = -180; theta <= 180; theta += 10) {

              float thetar = c * theta;

              x = sin(thetar) * cos(phir);
              y = cos(thetar) * cos(phir);
              z = sin(phir);
              glVertex3f(x, y, z);

              x = sin(thetar) * cos(phir2);
              y = cos(thetar) * cos(phir2);
              z = sin(phir2);
              glVertex3f(x, y, z);
       }
       glEnd();
}

glColor3f(1, 0, 0);

glBegin(GL_TRIANGLE_FAN);
glVertex3f(0, 0, 1);
float c80 = c * 80;
for (int theta = -180; theta <= 180; theta += 10) {

       float thetar = c * theta;
       x = sin(thetar) * cos(c80);
       y = cos(thetar) * cos(c80);
       z = sin(c80);
       glVertex3d(x, y, z);
}
glEnd();

glBegin(GL_TRIANGLE_FAN);
       glVertex3d(0, 0, -1);
       for (int theta = -180.0; theta <= 180.0; theta += 10.0) {

              float thetar = c * theta;
              x = sin(thetar) * cos(c80);
              y = cos(thetar) * cos(c80);
              z = -sin(c80);
              glVertex3d(x, y, z);
       }
       glEnd();

}

void display() {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       glTranslatef(0, 0, -1);
       glRotatef(60.0, 1.0, 1.0, 0.0);

       sphere();

       glFlush();
}

void myInit() {
       glClearColor(1, 1, 1, 1);
       glOrtho(-1, 1, -1, 1, -1, 1);

}

int main(int argc, char **argv) {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Sphere Display");

       glutDisplayFunc(display);
       myInit();
       glutMainLoop();
}

// ============================================================
// scanline area filling

#include <iostream>
#include <algorithm>
#include <GL/glut.h>

using namespace std;

int n;
float x[100], y[100];

void drawLine(float x1, float y1, float x2, float y2) {
       glColor3f(0, 0, 1);
       glBegin(GL_LINES);
       glVertex2f(x1, y1);
       glVertex2f(x2, y2);
       glEnd();

}

void edgeDetect(float x1, float y1, float x2, float y2,
                             int scanline, float intx[], int &count) {

       if (y1 > y2) {
              swap(x1, x2);
              swap(y1, y2);

       }

       // Ignore horizontal edges and avoid double-counting vertices
       if (y1 != y2 && scanline >= y1 && scanline < y2) {

              float xi = x1 + (scanline - y1) *
                                  (x2 - x1) / (y2 - y1);

              intx[count++] = xi;
       }
}
void scanFill() {
       for (int s = 0; s <= 500; s++) {
              float intx[100];
              int count = 0;

              for (int i = 0; i < n; i++) {
                     int j = (i + 1) % n;
                     edgeDetect(x[i], y[i], x[j], y[j],
                                         s, intx, count);

              }

              sort(intx, intx + count);

              // Fill between pairs of intersections
              for (int i = 0; i + 1 < count; i += 2) {

                     drawLine(intx[i], s, intx[i + 1], s);
              }
       }
}

void display() {
       glClear(GL_COLOR_BUFFER_BIT);

       // Fill the polygon
       scanFill();

       // Draw the polygon boundary
       glColor3f(0, 1, 0);
       glLineWidth(2);

       glBegin(GL_LINE_LOOP);
       for (int i = 0; i < n; i++) {

              glVertex2f(x[i], y[i]);
       }
       glEnd();

       glFlush();
}

void myInit() {
       glClearColor(1, 1, 1, 1);

       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(0, 500, 0, 500);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
}

int main(int argc, char** argv) {
       cout << "Enter the number of sides (3-100): ";
       cin >> n;

       if (n < 3 || n > 100) {
              cout << "Invalid number of vertices.\n";
              return 1;

       }

       cout << "Enter the coordinates of vertices (x y):\n";
       for (int i = 0; i < n; i++) {

              cin >> x[i] >> y[i];
       }

       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Scan-Line Area Filling");

       myInit();
       glutDisplayFunc(display);

       glutMainLoop();
       return 0;
}

// ============================================================
// cohen sutherland line clipping algorithm

#include <iostream>
#include <GL/glut.h>
using namespace std;

typedef int outcode;

const int LEFT=8, RIGHT=4, BOTTOM=2, TOP=1;

float xmin,ymin,xmax,ymax;
int n,vx,vy,vw,vh;
float lines[100][4];

outcode compute(float x,float y) {
       int c=0;
       if(y>ymax) c|=TOP;
       else if(y<ymin) c|=BOTTOM;
       if(x>xmax) c|=RIGHT;
       else if(x<xmin) c|=LEFT;
       return c;

}

bool clip(float &x0,float &y0,float &x1,float &y1) {
       int c0=compute(x0,y0), c1=compute(x1,y1);

       while(true) {
              if(!(c0|c1)) return true;
              if(c0&c1) return false;

              float x,y,dx=x1-x0,dy=y1-y0;
              int c=c0?c0:c1;

              if(c&TOP) {
                     y=ymax;
                     x=x0+dx*(ymax-y0)/dy;

              }
              else if(c&BOTTOM) {

                     y=ymin;
                     x=x0+dx*(ymin-y0)/dy;
              }
              else if(c&RIGHT) {

                     x=xmax;
                     y=y0+dy*(xmax-x0)/dx;
              }
              else {
                     x=xmin;
                     y=y0+dy*(xmin-x0)/dx;
              }

              if(c==c0) {
                     x0=x; y0=y; c0=compute(x0,y0);

              }
              else {

                     x1=x; y1=y; c1=compute(x1,y1);
              }
       }
}

void display() {
       glClear(GL_COLOR_BUFFER_BIT);

       // Original lines and clipping window (left side)
       glViewport(0,0,500,600);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(-250,250,-250,250);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       glColor3f(1,0,0);
       glBegin(GL_LINES);
       for(int i=0;i<n;i++) {

              glVertex2f(lines[i][0],lines[i][1]);
              glVertex2f(lines[i][2],lines[i][3]);
       }
       glEnd();

       glColor3f(0,1,0);
       glBegin(GL_LINE_LOOP);
       glVertex2f(xmin,ymin);
       glVertex2f(xmax,ymin);
       glVertex2f(xmax,ymax);
       glVertex2f(xmin,ymax);
       glEnd();

       // Clipped lines in viewport (right side)
       glViewport(vx,vy,vw,vh);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(xmin,xmax,ymin,ymax);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       glColor3f(0,0,1);
       glBegin(GL_LINES);
       for(int i=0;i<n;i++) {

              float x0=lines[i][0],y0=lines[i][1];
              float x1=lines[i][2],y1=lines[i][3];

              if(clip(x0,y0,x1,y1)) {
                     glVertex2f(x0,y0);
                     glVertex2f(x1,y1);

              }
       }
       glEnd();

       glFlush();
}

int main(int argc,char** argv) {
       cout<<"Enter clipping window (xmin ymin xmax ymax): ";
       cin>>xmin>>ymin>>xmax>>ymax;

       cout<<"Enter number of lines: ";
       cin>>n;

       if(xmin>=xmax || ymin>=ymax || n<1 || n>100) {
              cout<<"Invalid input!";
              return 1;
       }

       cout<<"Enter line coordinates (x0 y0 x1 y1):\n";
       for(int i=0;i<n;i++)

              cin>>lines[i][0]>>lines[i][1]
                    >>lines[i][2]>>lines[i][3];

       cout<<"Enter viewport (x y width height): ";
       cin>>vx>>vy>>vw>>vh;

       if(vx<500 || vy<0 || vw<=0 || vh<=0 ||
            vx+vw>1000 || vy+vh>600) {
              cout<<"Invalid viewport!";
              return 1;

       }

       glutInit(&argc,argv);
       glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
       glutInitWindowSize(1000,600);
       glutInitWindowPosition(100,100);
       glutCreateWindow("Cohen Sutherland Line Clipping");

       glClearColor(1,1,1,1);
       glutDisplayFunc(display);
       glutMainLoop();

       return 0;
}

// ============================================================
// liang barsky line clipping algorithm

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

// ============================================================
// sutherland hodgeman polygon clipping algorithm

#include <iostream>
#include <algorithm>
#include <GL/glut.h>
using namespace std;

float xmin, ymin, xmax, ymax;

struct Point {
       float x, y;

};
Point original[100], inp[100], outp[100];
int n, clippedN;

enum Edge { LEFT, TOP, RIGHT, BOTTOM };

void drawPoly(Point p[], int n) {
       if(n < 2) return;

       glLineWidth(3);
       glBegin(GL_LINE_LOOP);
       for(int i = 0; i < n; i++)

              glVertex2f(p[i].x, p[i].y);
       glEnd();
}

bool inside(Point p, int edge) {
       switch(edge) {
              case LEFT: return p.x >= xmin;
              case RIGHT: return p.x <= xmax;
              case BOTTOM: return p.y >= ymin;
              case TOP: return p.y <= ymax;
       }
       return false;

}

Point intersect(Point s, Point p, int edge) {
       float t, x, y;

       if(edge == LEFT || edge == RIGHT) {
              x = (edge == LEFT) ? xmin : xmax;
              t = (x - s.x) / (p.x - s.x);
              y = s.y + t * (p.y - s.y);

       }
       else {

              y = (edge == BOTTOM) ? ymin : ymax;
              t = (y - s.y) / (p.y - s.y);
              x = s.x + t * (p.x - s.x);
       }

       return {x, y};
}

void sutherlandHodgman() {
       copy(original, original + n, inp);
       clippedN = n;

       for(int edge = 0; edge < 4; edge++) {
              int k = 0;
              if(clippedN == 0) break;

              Point s = inp[clippedN - 1];

              for(int j = 0; j < clippedN; j++) {
                     Point p = inp[j];

                     if(inside(p, edge)) {
                             if(!inside(s, edge))
                                    outp[k++] = intersect(s, p, edge);

                             outp[k++] = p;
                     }
                     else if(inside(s, edge)) {

                             outp[k++] = intersect(s, p, edge);
                     }

                     s = p;
              }

              clippedN = k;
              copy(outp, outp + clippedN, inp);
       }
}

void display() {
       glClear(GL_COLOR_BUFFER_BIT);

       // Original polygon - Red
       glColor3f(1, 0, 0);
       drawPoly(original, n);
       // Clipping window - Green
       glColor3f(0, 1, 0);
       glBegin(GL_LINE_LOOP);
       glVertex2f(xmin, ymin);
       glVertex2f(xmax, ymin);
       glVertex2f(xmax, ymax);
       glVertex2f(xmin, ymax);
       glEnd();

       // Clipped polygon - Blue
       sutherlandHodgman();
       glColor3f(0, 0, 1);
       drawPoly(inp, clippedN);

       glFlush();
}

void myInit() {
       glClearColor(1, 1, 1, 1);
       gluOrtho2D(-250, 250, -250, 250);

}

int main(int argc, char** argv) {
       cout << "Enter number of polygon vertices: ";
       cin >> n;

       if(n < 3 || n > 100) {
              cout << "Invalid number of vertices";
              return 0;

       }

       cout << "Enter polygon vertices (x y):\n";
       for(int i = 0; i < n; i++) {

              cin >> original[i].x >> original[i].y;
       }

       cout << "Enter clipping window (xmin ymin xmax ymax): ";
       cin >> xmin >> ymin >> xmax >> ymax;

       if(xmin >= xmax || ymin >= ymax) {
              cout << "Invalid clipping window";
              return 0;
       }

       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Sutherland Hodgman Polygon Clipping");

       myInit();
       glutDisplayFunc(display);
       glutMainLoop();

       return 0;
}

// ============================================================
// house like figure

#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

float m, c, t, xr, yr;

float house[11][2] = {
       {100, 100},
       {140, 100},
       {140, 150},
       {160, 150},
       {160, 100},
       {200, 100},
       {200, 200},
       {220, 200},
       {150, 300},
       {80, 200},
       {100, 200},
};
int n = 11;

void drawHouse() {
       glBegin(GL_LINE_LOOP);
       for(int i = 0; i < n; i++)
              glVertex2fv(house[i]);
       glEnd();
       glFlush();

}

void displayRot() {
       glClear(GL_COLOR_BUFFER_BIT);

       glColor3f(1, 0, 0);
       drawHouse();

       glPushMatrix();
       glTranslatef(xr, yr, 0);
       glRotatef(t, 0, 0, 1);
       glTranslatef(-xr, -yr, 0);

       glColor3f(0, 0, 1);
       drawHouse();
       glPopMatrix();

       glFlush();
}

void displayRef() {
       glClear(GL_COLOR_BUFFER_BIT);

       glColor3f(1, 0, 0);
       drawHouse();

       int x0 = 0, x1 = 400;
       int y0 = m * x0 + c, y1 = m * x1 + c;

       glColor3f(0, 1, 0);
       glBegin(GL_LINES);
       glVertex2f(x0,y0);
       glVertex2f(x1,y1);
       glEnd();

       float r = atan(m) * (180/3.1415);
       glPushMatrix();
       glTranslatef(0, c, 0);
       glRotatef(r, 0, 0, 1);
       glScalef(1, -1, 1);
       glRotatef(-r, 0, 0, 1);
       glTranslatef(0, -c, 0);

       glColor3f(0, 0, 1);
       drawHouse();
       glPopMatrix();

       glFlush();
}

void myInit() {
       glClearColor(1, 1, 1, 1);
       gluOrtho2D(0, 500, 0, 500);

}

int main(int argc, char** argv) {
       int opt;
       cout << "Enter 1 for rotation and 2 for reflection\n";
       cin >> opt;
       if(opt == 1){
              cout << "Enter t, xr, yr\n";
              cin >> t >> xr >> yr;
       }
       if(opt == 2){
              cout << "Enter m, c\n";
              cin >> m >> c;
       }
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("House");

       if(opt == 1)
              glutDisplayFunc(displayRot);

       if(opt == 2)
              glutDisplayFunc(displayRef);

       myInit();
       glutMainLoop();
}

// ============================================================
// cube spinning

#include <GL/glut.h>

float vertices[8][3] = {
       {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
       {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,1}

};

float colors[8][3] = {
       {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
       {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}

};

GLubyte indices[24] = {
       0,1,2,3, 0,6,7,1, 3,4,5,2,
       0,3,4,7, 2,5,6,1, 7,4,5,6

};

float angle = 0;

void display() {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glLoadIdentity();
       glTranslatef(0, 0, -4);
       glRotatef(angle, 1, 1, 1);
       glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

       glutSwapBuffers();
}

void idle() {
       angle += 0.3;
       if(angle >= 360) angle -= 360;
       glutPostRedisplay();

}

void reshape(int w, int h) {
       if(h == 0) h = 1;

       glViewport(0, 0, w, h);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(80, (float)w/h, 0.1, 10);

       glMatrixMode(GL_MODELVIEW);
}

void myInit() {
       glEnable(GL_DEPTH_TEST);

       glEnableClientState(GL_VERTEX_ARRAY);
       glEnableClientState(GL_COLOR_ARRAY);

       glVertexPointer(3, GL_FLOAT, 0, vertices);
       glColorPointer(3, GL_FLOAT, 0, colors);

       glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Spinning Color Cube");
       myInit();
       glutDisplayFunc(display);
       glutIdleFunc(idle);
       glutReshapeFunc(reshape);

       glutMainLoop();
       return 0;
}
