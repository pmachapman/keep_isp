/************************************************************
	keep_isp.cpp
    Pings the ISP on regular intervals to avoid timeout.
	Written by Scott Zimmerman
	December 1996
************************************************************/
#include <windows.h>
#include "keep_isp.h"

HINSTANCE hInst;          // current instance
HWND g_hWnd;
char szAppName[] = "Keep_ISP"; // The name of this application
char szTitle[]   = "Keep_ISP"; // The title bar text
char szIP[20];
int bCmdBeep = FALSE;		// default = no beeps
int nMinutesCmd = 10;		// default time interval = 10 minutes
int	nMinutesElapsed = 0;

BOOL InitApplication(void);
BOOL InitInstance(void);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR szCmd, int nCmdShow)
{
	MSG		msg;
	LPSTR	p;
	char	buf[20];

	// Check if the command line includes -b to beep
	if (strstr(szCmd, "-b"))
		bCmdBeep = TRUE;

	// Check if the cmd line includes a time to ping in minutes
	p = strstr(szCmd, "-n");
	if (p != NULL)
	{
		buf[0] = *(p + 2);
		buf[1] = *(p + 3);
		buf[2] = 0;
		nMinutesCmd = atoi(buf);
	}

	// The IP address must be the last switch on the command line
	p = strstr(szCmd, "-a");
	if (p == NULL)
	{
		MessageBox(0,"Missing -a for IP address", "Error", 0);
		return FALSE;
	}
	strcpy(szIP, p+2);

	hInst = hInstance;
	if (!hPrevInstance)
	{
		if (!InitApplication())
	            return FALSE;  // Exit if unable to initialize
	}

	if (!InitInstance())
	    return FALSE;

	UpdateWindow(g_hWnd);
	ShowWindow(g_hWnd, SW_SHOWMINIMIZED);

	while (GetMessage(&msg,	NULL, 0, 0))
	{
		TranslateMessage(&msg);// Translates virtual key codes
	  DispatchMessage(&msg); // Dispatches message to window
	}

	return (msg.wParam); // Returns the value from PostQuitMessage
}

BOOL InitApplication(void)
{
        WNDCLASS  wc;

        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc   = (WNDPROC)WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInst;          		// Owner of this class
        wc.hIcon         = LoadIcon (hInst, MAKEINTRESOURCE(IDI_APP));
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = szAppName;

        // Register the window class and return success/failure code.
        return (RegisterClass(&wc));
}

BOOL InitInstance(void)
{
        // Create a main window for this application instance.
        g_hWnd = CreateWindow(szAppName,
                szTitle,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                NULL,
                NULL,
                hInst,
                NULL);

        // If window could not be created, return "failure"
        return (BOOL)g_hWnd;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM uParam,LPARAM lParam)
{
	char	buf[100];

	switch (message)
	{
		case WM_CREATE:
			if (SetTimer(hWnd, 1, 60000, NULL) == 0)
			{
				MessageBox(0, "Error starting timer.", "Keep_ISP", 0);
				PostQuitMessage(0);
				break;
			}
			return (DefWindowProc(hWnd, message, uParam, lParam));

		case WM_TIMER:
			if (++nMinutesElapsed % nMinutesCmd == 0)
			{
				// Execute the DOS Ping program
				wsprintf(buf, "PING.EXE -n 1 -l 10 %s", (LPSTR)szIP);
				WinExec(buf, SW_HIDE);
				if (bCmdBeep)
					MessageBeep(-1);
				nMinutesElapsed = 0;
			}
			break;

		case WM_DESTROY:  // message: window being destroyed
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			break;

		default:          // Passes it on if unproccessed
			return (DefWindowProc(hWnd, message, uParam, lParam));
	}
	return (0);
}
