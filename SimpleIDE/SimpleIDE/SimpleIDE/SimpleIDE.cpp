#include <Windows.h>

int CALLBACK wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR szCmdSize, int nCmdShow) {
    MSG msg;
    WNDCLASS mainWindClass = {};
    mainWindClass.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
        };
    mainWindClass.hInstance = hInst;
    mainWindClass.lpszClassName = L"MainWndClass";

    RegisterClass(&mainWindClass);

    HWND hWnd = CreateWindow(L"MainWndClass", L"SimpleWindow", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, hInst, nullptr);

    if (hWnd == NULL)
        return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}