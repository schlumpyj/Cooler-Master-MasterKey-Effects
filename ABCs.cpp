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
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
BYTE r = 0;
BYTE g = 0;
BYTE b = 0;
BYTE R = 255;
BYTE G = 255;
BYTE B = 255;
bool exiter = false;
// Bunch of lists that are separated because the ABC song goes at different tempos during the song 
// and writing different for loops for each beat was easier than trying to make one big one
int row1[7] = { 3, 4, 4, 3, 2, 3, 3 };
int col1[7] = { 1, 6, 4, 3, 3, 4, 5 };
int row2[4] = { 3, 2, 3, 3 };
int col2[4] = { 6, 8, 7, 8 };
int row3[5] = { 3, 4, 4, 2, 2 };
int col3[5] = { 9, 8, 7, 9, 10 };
int row4[6] = { 2, 2, 3, 2, 2, 4 };
int col4[6] = { 1, 4, 2, 5, 7, 5 };

int nowR[3] = { 4, 2, 2 };
int nowC[3] = { 7, 9, 2 };

int knowR[10] = { 3, 4, 2, 4, 4, 2, 3, 4, 4, 3 };
int knowC[10] = { 8, 8, 9, 7, 8, 6, 1, 6, 4, 2 };

int nextR[29] = { 4, 2, 4, 2, 2, 2, 4, 2, 2, 2, 4, 4, 3, 2, 2, 2, 2, 3, 2, 4, 3, 2, 2, 2, 3, 4, 2, 4, 4 };
int nextC[29] = { 7, 3, 3, 5, 5, 8, 8, 3, 2, 9, 7, 0, 11, 5, 6, 9, 7, 2, 8, 7, 5, 2, 8, 5, 6, 8, 3, 0, 11 };
//                Next........Time........wont...............you.......sing.......with........me?..........
void showABC(){
	for (int x = 0; x < 7; x++){

		SetLedColor(row1[x], col1[x], R, G, B);
		Sleep(500);
	}
	Sleep(500);
	for (int x = 0; x < 4; x++){

		SetLedColor(row2[x], col2[x], R, G, B);
		Sleep(500);
	}
	for (int x = 0; x < 5; x++){

		SetLedColor(row3[x], col3[x], R, G, B);
		Sleep(250);
	}
	Sleep(750);
	for (int x = 0; x < 6; x++){

		SetLedColor(row4[x], col4[x], R, G, B);
		if (x == 2){
			Sleep(1000);
		}
		else{
			Sleep(500);
		}
	}
	Sleep(500);
	SetLedColor(2, 2, R, G, B);
	Sleep(100);
	SetLedColor(2, 2, r, g, b);
	Sleep(100);
	SetLedColor(2, 2, R, G, B);
	Sleep(100);
	SetLedColor(2, 2, r, g, b);// W madness
	Sleep(100);
	SetLedColor(2, 2, R, G, B);
	Sleep(100);
	SetLedColor(2, 2, r, g, b);
	Sleep(300);
	SetLedColor(2, 2, R, G, B);
	Sleep(200);
	SetLedColor(4, 3, R, G, B);
	Sleep(1000);

	SetLedColor(2, 6, R, G, B);
	Sleep(500);

	SetLedColor(1, 7, R, G, B);
	SetLedColor(4, 0, R, G, B);
	Sleep(400);
	SetLedColor(4, 2, R, G, B);
	Sleep(500);

	SetFullLedColor(r, g, b);
	Sleep(200);
	//Now I know my ABCs
	for (int x = 0; x < 3; x++){

		SetLedColor(nowR[x], nowC[x], R, G, B);

	}
	cout << "Now ";
	Sleep(600);
	SetFullLedColor(r, g, b);
	SetLedColor(2, 8, R, G, B);
	cout << "I ";
	Sleep(600);
	SetFullLedColor(r, g, b);
	for (int x = 0; x < 4; x++){
		SetLedColor(knowR[x], knowC[x], R, G, B);
	}
	cout << "Know ";
	Sleep(600);
	SetFullLedColor(r, g, b);
	for (int x = 4; x < 6; x++){
		SetLedColor(knowR[x], knowC[x], R, G, B);
	}
	cout << "My ";
	Sleep(600);
	SetFullLedColor(r, g, b);
	cout << "ABCs " << endl;
	for (int x = 6; x < 10; x++){
		if (x == 8){
			SetLedColor(knowR[x], knowC[x], R, G, B);
			SetLedColor(knowR[x + 1], knowC[x + 1], R, G, B);
		}
		else{
			SetLedColor(knowR[x], knowC[x], R, G, B);
		}
		Sleep(425);
	}

	SetFullLedColor(r, g, b);
	for (int x = 0; x < 4; x++){//next
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "Next ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 4; x < 8; x++){//time
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "Time ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 8; x < 14; x++){//won't
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "won't ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 14; x < 17; x++){//you
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "you ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 17; x < 21; x++){ //sing
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "sing ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 21; x < 25; x++){ //with
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "with ";
	Sleep(500);
	SetFullLedColor(r, g, b);
	for (int x = 25; x < 29; x++){//me?
		SetLedColor(nextR[x], nextC[x], R, G, B);

	}
	cout << "me? " << endl;
	Sleep(1000);
	SetFullLedColor(r, g, b);
	
}
// Just some code I found that allows you to close your program without random windows error
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
	mciSendString(L"open \"song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL); // open the song
	SetControlDevice(DEV_MKeys_M_White);

	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		printf("\nTurn up the volume and sing along!!.\n");

	}
	mciSendString(L"play mp3", NULL, 0, NULL);
	while (::exiter == false){

		EnableLedControl(true);//Allows for control of LED

		showABC();//Turns off and on the LEDS

		Sleep(350);//Disables the LEDs}
		mciSendString(L"play mp3 from 0", NULL, 0, NULL); // restart the song
	}
	mciSendString(L"close mp3", NULL, 0, NULL); // close the song for good measure
	EnableLedControl(false);
	return 0;

}
