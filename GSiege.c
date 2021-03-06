#include "includes.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	timeBeginPeriod(SLEEPMIN);
	SKQueInit();

	memset(&g_GlobalSettings, 0, sizeof(g_GlobalSettings));
	memset(&g_UserSettings, 0, sizeof(g_UserSettings));

	g_UserSettings.MajorVersion = GSIEGE_MAJOR_VERSION;
	g_UserSettings.MinorVersion = GSIEGE_MINOR_VERSION;

	// Initialise global variables
	g_GlobalSettings.hInstance = hInstance;
	g_GlobalSettings.hPrevInstance = hPrevInstance;
	g_GlobalSettings.nCmdShow = nCmdShow;
	g_GlobalSettings.dwThreadId = 0;

	// Set font
	g_GlobalSettings.hFont = CreateFont(11,6,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
	g_GlobalSettings.hBoldFont = CreateFont(11,6,0,0,FW_BOLD,0,0,0,0,0,0,0,0,TEXT("Tahoma"));

	// Build windows
	LoadSettings();
	MainWindowClassBuilder();
	TabWindowClassBuilder();
	FlameRamFormBuilder();
	CatapultFormBuilder();
	TrebuchetFormBuilder();
	ChatWindowClassBuilder();
	FlameRamToggleElements();

	// Start main procedure loop
	while ( GetMessage(&msg, NULL, 0, 0) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Cleanup before exit
	if ( g_GlobalSettings.dwThreadId )
		TerminateThread(g_GlobalSettings.hThread, 0);
	if ( g_GlobalSettings.dwIdleThreadId )
		TerminateThread(g_GlobalSettings.hIdleThread, 0);
	DeleteObject(g_GlobalSettings.hFont);
	DeleteObject(g_GlobalSettings.hBoldFont);

	timeEndPeriod(SLEEPMIN);

	return msg.wParam;
}
