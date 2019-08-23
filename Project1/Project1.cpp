// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"
#include "windowsx.h"

int g_is_clicked = 0;
RECT g_rect = { 10, 10, 50, 50 };
POINT g_prev_pos;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN) {
		HDC h_dc = GetDC(hWnd);
		HPEN h_pen;

		const char * p_style_string[6] = { "PS_SOLID", "PS_DASH", "PS_DOT", "PS_DASHDOT", "PS_DASHDOTDOT", "PS_NULL" };
		//const char * p_style_string[6] = { L"PS_SOLID", L"PS_DASH", L"PS_DOT", L"PS_DASHDOT", L"PS_DASHDOTDOT", L"PS_NULL" };
		int pen_style[6] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL };
		SetBkMode(h_dc, TRANSPARENT);

		HGDIOBJ h_old_pen = GetCurrentObject(h_dc, OBJ_PEN);

		for (int i = 0; i < 6; i++) {
			TextOutA(h_dc, 10, 10 + i * 20, p_style_string[i], strlen(p_style_string[i]));
			//TextOut(h_dc, 10, 10 + i * 20, p_style_string[i], wcslen(p_style_string[i]));
			h_pen = CreatePen(pen_style[i], 1, RGB(0, 0, 255));
			SelectObject(h_dc, h_pen);

			MoveToEx(h_dc, 200, 15 + i * 20, NULL);
			LineTo(h_dc, 400, 15 + i * 20);

			DeleteObject(h_pen);
		}

		SelectObject(h_dc, h_old_pen);
		ReleaseDC(hWnd, h_dc);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}