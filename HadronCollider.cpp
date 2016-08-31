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
BYTE g = 0;// no brightness
BYTE b = 0;
BYTE R = 255;
BYTE G = 255;// full brightness
BYTE B = 255;
bool exiter = false;
void hadron(){
	// Makes the explosion
	r = 0;
	g = 0;
	b = 0;

	int workaround = 18;
	SetFullLedColor(r, g, b);
	for (int x = 0; x < 8; x++){
		SetFullLedColor(r, g, b);
		SetLedColor(3, x, R, G, B);
		if (workaround == 14){ // on the enter key, there are some numbers missing
			workaround = 11;
		}
		else{
			workaround = workaround - 1;
		}
		SetLedColor(3, workaround, R, G, B);
		
		Sleep(40);

	}
	double multi;

	for (int y = 7; y > -1; y=y-1){
		multi = (.12857*y) + .1; //makes keys less bright the farther they are away
		BYTE Rs = 255 * multi;
		BYTE Gs = 255 * multi; 
		BYTE Bs = 255 * multi;
		for (int x = 0; x < 6; x++){
			SetLedColor(x, y, Rs, Gs, Bs);
			SetLedColor(5 - x, 15-y, Rs, Gs, Bs);
		}
		Sleep(20);
	}

}
// Just some code that allows you to close the program without windows error
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
		printf("\nHadron Collider is active!.\n");

	}
	EnableLedControl(true);//Allows for control of LED

	while (::exiter == false){

		hadron();//

		Sleep(250);
	}
	EnableLedControl(false); // hands control back over to the keyboard
	return 0;

}
