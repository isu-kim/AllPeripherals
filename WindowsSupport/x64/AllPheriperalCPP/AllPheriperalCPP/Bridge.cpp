/**
	Allpheriperals
	Communications.cpp
	Purpose: To receive data from Python side of this program using socket program

	@author Gooday2die(Isu Kim)
	@version 1.0 20/03/31
*/

#include "Bridge.hpp"

class ConnectrionBridge {
	/**
	A Class for processing communications.
	*/
public:
	WSADATA wsaData;
	SOCKET hListen;
	SOCKET hClient;
	SOCKADDR_IN tListenAddr = {};
	SOCKADDR_IN tCIntAddr = {};
	RGBVAL BeforeColor;
	int operationMode = -1;


	/*
	RGBVAL receive4ByteData(void);
	void sendData(char* cMsg);
	void EndServer(void);
	int InitOperatingMode(void);
	*/

	ConnectrionBridge() {
		/**
		A Constructor member function for class Communications

		@param {bool} whether or not to debug.
		@return {void}
		*/

		std::cout << "[Server] Now initializing socket server..." << std::endl;

		WSAStartup(MAKEWORD(2, 2), &wsaData);

		hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		tListenAddr.sin_family = AF_INET;
		tListenAddr.sin_port = htons(PORT);
		tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
		listen(hListen, SOMAXCONN);

		int iCIntSize = sizeof(tCIntAddr);
		hClient = accept(hListen, (SOCKADDR*)&tCIntAddr, &iCIntSize);

		std::cout << "[Server] Client was successfully connected." << std::endl;

		getOperationMode();

		switch (operationMode) {
		case 1:
			std::cout << "[Server] Operating program in mode 1" << std::endl;
			std::cout << "[Server] Now syncing all the colors" << std::endl;
			break;
			
		case 2:
			std::cout << "[Server] Operating program in mode 2" << std::endl;
			std::cout << "[Server] Now syncing all the colors" << std::endl;
			break;

		default:
			std::cout << "[ERROR] Could not initialize the program successfully." << std::endl;
		}

	}

	void intializeBeforeColor(void) {
		BeforeColor.R = 0;
		BeforeColor.G = 0;
		BeforeColor.B = 0;

		return;
	}

	void getOperationMode(void){
		/**
		A member function for receiving which operation mode would be using.

		The mode settings are like it is below.

		Mode -1 : Error state. Ends the program.
		Mode 1 : Sync into just one color.
		More to be added.

		@param {void}
		@return {int} the mode that this program would be ran.
		*/

		char cBuffer; // A buffer for temporary storing recived data
		recv(hClient, &cBuffer, 1, 0);

		operationMode = cBuffer;
	}

	RGBVAL getRGBValues(void) {
		/**
		A Member function for receiving data from Python side of this program.

		This Function would be used ONLY when all the devices would be just synced
		to one color. This function would not support individual color settings of
		devices due to it's lack of transmission packet capicity.

		Please note that this recived data would be saved in cBuffer string which
		would have size of 3 bytes to minimize overhead and enhance speed of
		communications.

		Please check documents regarding that communication protocol.

		[R][G][B]

		@param {void}
		@return {RGBVAL} RGB value that had been sent by the Python side.
		*/
		char cBuffer[3] = {};  // Assigning a string buffer to listen data
		RGBVAL tempVal;  // Assigning a temp RGBVAL structure to return data

		recv(hClient, cBuffer, 3, 0);
		tempVal.R = cBuffer[0];  // I do know that this method seems crazy however,
		tempVal.G = cBuffer[1];  // I will just use it this way :b
		tempVal.B = cBuffer[2];

		return tempVal;
	}

	void sendData(char* cMsg) {
		/**
		A member function for sending data back to Python side of the program.
		This probably would be used for just the cases in which errors occur.

		@param {char*} The message starting address of message string to send.
		@return {void}
		*/
		send(hClient, cMsg, strlen(cMsg), 0);
		return;
	}


	void endServer(void) {
		/**
		A member function for stopping all the connections and closing sockets properly.

		@param {void}
		@return {void}
		*/
		WSACleanup();
		closesocket(hClient);
		closesocket(hListen);
		return;
	}

	bool isDifferentColor(RGBVAL newVal) {
		if ((BeforeColor.R - newVal.R) || (BeforeColor.G - newVal.G) || (BeforeColor.B - newVal.B)) {
			BeforeColor.R = newVal.R;
			BeforeColor.G = newVal.G;
			BeforeColor.B = newVal.B;

			return true;
		}
		else return false;
	}

};
