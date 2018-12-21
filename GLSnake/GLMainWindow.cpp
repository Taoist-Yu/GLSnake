#include "GLMainWindow.h"
#include <iostream>

#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"

#include "Ball.h"

LRESULT CALLBACK GLMainWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

GLMainWindow::GLMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
	InitGLWindow();
}

GLMainWindow::GLMainWindow(int width, int height, HINSTANCE hInstance, int nCmdShow)
	: GLMainWindow(hInstance, nCmdShow)
{
	SetHeight(height);
	SetWidth(width);
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
}

GLMainWindow::~GLMainWindow()
{
	DisableOpenGL(hwnd, hDC, hRC);
	DestroyWindow(hwnd);
}

void GLMainWindow::SetHeight(int height)
{
	this->height = height;
}

void GLMainWindow::SetWidth(int width)
{
	this->width = width;
}

int GLMainWindow::InitGLWindow()
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return -1;

	hwnd = CreateWindowEx(0,
		L"GLSample",
		L"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);
	EnableOpenGL(hwnd, &hDC, &hRC);
	return 0;
}

void* GLMainWindow::GetGLFunctionAddress(const char * name)
{
	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}

	return p;
}

void GLMainWindow::EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	*hDC = GetDC(hwnd);

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
	gladLoadGLLoader((GLADloadproc)GetGLFunctionAddress);
	//Default enable depth test
	glEnable(GL_DEPTH_TEST);
}

void GLMainWindow::DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

int GLMainWindow::MainLoop()
{
	ShowWindow(hwnd, nCmdShow);

	Shader shader("shader.vert", "shader.frag");
	Scene scene;
	GameObject human(&scene, "model/nanosuit/nanosuit.obj", shader);
	GameObject plane(&scene, "model/GrassPlane/Grass.obj", shader);
	Ball ball(&scene);
	Camera camera(&scene, &human);

	plane.transform.Scale(100, 1, 100);
	plane.transform.Translate(0, -0.5f, 0);
	ball.transform.Translate(-3, 2, 0);
	camera.transform.Translate(0, 20, 20);
	camera.transform.Rotate(-30, 0, 0);

	camera.Update();
	camera.Activate();


	while (!isQuit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//Timer
			Time.TimerUpdate();
			//Render
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.aspectRatio = (float)this->width / (float)this->height;
			scene.FrameCycle();

			SwapBuffers(hDC);
		}
	}
	DisableOpenGL(hwnd, hDC, hRC);
	DestroyWindow(hwnd);

	return msg.wParam;
}

