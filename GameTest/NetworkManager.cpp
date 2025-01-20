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

	ioctlsocket( mysocket, FIONBIO, &mode );
}

void NetworkManager::SetUpHost() {
	// Attempt bind multiple times before failing
	for (u_short i = 0; i < 100; i++ ) {
		myAddr.sin_port = htons( port + i );
		if ( bind( mysocket, (sockaddr *) &myAddr, sizeof( myAddr ) ) == 0 ) {
			isHost = true;

			char hostname[256];
			if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
				Shutdown();
				assert(false);
			}

			struct addrinfo hints = { 0 }, * res;
			hints.ai_family = AF_INET;

			if (getaddrinfo(hostname, NULL, &hints, &res) == 0) {
				for (struct addrinfo* p = res; p != NULL; p = p->ai_next) {
					sockaddr_in* addr = (sockaddr_in*)p->ai_addr;
					char ipStr[INET_ADDRSTRLEN];
					inet_ntop(AF_INET, &addr->sin_addr, ipStr, sizeof(ipStr));
					bindedIP = ipStr;
				}
				freeaddrinfo(res);
			} else {
				Shutdown();
				assert(false);
			}

			return;		// Successful bind so early exit
		}
	}
	// Must not have binded so...
	Shutdown();
	assert(false);
}

bool NetworkManager::SetUpClient( const std::string& serverIP, u_short serverPort ) {
	myAddr.sin_port = htons( serverPort );
	inet_pton(AF_INET, serverIP.c_str(), &myAddr.sin_addr);

	// Connect the UDP socket to the server
	if ( connect( mysocket, (sockaddr*) &myAddr, sizeof( myAddr ) ) == SOCKET_ERROR ) {
		return false;
	}

	return true;
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

void NetworkManager::UpdateLobbyClient() {
	if ( ! isHost &&  ! connected ) {
		std::vector<char> buffer( sizeof( PacketHeader ) + JOINMESSAGE.size() );
		buffer[0] = PacketHeader::JOIN;
		memcpy( buffer.data() + 1, JOINMESSAGE.c_str(), JOINMESSAGE.size() );
		send( mysocket, buffer.data(), (int) buffer.size(), 0);
	}
}

void NetworkManager::ReceivePackets() {
	char recvBuffer[2048];
	sockaddr_in senderAddr;
	int senderAddrSize = sizeof( senderAddr );

	while ( true ) {
		int bytesReceived = 0;
		if ( isHost ) {
			bytesReceived = recvfrom( mysocket, recvBuffer, sizeof(recvBuffer), 0, (sockaddr*)&senderAddr, &senderAddrSize );
		} else {
			bytesReceived = recv( mysocket, recvBuffer, sizeof(recvBuffer), 0 );
		}

		if ( bytesReceived == SOCKET_ERROR ) {
			if ( WSAGetLastError() == WSAEWOULDBLOCK ) {
				// no more packets
				return;
			} else {
				// Duct tape solution. If host exits their game then client's game is also exited :D
				glutLeaveMainLoop();
			}
		}

		ProcessPacket( recvBuffer, bytesReceived, senderAddr );
	}
}

void NetworkManager::ProcessPacket( char* data, int dataLength, sockaddr_in senderAddr ) {
	uint8_t packetType = data[0];

	char* payload = data + sizeof(PacketHeader);

	switch ( packetType ) {
		case PacketHeader::JOIN:
			HandleJoinRequest( payload, dataLength - sizeof(PacketHeader), senderAddr );
			break;
	}
}

void NetworkManager::HandleJoinRequest( char* payload, int payloadLength, sockaddr_in senderAddr ) {
	std::string message( payload, payloadLength );
	if ( message == JOINMESSAGE ) {
		for ( Player &p : connectedPlayers ) {
			if ( ( p.address.sin_addr.s_addr == senderAddr.sin_addr.s_addr ) && ( p.address.sin_port == senderAddr.sin_port ) ) {
				return;			// Already connected;
			}
		}
		connectedPlayers.emplace_back(senderAddr, numConnectedPlayers++);
		// Send confirmation back to original sender
	}
}
