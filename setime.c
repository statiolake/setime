#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <assert.h>

HWND get_immhwnd();
int ime_get(HWND immhwnd);
void ime_set(HWND immhwnd, int on);

void usage();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 0;
    }

    HWND immhwnd = get_immhwnd();
    if (strcmp(argv[1], "on") == 0) {
        ime_set(immhwnd, 1);
    } else if (strcmp(argv[1], "off") == 0) {
        ime_set(immhwnd, 0);
    } else if (strcmp(argv[1], "get") == 0) {
        return ime_get(immhwnd);
    } else {
        usage();
    }
    return 0;
}

HWND get_immhwnd() {
    return ImmGetDefaultIMEWnd(GetForegroundWindow());
}

int ime_get(HWND immhwnd) {
    // 0x0005 : IMC_GETOPENSTATUS
    return SendMessage(immhwnd, WM_IME_CONTROL, 0x0005, 0);
}

void ime_set(HWND immhwnd, int on) {
    // 0x0006 : IMC_SETOPENSTATUS
    SendMessage(immhwnd, WM_IME_CONTROL, 0x0006, on);
}

void usage() {
    MessageBox(NULL, _T("setime [on / off / get]"), _T("使い方"), MB_OK);
}