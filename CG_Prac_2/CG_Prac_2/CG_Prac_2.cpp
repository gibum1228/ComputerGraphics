#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(200, 150, 200, 150);
	glColor3f(1.0, 1.0, 1.0);
	
	glutWireTeapot(0.5);
	
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 680);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}