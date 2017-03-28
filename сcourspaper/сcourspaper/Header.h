#pragma once
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <mmsystem.h>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment (lib,"WinMM.Lib")
struct Data
{
	char PCName[30], ServerName[30], Massage[200], IP[16] = { 0 };
	WSADATA WSADat;
	SOCKADDR_IN sin;
	SOCKET Sock;
};
void CreatSocketAndConnect(struct Data *data);
void Menu(struct Data *data);
void CloseConnect(struct Data *data);
void RebootPC();
void ShutDownPC();
void ExitSystemePC();
void ExitFunction();
void OpenCD_ROM();