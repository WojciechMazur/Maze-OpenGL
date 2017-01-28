#pragma once

#include "GLUT.h"

using namespace BasicEngine::Core::Init;

BasicEngine::Core::IListener* GLUT::listener = NULL;
BasicEngine::Core::WindowInfo GLUT::windowInformation;

extern BasicEngine::Camera* activeCamera;

void BasicEngine::Core::Init::GLUT::init(const BasicEngine::Core::WindowInfo & window, const Core::ContextInfo & context, const Core::FramebufferInfo & framebufferInfo)
{
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);
	windowInformation = window;


	if (context.core) {
		glutInitContextVersion(context.majorVersion, context.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(window.position_x, window.position_y);
	glutInitWindowSize(window.width, window.height);

	//glutInitContextFlags(GLUT_DEBUG);
	//glEnable(GL_DEBUG_OUTPUT);

	

	glutCreateWindow(window.name.c_str());
	std::cout << "GLUT: Initialized" << std::endl;
	glEnable(GL_DEBUG_OUTPUT);
	glutIdleFunc(IdleCallback);
	glutCloseFunc(CloseCallback);
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutPassiveMotionFunc(MouseMotionCallback);
	glutSpecialFunc(SpecialKeysInputCallback);
	glutKeyboardFunc(KeysInputCallback);

	Core::Init::GLEW::Init();

	if (GL_DEBUG_OUTPUT)
		std::cout << "Debug output supported" << std::endl;
	glDebugMessageCallback(DebugOutput::errorCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetCursor(GLUT_CURSOR_NONE);
	printOpenGLInfo(window, context);
}


void GLUT::run() {
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void GLUT::close() {
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void GLUT::IdleCallback(void)
{
	//Do nothing

	glutPostRedisplay();
}

void GLUT::DisplayCallback()
{
	if (listener) {
		listener->NotifyBeginFrame();
		listener->NotifyDisplayFrame();
		glutSwapBuffers();
		listener->NotifyEndFrame();
	}
}

void GLUT::ReshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener) 
			listener->NotifyReshape(width, height, windowInformation.width, windowInformation.height);
		windowInformation.width = width;
		windowInformation.height = height;
	}
}


void GLUT::CloseCallback() {
	close();
}

void GLUT::MouseMotionCallback(int x, int y)
{
	activeCamera->mouseUpdate(x, y);
}

void GLUT::SpecialKeysInputCallback(int key, int x, int y)
{
	activeCamera->specialKeysInput(key, x, y);
}

void GLUT::KeysInputCallback(unsigned char key, int x, int y)
{
	activeCamera->normalKeysInput(key, x, y);
}


void BasicEngine::Core::Init::GLUT::setListener(Core::IListener* iListener)
{
	listener = iListener;
}

void GLUT::enterFullscreen()
{
	glutFullScreen();
}

void GLUT::exitFullscreen() {
	glutLeaveFullScreen();
}



void GLUT::printOpenGLInfo(const BasicEngine::Core::WindowInfo& windowInfo,
	const BasicEngine::Core::ContextInfo& contextInfo)
{

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "*******************************************************************************" << std::endl;

	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "GLUT:\tInitial window is '" << windowInfo.name << "', with dimensions (" << windowInfo.width
		<< "X" << windowInfo.height;
	std::cout << ") starts at (" << windowInfo.position_x << "X" << windowInfo.position_y;
	std::cout << ") and " << ((windowInfo.isReshapable) ? "is" : "is not ") << " redimensionable" << std::endl;
	std::cout << "GLUT:\tInitial Framebuffer contains double buffers for" << std::endl;

	std::cout << "GLUT:\t OpenGL context is " << contextInfo.majorVersion << "." << contextInfo.minorVersion;
	std::cout << " and profile is " << ((contextInfo.core) ? "core" : "compatibility") << std::endl;

	std::cout << "*****************************************************************" << std::endl;
}