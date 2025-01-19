#pragma once

#include <winsock2.h>

/*
===============================================================================



===============================================================================
*/
class NetworkManager {
public:
	WSADATA							wsaData;
	SOCKET							mysocket;
	int								desiredPort = 60140;	// GOLF0
	int								actualPort;

	void							Shutdown();
	static NetworkManager&			GetInstance();

private:
									NetworkManager();
};