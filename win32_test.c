#include <Windows.h>
#include <WinDef.h>
#include <WinGDI.h>
#include "crab_define.h"

renderer* r = 0;
HDC g_hdc;


/*
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	matrix mat, mat1, mat2;

	crab_matrix_scale(&mat1, 2, 3, 4);
	crab_matrix_transform(&mat2, 10, 8, 6);
	crab_matrix_mul(&mat, &mat1, &mat2);

	return 0;
}
*/
void DrawPoint(int x, int y, int color)
{
	SetPixel(g_hdc, x, y, color & 0x00FFFFFF);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("HelloWin");
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,                  // window class name
        TEXT("The Hello Program"), // window caption
        WS_OVERLAPPEDWINDOW,        // window style
        CW_USEDEFAULT,              // initial x position
        CW_USEDEFAULT,              // initial y position
        CW_USEDEFAULT,              // initial x size
        CW_USEDEFAULT,              // initial y size
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
    {
	case WM_CREATE:
		r = create_renderer(640, 480, DrawPoint);
		break;

	case WM_PAINT:
		{
			if (0)
			{
				g_hdc = GetDC(hWnd);

				begin_render(r);
				render(r);
				end_render(r);

				ReleaseDC(hWnd, g_hdc);
				g_hdc = 0;
			}
			else
			{
				HDC hWndDC, hBackbufferDC;
				HBITMAP hBackbuffer;
				RECT rcSize;
				BOOL bRet;
				GetClientRect(hWnd, &rcSize);
				hWndDC = GetDC(hWnd);
				hBackbuffer = CreateCompatibleBitmap(hWndDC, rcSize.right - rcSize.left, rcSize.bottom - rcSize.top);
				hBackbufferDC = CreateCompatibleDC(hWndDC);
				SelectObject(hBackbufferDC, hBackbuffer);
				g_hdc = hBackbufferDC;

				begin_render(r);
				render(r);
				end_render(r);

				bRet = BitBlt(hWndDC, 0, 0, rcSize.right - rcSize.left, rcSize.bottom - rcSize.top,
						hBackbufferDC, 0, 0,
						SRCCOPY);

				//this should be done before exiting the program:
				ReleaseDC(hWnd, hWndDC); //retrieved device contexts are just released
				DeleteDC(hBackbufferDC); //created device contexts must be deleted
				DeleteObject(hBackbuffer); //created objects must be deleted
				g_hdc = 0;
			}
		}
		break;

    case WM_CLOSE:
		destroy_renderer(r);

        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
