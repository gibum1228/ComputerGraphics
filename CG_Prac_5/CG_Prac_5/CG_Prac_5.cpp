#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

static int Day = 0, Time = 0;
static GLboolean isOrtho = true;

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.3f, 0.3f);
	glutWireSphere(0.2, 20, 16);						// 1
	glPushMatrix();										// 2 - 모델뷰 행렬 저장(태양 위치)
	glRotatef((GLfloat)Day, 0.0f, 1.0f, 0.0f);		// 3
	glTranslatef(0.7f, 0.0f, 0.0f);					// 4
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);		// 5
	glColor3f(0.5f, 0.6f, 0.7f);
	glutWireSphere(0.1f, 10, 8);					// 6
	glPushMatrix();									// 7 - 모델뷰 행렬 저장(지구 위치)
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);	// 8
	glTranslatef(0.2f, 0.0f, 0.0f);				// 9
	glColor3f(0.9f, 0.8f, 0.2f);
	glutWireSphere(0.04f, 10, 8);				// 10
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	GLint MyMenuID = glutCreateMenu(MyMenu);
	glutAddMenuEntry("Parallel Projection", 1);
	glutAddMenuEntry("Perspective Projection", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;
}