#pragma once

#include <CUESDK.h>
#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS
#include "RGBColor.hpp" //Since the RGBColor.hpp is in parent directory


/// This Struct is for which index the device is set as. If it is set to 0, then it is not valid device.
/// However, since I am going to set all device colors using individual values,
/// this struct would not be used very much.
struct DeviceIDIndex {
    int Keyboard;
    int Mouse;
    int Headset;
    int MouseMat;
    int HeadsetStand;
    int Cooler;
    int CommanderPro;
    int LightingNode;
    int MemoryModule;
    int Unknown;
};

struct ConnectedDeviceBool {
    bool Keyboard;
    bool Mouse;
    bool Headset;
    bool MouseMat;
    bool HeadsetStand;
    bool Etc;
};

/// This Struct is for saving the LED couts of devices.
struct DeviceLedsCounts {
    int Keyboard;
    int Mouse;
    int Headset;
    int MouseMat;
    int HeadsetStand;
    int Cooler;
    int CommanderPro;
    int LightingNode;
    int MemoryModule;
    int Unknown;
};

struct LedIdArray {
    CorsairLedColor* Keyboard;
    CorsairLedColor* Mouse;
    CorsairLedColor* Headset;
    CorsairLedColor* MouseMat;
    CorsairLedColor* HeadsetStand;
    CorsairLedColor* Etc;
};

/// This struct is for storing basic Corsair Device Information.
struct CorsairInfo {
    int TotalCounts; // Total Device counts
    int TotalFunctionPointerCounts;
    bool AlreadyInitialized; // For checking if we have intialized.
    DeviceIDIndex Indexes; // The struct data type mentioned up above.
    DeviceLedsCounts Counts; // The struct data type mentioned up above.
};