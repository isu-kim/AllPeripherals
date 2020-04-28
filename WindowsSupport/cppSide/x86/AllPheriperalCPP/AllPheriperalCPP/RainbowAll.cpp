#include "RainbowAll.hpp"

void RainbowAllEffect(Wrapper WrapperObj, ConnectrionBridge BridgeObj) {
	int ChangeSpeed;

	BridgeObj.getSpeed();
    ChangeSpeed = BridgeObj.Speed;

	std::cout << "[RainbowAllEffect] Now Operating RainbowAllEffect" << std::endl;
    printf("[RainbowAllEffect] Speed : %d\n", ChangeSpeed);
    RGBVAL tempVal = { 255, 0, 0 };

    while (1) {
        for (tempVal.G = 0; tempVal.G < 255; tempVal.G++) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }

        for (tempVal.R = 255; tempVal.R > 0; tempVal.R--) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }


        for (tempVal.B = 0; tempVal.B < 255; tempVal.B++) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }

        for (tempVal.G = 255; tempVal.G > 0; tempVal.G--) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }

        for (tempVal.R = 0; tempVal.R < 255; tempVal.R++) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }

        for (tempVal.B = 255; tempVal.B > 0; tempVal.B--) {
            WrapperObj.SetAllLedColor(tempVal);
            Sleep(ChangeSpeed);
        }
    }
    return;

}

