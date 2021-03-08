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

	hWnd = CreateWindow(lpszClass,			//������Ŭ���� �̸�
		L"������ ���α׷���",					//������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
		200, 200,							//�����찡 ���϶� X Y��ǥ
		600, 600,							//�������� ���� ����				
		(HWND)NULL,							//�θ������� �ڵ�
		(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
		hInstance,							//�ν��Ͻ��ڵ�
		NULL);								//������ ������

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
	LPCTSTR text = L"���������� ����";
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
			ChildClassName,						//������Ŭ���� �̸�
			L"���ϵ� ������",						//������Ÿ��Ʋ
			WS_OVERLAPPEDWINDOW | WS_CHILD,		//�����콺Ÿ��
			150, 150,							//�����찡 ���϶� X Y��ǥ
			260, 200,							//�������� ���� ����				
			hWnd,								//�θ������� �ڵ�
			(HMENU)2000,						//���ϵ� �����찡 ������ �޴��ڵ�
			g_hInst,							//�ν��Ͻ��ڵ�
			(LPVOID)NULL						//������ ������
		);
		if (!hChildWnd) return -1;

		ShowWindow(hChildWnd, SW_SHOW);			//���ϵ� �����츦 ȭ�鿡 �����ش�.
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