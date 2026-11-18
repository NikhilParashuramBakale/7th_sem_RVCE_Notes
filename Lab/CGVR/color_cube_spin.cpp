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
