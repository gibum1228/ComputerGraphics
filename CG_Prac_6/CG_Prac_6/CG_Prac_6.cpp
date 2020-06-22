#include<glut.h>

static int Day = 0, Time = 0;
static GLboolean isOrtho = true;

void InitLight(void)
{
	GLfloat light0_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 태양의 광원
	GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light1_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat light1_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };

	glShadeModel(GL_SMOOTH);							// 구로 쉐이딩
	glEnable(GL_LIGHTING);								// 조명기능 활성화
	glEnable(GL_DEPTH_TEST);							// 깊이 테스트 활성화
	glEnable(GL_LIGHT0);								// 0번 광원 활성화
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
}

void MyDisplay(void)
{
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light1_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light1_direction[] = { -1.0f, 0.0f, 0.0f, 0.0f };
	GLfloat light1_spot_angle[] = { 60.0 };

	GLfloat earth_ambient[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	GLfloat earth_diffuse[] = { 0.0f, 0.0f, 0.7f, 1.0f };
	GLfloat earth_specular[] = { 0.0f, 0.0f, 0.1f, 1.0f };

	GLfloat moon_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat moon_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat moon_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.3f, 0.3f);
	glutSolidSphere(0.2, 20, 16);						// 1 - 태양 모델
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); // 카메라 좌표계? 월드 좌표계?

	glPushMatrix();										// 2 - 모델뷰 행렬 저장(태양 위치)
	glRotatef((GLfloat)Day, 0.0f, 1.0f, 0.0f);		// 3
	glTranslatef(0.7f, 0.0f, 0.0f);					// 4
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1_spot_angle);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);		// 5
	//glColor3f(0.5f, 0.6f, 0.7f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_specular);

	glutSolidSphere(0.1f, 10, 8);					// 6 - 지구 모델
	glPushMatrix();									// 7 - 모델뷰 행렬 저장(지구 위치)
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);	// 8
	glTranslatef(0.2f, 0.0f, 0.0f);				// 9
	//glColor3f(0.9f, 0.8f, 0.2f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_specular);

	glutSolidSphere(0.04f, 10, 8);				// 10 - 달 모델
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
	case 'D':
		Day = (Day - 10) % 360;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	case 'T':
		Time = (Time - 5) % 360;
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		Day = Time = 0;
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
		glOrtho(-1.0, 1.0, -1.0, 1.0, -3.0, 3.0);
	}
	else
	{
		gluPerspective(60.0, 1.0, 0.5, 10);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// 시점 변환
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	InitLight();

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