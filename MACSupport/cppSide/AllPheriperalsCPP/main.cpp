//
//  main.cpp
//  AllPheriperalsCPP
//
//  Created by Isu Kim on 2020/04/19.
//  Copyright © 2020 Isu Kim. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "Networks/Bridge.cpp" // If I load bridge later than corsair, it crashes. kind of odd...
#include "Wrappers/CorsairWrapper.cpp"
#include "Wrappers/CUESDK.framework/Headers/CUESDK.h"

/// A Functiont at syncs all device colors into one color.
/// The parameter CorsairObj would be later changed to some other class for all integration.
/// @param CorsairObj The Corsair type object to use.
/// @param BridgeObj The ConnectionBride type object to use.
void SyncAllColors(Corsair CorsairObj, ConnectrionBridge BridgeObj){
    std::cout << "[Server] Now syncing all colors" << std::endl;
    
    while(1){
        RGBVAL tempVal = BridgeObj.getRGBValues();
            if(BridgeObj.isDifferentColor(tempVal)) CorsairObj.SetAllLedColor(tempVal);
    }
    return;
}

/// Our Friendly GUI function that prints our logo in ascii-art!
void PrintTitle(void){
    std::cout << " █████╗ ██╗     ██╗     ██████╗ ███████╗██████╗ ██╗██████╗ ██╗  ██╗███████╗██████╗  █████╗ ██╗     ███████╗" << std::endl;
    std::cout << "██╔══██╗██║     ██║     ██╔══██╗██╔════╝██╔══██╗██║██╔══██╗██║  ██║██╔════╝██╔══██╗██╔══██╗██║     ██╔════╝" << std::endl;
    std::cout << "███████║██║     ██║     ██████╔╝█████╗  ██████╔╝██║██████╔╝███████║█████╗  ██████╔╝███████║██║     ███████╗" << std::endl;
    std::cout << "██╔══██║██║     ██║     ██╔═══╝ ██╔══╝  ██╔══██╗██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗██╔══██║██║     ╚════██║" << std::endl;
    std::cout << "██║  ██║███████╗███████╗██║     ███████╗██║  ██║██║██║     ██║  ██║███████╗██║  ██║██║  ██║███████╗███████║" << std::endl;
    std::cout << "╚═╝  ╚═╝╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝" << std::endl;
    std::cout << "                                                                                     MacOS C++ Side Program" << std::endl;
    std::cout << "                                                                                              by Gooday2die" << std::endl;
    std::cout << "                                       Please Check My Github : https://github.com/gooday2dieAllPeripherals" << std::endl;

}

/// Yes. The Entry point of this program!
/// @param argc You know what it is
/// @param argv This one also.
int main(int argc, const char * argv[]) {
    PrintTitle();
    Corsair CorsairObj = Corsair();
    ConnectrionBridge BridgeObj = ConnectrionBridge();
    
    switch (BridgeObj.operationMode) {
        case 1:
            std::cout << "[Server] Received Mode 1 : Screen Reactive" << std::endl;
            SyncAllColors(CorsairObj, BridgeObj);
            break;
            
        case 2:
            std::cout << "[Server] Received Mode 2 : Rainbow All" << std::endl;
            SyncAllColors(CorsairObj, BridgeObj);
        default:
            break;
    }
    return 0;
}

