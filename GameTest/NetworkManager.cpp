#include "stdafx.h"
#include "NetworkManager.h"


NetworkManager::NetworkManager() {

}

NetworkManager& NetworkManager::GetInstance() {
	static NetworkManager instance;
	return instance;
}
