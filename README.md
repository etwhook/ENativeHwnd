
# ENativeHwnd

Natively Enumerating Windows With NtUserBuildHwndList.

## Motives
I initially wanted to understand how **EnumWindows** and other window apis worked under the hood to get to the native functions for enumerating windows that are hookable from the kernel with **Shadow SSDT Hooks**, To hide windows with blacklisted keywords like **x64dbg** or **ReClass** since alot of anti-debug software utilizes this method, This repository serves as a reference for me when i'm working on something involving **NtUserBuildHwndList** hooks, You can use this repository when also working on an **anti-anti debug** tool, Instead of hooking higher level apis like **EnumWindows**, You straight up hook **NtUserBuildHwndList** in **win32u.dll**.

