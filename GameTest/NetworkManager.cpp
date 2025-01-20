#include "stdafx.h"

#include "NetworkManager.h"
#include <assert.h>

#pragma comment(lib, "ws2_32.lib")


NetworkManager::NetworkManager() {
	int error = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );		// Init Windows Socket Library using latest version which appears to be 2.2
	assert( error == 0 );

	ResetSocket();

	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = INADDR_ANY;
}

void NetworkManager::SetUpHost() {
	// Attempt bind multiple times before failing
	for (u_short i = 0; i < 100; i++ ) {
		myAddr.sin_port = htons( port + i );
		if ( bind( mysocket, (sockaddr *) &myAddr, sizeof( myAddr ) ) == 0 ) {
			return;		// Successful bind so early exit
		}
	}
	// Must not have binded so...
	Shutdown();
	assert(false);
}

void NetworkManager::SetUpClient( const std::string& serverIP, u_short serverPort ) {
	myAddr.sin_port = htons( serverPort );
	inet_pton(AF_INET, serverIP.c_str(), &myAddr.sin_addr);

	// Connect the UDP socket to the server
	if ( connect( mysocket, (sockaddr*) &myAddr, sizeof( myAddr ) ) == SOCKET_ERROR ) {
		Shutdown();
		assert(false);
	}
}

void NetworkManager::ResetSocket() {
	if ( mysocket != INVALID_SOCKET) {
		closesocket(mysocket);
	}
	mysocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (mysocket == INVALID_SOCKET) {
		Shutdown();
		assert(false);
	}
}

void NetworkManager::Shutdown() {
	if ( mysocket != INVALID_SOCKET ) {
		closesocket(mysocket);
	}
	WSACleanup();
}

NetworkManager& NetworkManager::GetInstance() {
	static NetworkManager instance;
	return instance;
}
