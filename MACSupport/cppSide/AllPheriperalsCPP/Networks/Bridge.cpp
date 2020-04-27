//
//  Bridge.cpp
//  AllPheriperalsCPP
//
//  Created by Isu Kim on 2020/04/19.
//  Copyright © 2020 Isu Kim. All rights reserved.
//

#include "Bridge.hpp"

class ConnectrionBridge{
public:
    int servsock;
    int enable;
    int port;
    int clientsock;
    int operationMode;
    
    RGBVAL BeforeColor;
        
    struct sockaddr_storage client_addr_info;
    socklen_t len;
    
    /// A constructor member function that initializes this function.
    /// Since this function took a lot of time due to several bugs, I mean that it ran on g++ environement but not on Xcode.
    /// So I am not 100% sure why this function works. If you know how this function works 100%,  please let me know
    ConnectrionBridge(void){
        servsock = socket(AF_INET, SOCK_STREAM, 0);
        if(servsock < 0) perror("[ERROR] Failed to create a socket");

        enable = 1;
        setsockopt(servsock, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(int));
            
        sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(PORT);

        bind(servsock, (sockaddr*)&serv_addr, sizeof(serv_addr)); //Binding and listening here
        listen(servsock, 5);
        std::cout<< "[Server] Listening Server on port : " << PORT << std::endl;
    
        len = sizeof client_addr_info;

        clientsock = accept(servsock, (struct sockaddr*)&client_addr_info, &len); //Accepting here.
        std::cout << "[Server] Client connected" << std::endl;
        
        getOperationMode();
        intializeBeforeColor();

    }
    
    /// A member function that intializes color to 0, 0, 0 in order to make it more stable and not crash.
    void intializeBeforeColor(void){
        BeforeColor.R = 0;
        BeforeColor.G = 0;
        BeforeColor.B = 0;
        
        return;
    }
    
    /// A member function that receives which operation mode that this program should take
    /// 1 means sync all colors into one color.
    /// Other values are NOT implemented yet.
    void getOperationMode(void){
        int buffer[1];
        recv(clientsock, buffer, 1, 0);
        //buffer[0] = buffer[0] - 32512; // For Release Version. It's kind of odd...
        
        std::cout << "[Server] Received Operating Mode : " << buffer[0] << std::endl;
        std::cout << "[Server] The operating mode would be : ";
        operationMode = buffer[0];
                
        switch (operationMode) {
            case 1:
                std::cout << "Screen Reactive" << std::endl;
                break;
                
            case 2:
                std::cout << "Rainbow All" << std::endl;
                break;
                
            default:
                std::cout << "Not implemented yet" << std::endl;
                exit(0);
                break;
        }
        return;
    }
    
    /// A member functiont that receives 3 bytes of characters and saves them for RGB values.
    /// Returns : RGBVAL type.
    RGBVAL getRGBValues(void){
        char cBuffer[3] = {};
        RGBVAL tempVal;
        
        recv(clientsock, cBuffer, 3, 0);
            
        tempVal.R = cBuffer[0];
        tempVal.G = cBuffer[1];
        tempVal.B = cBuffer[2];

        // printf("RGB VAL : %d , %d , %d\n", tempVal.R, tempVal.G, tempVal.B); //Just for debug
        
        return tempVal;
    }
    
    /// A function that checks if new received RGBVAL type of data is new color
    /// @param newVal The new value of RGBVAL type to compair.
    /// @returns true if two colors are not the same color.
    /// @returns false if two colors are the same.
    bool isDifferentColor(RGBVAL newVal){
        if ((BeforeColor.R - newVal.R) || (BeforeColor.G - newVal.G) || (BeforeColor.B - newVal.B)){
            BeforeColor.R = newVal.R;
            BeforeColor.G = newVal.G;
            BeforeColor.B = newVal.B;
            
            return true;
        }
        else return false;
    }
};
