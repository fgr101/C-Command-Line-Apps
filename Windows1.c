#include <windows.h>


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
 PSTR szCmdLine, int iCmdShow)

{
 MessageBox (NULL, TEXT ("I Can change this text and write whatever I want here to be shown in the window... Nice!"), TEXT ("HERE GOES THE WINDOW TITLE"), MB_RETRYCANCEL ) ;
 return 0 ;

//The fourth argument to MessageBox can be a combination of constants beginning with the prefix MB_
//that are defined in WINUSER.H. You can pick one constant from the first set to indicate what buttons
//you wish to appear in the dialog box:

//MB_OK
//MB_OKCANCEL
//MB_ABORTRETRYIGNORE
//MB_YESNOCANCEL
//MB_YESNO
//MB_RETRYCANCEL

// When you set the fourth argument to 0 in HELLOMSG, only the OK button appears.
//You can also use a constant that indicates the appearance of an icon in the message box:

// #define MB_ICONHAND 0x00000010L
// #define MB_ICONQUESTION 0x00000020L
// #define MB_ICONEXCLAMATION 0x00000030L
// #define MB_ICONASTERISK 0x00000040L

// Some of these icons have alternate names:

// #define MB_ICONWARNING MB_ICONEXCLAMATION
// #define MB_ICONERROR MB_ICONHAND
// #define MB_ICONINFORMATION MB_ICONASTERISK
// #define MB_ICONSTOP MB_ICONHAND

}
