#include <Windows.h>
#include <WinDef.h>
#include <WinGDI.h>
#include "crab_define.h"

renderer* r = 0;
void* pixel_buffer = 0;


void DrawPoint(int x, int y, int color)
{
	int* buf = pixel_buffer;
	if (y * r->screen_sx + x < r->screen_sx * r->screen_sy)
		buf[y * r->screen_sx + x] = color;
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
        TEXT("crab_soft3d"), // window caption
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
		{
			RECT rc;
			GetClientRect(hWnd, &rc);
			r = create_renderer(rc.right - rc.left, rc.bottom - rc.top, DrawPoint);
		}
		break;

	case WM_PAINT:
		{
			HDC hWndDC, hBackbufferDC;
			HBITMAP hBitmap, hBitmapBack;
			BITMAPINFO bm;
			RECT rcSize;
			BOOL bRet;
			GetClientRect(hWnd, &rcSize);
			hWndDC = GetDC(hWnd);
			hBackbufferDC = CreateCompatibleDC(hWndDC);

			bm.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bm.bmiHeader.biWidth = r->screen_sx;
			bm.bmiHeader.biHeight = r->screen_sy;
			bm.bmiHeader.biPlanes = 1;
			bm.bmiHeader.biBitCount =32;             // four 8-bit components
			bm.bmiHeader.biCompression = BI_RGB;
			bm.bmiHeader.biSizeImage =r->screen_sx*r->screen_sy*4 ;
			hBitmap = CreateDIBSection(hWndDC, &bm, DIB_RGB_COLORS, &pixel_buffer, 0, 0);
			hBitmapBack = SelectObject(hBackbufferDC, hBitmap);

			begin_render(r);
			render(r);
			end_render(r);

			bRet = BitBlt(hWndDC, 0, 0, r->screen_sx, r->screen_sy,
					hBackbufferDC, 0, 0,
					SRCCOPY);

			SelectObject(hBackbufferDC, hBitmapBack);
			ReleaseDC(hWnd, hWndDC); //retrieved device contexts are just released
			DeleteDC(hBackbufferDC); //created device contexts must be deleted
			DeleteObject(hBitmap); //created objects must be deleted
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
