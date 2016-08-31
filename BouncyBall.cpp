#include "stdafx.h"
#include <windows.h> 
#include <stdio.h> 
#include <iostream>
#include "SDKDLL.h"
#include <string>
#include <chrono>
#include <thread>
#include <signal.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
BYTE r = 0;
BYTE g = 0;
BYTE b = 0;
BYTE R = 255;
BYTE G = 255;
BYTE B = 255;
BYTE Rs = 100;
BYTE Gs = 100;
BYTE Bs = 100;
bool exiter = false;
// sequence of LEDs that the ball goes around
int row[30] = { 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 4, 2, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3 };
int col[30] = { 0, 2, 4, 5, 6, 7, 8, 10, 11, 14, 15, 16, 17, 18, 17, 16, 15, 14, 11, 10, 8, 7, 6, 4, 4, 3, 2 };
void ball(){



	int workaround = 18;
	SetFullLedColor(r, g, b);
	for (int x = 0; x < 27; x++){

		SetLedColor(row[x], col[x], R, G, B);
		// Does the trailing leds with lighter and ligher brightness intensity
		if (x > 0){
			SetLedColor(row[x - 1], col[x - 1], R / 1.5, G / 1.5, B / 1.5);
		}
		if (x > 1){
			SetLedColor(row[x - 2], col[x - 2], R / 2, G / 2, B / 2);
		}
		if (x > 2){
			SetLedColor(row[x - 3], col[x - 3], R / 4, G / 4, B / 4);
		}
		if (x > 3){
			SetLedColor(row[x - 4], col[x - 4], R / 8, G / 8, B / 8);
		}
		if (x > 4){
			SetLedColor(row[x - 5], col[x - 5], r, g, b);
		}



		Sleep(50);

	}


}
// code that allows you to quit the program at any moment without windows error
BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		Beep(750, 300);
		::exiter = true;
		return(TRUE);

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		Beep(600, 200);
		printf("Ctrl-Close event\n\n");
		EnableLedControl(false);
		return(TRUE);

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return FALSE;

	case CTRL_LOGOFF_EVENT:
		Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}

int main(void)
{
	SetControlDevice(DEV_MKeys_M_White);

	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		printf("\nThe Bouncy Ball is now in play!.\n");

	}
	EnableLedControl(true);
	while (::exiter == false){



		ball();//the function that does the work

		
	}
	EnableLedControl(false);
	return 0;

}
