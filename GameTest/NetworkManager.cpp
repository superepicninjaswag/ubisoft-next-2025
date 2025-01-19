#include "stdafx.h"

#include "NetworkManager.h"
#include <assert.h>

#pragma comment(lib, "ws2_32.lib")


NetworkManager::NetworkManager() {
	int error = WSAStartup( MAKEWORD(2, 2), &wsaData );		// Init Windows Socket Library using latest version which appears to be 2.2
	assert( error == 0 );

	mysocket = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( mysocket == INVALID_SOCKET ) {
		WSACleanup();
		assert( mysocket != INVALID_SOCKET );
	}
}

void NetworkManager::Shutdown() {
	closesocket( mysocket );
	WSACleanup();
}

NetworkManager& NetworkManager::GetInstance() {
	static NetworkManager instance;
	return instance;
}
