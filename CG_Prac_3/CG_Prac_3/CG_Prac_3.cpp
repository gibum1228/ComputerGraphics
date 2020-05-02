#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

GLboolean IsSphere = true;
GLboolean IsSmall = true;
GLboolean IsWire = true;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.0, 0.5);

	if ((IsSphere) && (IsSmall) && (IsWire)) {
		glutWireSphere(0.2, 15, 15); // ���� ����
	}
	else if((IsSphere) && (!IsSmall) && (IsWire)){
		glutWireSphere(0.4, 15, 15); // ū ����
	}
	else if ((!IsSphere) && (IsSmall) && (IsWire)) {
		glutWireTorus(0.1, 0.3, 40, 20); // ���� ��ȯü
	}
	else if((!IsSphere) && (!IsSmall) && (IsWire)){
		glutWireTorus(0.2, 0.5, 40, 20); // ū ��ȯü
	}
	else if ((IsSphere) && (IsSmall) && (!IsWire)) {
		glutSolidSphere(0.2, 15, 15); // �� �� ���� ����
	}
	else if ((IsSphere) && (!IsSmall) && (!IsWire)) {
		glutSolidSphere(0.4, 15, 15); // �� �� ū ����
	}
	else if ((!IsSphere) && (IsSmall) && (!IsWire)) {
		glutSolidTorus(0.1, 0.3, 40, 20); // �� �� ���� ��ȯü
	}
	else if((!IsSphere) && (!IsSmall) && (!IsWire)){
		glutSolidTorus(0.2, 0.5, 40, 20); // �� �� ū ��ȯü
	}

	glFlush();
}

void MyMainMenu(int entryID) {
	if (entryID == 1) {
		IsSphere = true; // ���� �׸���
	}
	else if (entryID == 2) {
		IsSphere = false; // ��ȯü �׸���
	}
	else if (entryID == 3) {
		exit(0); // ���α׷� ����
	}

	glutPostRedisplay();
}

void MySubMenu(int entryID) {
	if (entryID == 1) {
		IsSmall = true; // ���� ũ��� �׸���
	}
	else if (entryID == 2) {
		IsSmall = false; // ū ũ��� �׸���
	}
	else if (entryID == 3) {
		IsWire = true; // ���̾�� �׸���
	}
	else if (entryID == 4) {
		IsWire = false; // �ָ���� �׸���
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	GLint MySubMenuID = glutCreateMenu(MySubMenu);
	glutAddMenuEntry("Small One", 1);
	glutAddMenuEntry("Big One", 2);
	glutAddMenuEntry("Wire", 3);
	glutAddMenuEntry("Solid", 4);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddSubMenu("Mode", MySubMenuID);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}