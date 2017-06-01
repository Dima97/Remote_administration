#pragma once
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <tchar.h>
#include <process.h>
#include <winuser.h>
#include<iostream>
using namespace std;

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")

struct Data
{
	WSADATA WSADat;
	SOCKADDR_IN sin;
	SOCKET Sock, Client;
	int procent = 0;
	char PCName[30], ClientName[30], Massage[200], IP[16] = { 0 };
};

void Menu(struct Data *data);
void CreatSocketAndConnect(struct Data *data);
void CloseConnect(struct Data *data);
void recvFile(struct Data *data,char path[]);
void mouseClick(struct Data *data);
int recieveData(struct Data *data);
void Screen(struct Data *data, char path[]);
void funHelp();