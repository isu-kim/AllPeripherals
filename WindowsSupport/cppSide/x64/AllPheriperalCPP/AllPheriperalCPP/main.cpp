#include "main.hpp"

//
//  main.cpp
//  AllPheriperalsCPP
//
//  Created by Isu Kim on 2020/04/19.
//  Copyright © 2020 Isu Kim. All rights reserved.
//


/// A Functiont at syncs all device colors into one color.
/// The parameter CorsairObj would be later changed to some other class for all integration.
/// @param CorsairObj The Corsair type object to use.
/// @param BridgeObj The ConnectionBride type object to use.
void SyncAllColors(Wrapper WrapperObj, ConnectrionBridge BridgeObj) {
    std::cout << "[Server] Now syncing all colors" << std::endl;

    while (1) {
        RGBVAL tempVal = BridgeObj.getRGBValues();
        if (BridgeObj.isDifferentColor(tempVal)) {
            WrapperObj.SetAllLedColor(tempVal);
        }
    }
    return;
}

/// Our Friendly GUI function that prints our logo in ascii-art!
void PrintTitle(void) {
    std::cout << "                                                                             Windows 64bit C++ Side Program" << std::endl;
    std::cout << "                                                                                              by Gooday2die" << std::endl;
    std::cout << "                                       Please Check My Github : https://github.com/gooday2dieAllPeripherals" << std::endl;

}

/// Yes. The Entry point of this program!
/// @param argc You know what it is
/// @param argv This one also.
int main(int argc, const char* argv[]) {
    PrintTitle();
    
    Wrapper WrapperObj = Wrapper();
    ConnectrionBridge BridgeObj = ConnectrionBridge();

    switch (BridgeObj.operationMode) {
    case 1:
        std::cout << "[Server] Received Mode 1 : Screen Reactive" << std::endl;
        SyncAllColors(WrapperObj, BridgeObj);
        break;

    case 2:
        std::cout << "[Server] Received Mode 2 : Rainbow All" << std::endl;
        RainbowAllEffect(WrapperObj, BridgeObj);
    default:
        break;
    }
    return 0;
}

