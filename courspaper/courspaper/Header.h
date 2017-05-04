#pragma once
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")

struct Data
{
	WSADATA WSADat;
	SOCKADDR_IN sin;
	SOCKET Sock, Client;
	char PCName[30], ClientName[30], Massage[200], IP[16] = { 0 };
};

void Menu(struct Data *data);
void CreatSocketAndConnect(struct Data *data);
void CloseConnect(struct Data *data);
void recvFile(struct Data *data,char path[]);