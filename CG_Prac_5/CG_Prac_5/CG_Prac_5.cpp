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
	glutWireSphere(0.2, 20, 16); // 태양 그리기
	glPushMatrix(); // 현재의 모델 좌표계를 스택에 푸시하여 저장
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0); // 현 모델 좌표계를 y축을 기준으로 각도 day만큼 회전시킨 후 0.7만큼 오른쪽으로 이동시키는 과정 (4도 동일) !3, 4 순서 바뀌면 안 됨
		glTranslatef(0.7, 0.0, 0.0); // 4
		glRotatef((GLfloat)time, 0.0, 5.0, 0.0); // 각도 time만큼 회전 ( 지구 자전을 위한 것)
		glColor3f(0.5, 0.6, 0.7);
		glutWireSphere(0.1, 10, 8); // 지구의 모델 좌표계 Me에 지구를 그리기
		glPushMatrix(); // 지구 모델 좌표계를 저장
			glRotatef((GLfloat)time, 0.0, 5.0, 0.0); // 현 지구 모델 좌표계를 회전시키되 y축을 기준으로 각도 time만큼 회전
			glTranslatef(0.2, 0.0, 0.0); // 이 결과로 달의 모델 좌표계 Mm 생성
			glColor3f(0.9, 0.9, 0.2);
			glutWireSphere(0.04, 10, 8); // 달을 그려내기
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
	case 'd': // d를 누를 때마다 공전
		day = (day + 10) % 360;
		glutPostRedisplay();
		break;
	case 't': // t를 누를 때마다 자전
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