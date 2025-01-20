#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>


enum PacketHeader : uint8_t {
	JOIN = 1
};

struct Player {
	sockaddr_in address;
	int			playerNumber;

				Player(sockaddr_in addr, int number) : address(addr), playerNumber(number) {}
};

struct JoinPacket {

};


/*
===============================================================================



===============================================================================
*/
class NetworkManager {
public:
	WSADATA							wsaData;
	SOCKET							mysocket = INVALID_SOCKET;
	sockaddr_in						myAddr;
	u_short							port = 60140;			// GOLF0, port to open server socket on
	std::string						bindedIP;

	u_long							mode = 1;				// Enable non-blocking mode

	bool							isHost = false;
	bool							connected = false;		// Used by client to tell if they are connected

	const std::string				JOINMESSAGE = "JOIN REQUEST";

	std::vector<Player>				connectedPlayers;
	int								numConnectedPlayers = 1;	// When hosting, the host is "connected"

	void							SetUpHost();
	bool							SetUpClient( const std::string& serverIP, u_short serverPort );
	void							ResetSocket();
	void							Shutdown();
	static NetworkManager&			GetInstance();

	void							UpdateLobbyClient();

	void							ReceivePackets();
	void							ProcessPacket( char* data, int dataLength, sockaddr_in senderAddr );

	void							HandleJoinRequest( char* payload, int payloadLength, sockaddr_in senderAddr );

private:
									NetworkManager();
};