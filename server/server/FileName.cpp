//#define WIN32_LEAN_AND_MEAN

#include <iostream>

#include <WinSock2.h>

#include <cstring>

#include <string>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

using namespace std;

struct students

{

	string name;

	int group;

	double scholarship;

	double marks;

};

students table[5];

DWORD WINAPI ThreadFunc(LPVOID client_socket)

{

	setlocale(LC_ALL, "RUSSIAN");

	SOCKET soc = ((SOCKET*)client_socket)[0];

	char str[10];

	char sendstr[10];

	recv(soc, str, 10, 0); 

	string users_subj = "";

	int k = 0;

	while (str[k] != '\0') {

		users_subj.push_back(str[k]);

		k++;

	}

	cout << users_subj;

	for (int i = 0; i < 5; i++) { 

		if (table[i].name[0] == users_subj[0])

		{

			table[i].name.copy(sendstr, table[i].name.size() + 1);

			sendstr[table[i].name.size()] = '\0';

			send(soc, sendstr, sizeof(sendstr), 0); 

		}

	}

	send(soc, "7", sizeof("7"), 0);

	closesocket(soc);

	return 0;

}

int main()

{

	setlocale(LC_ALL, "RUSSIAN");

	table[0].scholarship = table[1].scholarship = table[2].scholarship = table[3].scholarship

		= table[4].scholarship = 70.2;

	table[0].name = "SERGEEV"; table[1].name = "IGOREV"; table[2].name = "IVANOV";

	table[3].name = "SVETLOV"; table[4].name = "PETROV";

	table[0].group = table[2].group = table[4].group = 972304;

	table[1].group = table[3].group = 972303;

	for (int i = 0; i < 5; i++)

	{

		table[i].marks = i + 3;

		cout << table[i].name << endl << "№ группы " << table[i].group << endl << "По скольким предметам стоят оценки в системе: "

			<< table[i].marks << endl << "Стипендия " << table[i].scholarship << endl << endl;

	}

	WORD wVersionRequested = MAKEWORD(2, 2);

	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0)

		return 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in local_addr;

	local_addr.sin_family = AF_INET;

	local_addr.sin_port = htons(1280);

	local_addr.sin_addr.s_addr = 0;

	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));

	listen(s, 5);

	cout << "Сервер готов к приему!" << endl << endl;

	SOCKET client_socket;

	sockaddr_in client_addr;

	int client_addr_size = sizeof(client_addr);

	while (client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size)) 

	{

		DWORD thID;

		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID); 

	}

	return 0;

}