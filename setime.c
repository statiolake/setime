#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <assert.h>

HWND get_hwnd();
int ime_get();
void ime_set(int on);

void usage();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 0;
    }
    if (strcmp(argv[1], "on") == 0) {
        ime_set(1);
    } else if (strcmp(argv[1], "off") == 0) {
        ime_set(0);
    } else if (strcmp(argv[1], "get") == 0) {
        return ime_get();
    } else {
        usage();
    }
    return 0;
}

HWND get_hwnd() {
    return GetForegroundWindow();
}

int ime_get() {
    HWND hwnd = get_hwnd();
    return SendMessage(ImmGetDefaultIMEWnd(hwnd), WM_IME_CONTROL, 0x0005, 0);
}

void ime_set(int on) {
    HWND hwnd = get_hwnd();

    // 0x0006 : IMC_SETOPENSTATUS
    SendMessage(ImmGetDefaultIMEWnd(hwnd), WM_IME_CONTROL, 0x0006, on);
}

void usage() {
    MessageBox(NULL, _T("setime [on / off / get]"), _T("使い方"), MB_OK);
}