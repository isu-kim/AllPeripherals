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

int main(int argc, const char * argv[]) {
    Corsair CorsairObj = Corsair();
    ConnectrionBridge BridgeObj = ConnectrionBridge();
    
    CorsairObj.SetAllLedColor(BridgeObj.getRGBValues());
    RGBVAL test;
    test.R = 255;
    test.G = 255;
    test.B = 0;
    
    while (1){
        RGBVAL tempVal = BridgeObj.getRGBValues();
        if(BridgeObj.isDifferentColor(tempVal)) CorsairObj.SetAllLedColor(tempVal);
    }
    
    return 0;
}
