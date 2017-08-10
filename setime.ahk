#NoTrayIcon
#NoEnv

;-----------------------------------------------------------
; IME�̏�Ԃ��Z�b�g
;   SetSts          1:ON / 0:OFF
;   WinTitle="A"    �Ώ�Window
;   �߂�l          0:���� / 0�ȊO:���s
;-----------------------------------------------------------
IME_SET(SetSts, WinTitle="A")    {
	ControlGet,hwnd,HWND,,,%WinTitle%
	if	(WinActive(WinTitle))	{
		ptrSize := !A_PtrSize ? 4 : A_PtrSize
	    VarSetCapacity(stGTI, cbSize:=4+4+(PtrSize*6)+16, 0)
	    NumPut(cbSize, stGTI,  0, "UInt")   ;	DWORD   cbSize;
		hwnd := DllCall("GetGUIThreadInfo", Uint,0, Uint,&stGTI)
	             ? NumGet(stGTI,8+PtrSize,"UInt") : hwnd
	}

    return DllCall("SendMessage"
          , UInt, DllCall("imm32\ImmGetDefaultIMEWnd", Uint,hwnd)
          , UInt, 0x0283  ;Message : WM_IME_CONTROL
          ,  Int, 0x006   ;wParam  : IMC_SETOPENSTATUS
          ,  Int, SetSts) ;lParam  : 0 or 1
}

argCount = %0%
IF argCount <> 1
{
    MsgBox [�g����] %A_scriptname% [on / off]
    ExitApp
}

cmd = %1%
If cmd = on
    IME_SET(1)
Else If cmd = off
    IME_SET(0)
Else
    MsgBox [�G���[] �����Ȉ���: %1%

ExitApp
