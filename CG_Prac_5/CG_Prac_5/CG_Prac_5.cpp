#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

static int day = 0, time = 0;
GLboolean isParallel = true;

void myDisplay() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16); // �¾� �׸���
	glPushMatrix(); // ������ �� ��ǥ�踦 ���ÿ� Ǫ���Ͽ� ����
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0); // �� �� ��ǥ�踦 y���� �������� ���� day��ŭ ȸ����Ų �� 0.7��ŭ ���������� �̵���Ű�� ���� (4�� ����) !3, 4 ���� �ٲ�� �� ��
		glTranslatef(0.7, 0.0, 0.0); // 4
		glRotatef((GLfloat)time, 0.0, 5.0, 0.0); // ���� time��ŭ ȸ�� ( ���� ������ ���� ��)
		glColor3f(0.5, 0.6, 0.7);
		glutWireSphere(0.1, 10, 8); // ������ �� ��ǥ�� Me�� ������ �׸���
		glPushMatrix(); // ���� �� ��ǥ�踦 ����
			glRotatef((GLfloat)time, 0.0, 5.0, 0.0); // �� ���� �� ��ǥ�踦 ȸ����Ű�� y���� �������� ���� time��ŭ ȸ��
			glTranslatef(0.2, 0.0, 0.0); // �� ����� ���� �� ��ǥ�� Mm ����
			glColor3f(0.9, 0.9, 0.2);
			glutWireSphere(0.04, 10, 8); // ���� �׷�����
		glPopMatrix();
	glPopMatrix();

	if (!isParallel) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else {
		glFrustum(-5.0, 5.0, -5.0, 5.0, 200.0, 1000.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	glutSwapBuffers();
	glFlush();
}

void myMainMenu(int entryID) {
	if (entryID == 1) {
		isParallel = true;
	}
	else if (entryID == 2) {
		isParallel = false;
	}
	else if (entryID == 3) {
		exit(0);
	}

	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd': // d�� ���� ������ ����
		day = (day + 10) % 360;
		glutPostRedisplay();
		break;
	case 't': // t�� ���� ������ ����
		time = (time + 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, 500, 400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	GLint myMainMenuID = glutCreateMenu(myMainMenu);
	glutAddMenuEntry("Parallel", 1);
	glutAddMenuEntry("Perspective", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();

	return 0;
}