#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszClassName = ChildClassName;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass,			//윈도우클래스 이름
		L"윈도우 프로그래밍",					//윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
		200, 200,							//윈도우가 보일때 X Y좌표
		600, 600,							//윈도우의 폭과 높이				
		(HWND)NULL,							//부모윈도우 핸들
		(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
		hInstance,							//인스턴스핸들
		NULL);								//여분의 데이터

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
	switch (iMessage) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		HWND hChildWnd = CreateWindow(
			ChildClassName,						//윈도우클래스 이름
			L"차일드 윈도우",						//윈도우타이틀
			WS_OVERLAPPEDWINDOW | WS_CHILD,		//윈도우스타일
			150, 150,							//윈도우가 보일때 X Y좌표
			260, 200,							//윈도우의 폭과 높이				
			hWnd,								//부모윈도우 핸들
			(HMENU)2000,						//차일드 윈도우가 가지는 메뉴핸들
			g_hInst,							//인스턴스핸들
			(LPVOID)NULL						//여분의 데이터
		);
		if (!hChildWnd) return -1;

		ShowWindow(hChildWnd, SW_SHOW);			//차일드 윈도우를 화면에 보여준다.
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage,	WPARAM wParam, LPARAM lParam)
{
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}