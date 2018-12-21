#pragma once
#include <Windows.h>
#include <glad/glad.h>
#include<list>

#include "Shader.h"

class GLMainWindow
{
public:
	GLMainWindow(HINSTANCE hInstance, int nCmdShow);
	GLMainWindow(int width,int height,HINSTANCE hInstance, int nCmdShow);
	~GLMainWindow();

public:
	void SetHeight(int height);
	void SetWidth(int width);

	int MainLoop();

private:
	static void* GetGLFunctionAddress(const char* name);
	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
	void DisableOpenGL(HWND, HDC, HGLRC);
	int InitGLWindow();

private:
	int height = 600;
	int width = 800;

	HINSTANCE hInstance;
	int nCmdShow;
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	bool isQuit = false;

};

