#include <glut.h>

static int Day = 0, Time = 0;
static GLboolean isOrtho = true;

void MyDisplay(void)
{
	GLfloat LightPosition0[] = { 0.0, 0.0, 0.65, 1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);

	glColor3f(1.0f, 0.3f, 0.3f);
	glutSolidSphere(0.27, 20, 16);						// 1
	glPushMatrix();										// 2 - �𵨺� ��� ����(�¾� ��ġ)
	glRotatef((GLfloat)Day, 0.0f, 1.0f, 0.0f);		// 3
	glTranslatef(0.7f, 0.0f, 0.0f);					// 4
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);		// 5
	glColor3f(0.5f, 0.6f, 0.7f);
	glutSolidSphere(0.12f, 10, 8);					// 6
	glPushMatrix();									// 7 - �𵨺� ��� ����(���� ��ġ)
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);	// 8
	glTranslatef(0.2f, 0.0f, 0.0f);				// 9
	glColor3f(0.9f, 0.8f, 0.2f);
	glutSolidSphere(0.05f, 10, 8);				// 10
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		Day = (Day + 10) % 360;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void Projection(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (isOrtho)
	{
		glOrtho(-2.0, 2.0, -2.0, 2.0, -3.0, 3.0);
	}
	else
	{
		gluPerspective(120.0, 1.0, 0.5, 10);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void MyMenu(int entryID)
{
	switch (entryID)
	{
	case 1:
		isOrtho = true;
		Projection();
		glutPostRedisplay();
		break;
	case 2:
		isOrtho = false;
		Projection();
		glutPostRedisplay();
		break;
	default:
		exit(1);
		break;
	}
}

void MyReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Projection();
}

void MyLightInit() {
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // ���� �ֺ� �ݻ�

	GLfloat light0_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // 0�� ���� Ư��
	GLfloat light0_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat material_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // ��ü Ư��
	GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat material_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat material_shininess[] = { 60.0f };

	glShadeModel(GL_SMOOTH); // ���� ���̵�
	glEnable(GL_DEPTH_TEST); // ���� ���� Ȱ��ȭ
	glEnable(GL_LIGHTING); // ���� ��� Ȱ��ȭ
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // 0�� ���� Ư��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8);
	glEnable(GL_LIGHT0); // 0�� ���� Ȱ��ȭ

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse); // ��ü Ư��
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // ���� �ֺ���
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // ���� ����
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLint MyMenuID = glutCreateMenu(MyMenu);
	glutAddMenuEntry("Parallel Projection", 1);
	glutAddMenuEntry("Perspective Projection", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	MyLightInit();

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;
}