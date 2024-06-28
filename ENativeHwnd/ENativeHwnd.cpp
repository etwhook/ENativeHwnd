#include <iostream>
#include<vector>
#include <windows.h>

typedef NTSTATUS(NTAPI* t_NtUserBuildHwndList) (
    HDESK  hDesk,
    HWND   hWndNext,
    BOOL   EnumChildren,
    BOOL   RemoveImmersive,
    DWORD  ThreadId,
    DWORD  MaxWindow,
    HWND*  WindowList,
    PDWORD WindowCount
);

t_NtUserBuildHwndList fnNtUserBuildHwndList;

void InitFunc() {
    HMODULE win32u = LoadLibraryA("win32u");
    fnNtUserBuildHwndList = (t_NtUserBuildHwndList)GetProcAddress(win32u, "NtUserBuildHwndList");
}

LPSTR GetWindowTitle(HWND hWindow) {
    char name[256];
    int nameLength = GetWindowTextA(hWindow, name, sizeof(name));

    if (nameLength <= 0)
        return NULL;

    return name;
}
std::vector<HWND> GetWindows() {

    std::vector<HWND> windows;

    DWORD windowCount = 0;
    fnNtUserBuildHwndList(NULL, 0, 0, 0, 0, 0, 0, &windowCount);

    HWND* windowMem = (HWND*)malloc(windowCount * sizeof(HWND));

    fnNtUserBuildHwndList(NULL, 0, 0, 0, 0, windowCount, windowMem, &windowCount);

    for (size_t i = 0; i < windowCount; i++)
    {
        HWND foundWindow = (HWND)(windowMem[i]);

        if (!foundWindow)
            continue;

        windows.push_back(
            foundWindow
        );

    }

    return windows;
}

int main()
{
    InitFunc();

    auto windows = GetWindows();

    for (HWND& hWindow : windows) {

        LPSTR windowName = GetWindowTitle(hWindow);

        if (!windowName)
            continue;

        printf("Window Title: %s\n", windowName);
    }
    
    getchar();
}
