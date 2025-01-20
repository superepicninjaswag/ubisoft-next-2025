#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>


/*
===============================================================================



===============================================================================
*/
class NetworkManager {
public:
	WSADATA							wsaData;
	SOCKET							mysocket = INVALID_SOCKET;
	sockaddr_in						myAddr;
	u_short							port = 60140;	// GOLF0

	void							SetUpHost();
	void							SetUpClient( const std::string& serverIP, u_short serverPort );
	void							ResetSocket();
	void							Shutdown();
	static NetworkManager&			GetInstance();

private:
									NetworkManager();
};