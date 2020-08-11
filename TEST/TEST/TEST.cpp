#include <gl/GLAux.h>
#include <gl/glut.h>

#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

int IsWire = false;

GLUquadric *g_ObjSolid = NULL;
GLUquadric *g_ObjWire = NULL;
GLuint g_TextureEarth = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Áö±¸
	if (IsWire)
		gluSphere(g_ObjWire, 0.5, 20, 16);
	else
	{
		glBindTexture(GL_TEXTURE_2D, g_TextureEarth);
		gluSphere(g_ObjSolid, 0.5, 20, 16);
	}

	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		IsWire = true;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		IsWire = false;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void loadEarthTexture(void)
{
	AUX_RGBImageRec *pTextureImage = auxDIBImageLoad(".\\earth.bmp");

	if (pTextureImage != NULL)
	{
		glGenTextures(1, &g_TextureEarth);

		glBindTexture(GL_TEXTURE_2D, g_TextureEarth);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	if (pTextureImage != NULL)
	{
		if (pTextureImage->data != NULL)
			free(pTextureImage->data);

		free(pTextureImage);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	g_ObjSolid = gluNewQuadric();
	gluQuadricNormals(g_ObjSolid, GLU_SMOOTH);
	gluQuadricOrientation(g_ObjSolid, GLU_OUTSIDE);
	gluQuadricDrawStyle(g_ObjSolid, GLU_FILL);
	gluQuadricTexture(g_ObjSolid, GL_TRUE);

	g_ObjWire = gluNewQuadric();
	gluQuadricDrawStyle(g_ObjWire, GLU_LINE);

	glEnable(GL_TEXTURE_2D);
	loadEarthTexture();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();

	return 0;
}