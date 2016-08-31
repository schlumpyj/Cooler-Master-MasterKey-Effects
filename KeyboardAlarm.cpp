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
bool exiter = false;
void alarm(){
	//Basically turns on and off LEDs 20 times
	for (int x = 1; x < 20; x++){

		Sleep(500);
		r = 255;
		g = 255;// full brightness
		b = 255;
		SetFullLedColor(r, g, b);
		Sleep(500);
		r = 0;
		g = 0;// no brightness
		b = 0;
		SetFullLedColor(r, g, b);
	}

}
//This is just something I found that allows you to close your console program without error
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
	int minuted;
	cout << "How many minutes between activity alarms? "; //Asks for how long they would like to be reminded
	cin >> minuted;//save it
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		printf("\nReminder every %d minutes to get up and be active!.\n", minuted);

	}

	while (::exiter == false){ // infinite loop until someone closes
		sleep_until(system_clock::now() + minutes(minuted));//waits X seconds to do the sequence again
		EnableLedControl(true);//Allows for control of LED
		cout << "GET UP AND BE ACTIVE" << endl;
		alarm();//Turns off and on the LEDS
		EnableLedControl(false);//Disables the LEDs}
	}
	EnableLedControl(false);//Make sure to hand back control to the keyboard
	return 0;

}
