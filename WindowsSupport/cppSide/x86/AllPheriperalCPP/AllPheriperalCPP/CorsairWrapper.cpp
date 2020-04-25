//
//  CorsairWrapper.cpp
//  MacPheriperalsCppSide
//
//  This CorsairWrapper.cpp is for wrapping Corsair ICUE SDK to my Project.
//
//  Created by Isu Kim on 2020/04/18.
//  Copyright © 2020 Isu Kim. All rights reserved.
//

#include "CorsairWrapper.hpp"
#include <iostream>

/*There are two options while running this process.
 The process loads LedColor array to ram when the devices are only connected.
 However, if you accidently call a function that uses uninitialized array or non existing array,
 this program will die due to segementation fault.

 For example, If you only have headphone but you manually controlled led value of keyboard which is not connected, then the program assigns your LED color value to not assigned memory address of your ram.
 This crashes the program since it is not a possible operation in C++ or any other C relevant programs.

 So, the soloution to this is that you just load all the device arrays. Then even if you have acciently
 assigned a value to non existing device, the program does not die. It will just keep going on.

 However, as it says loading all device arrays to ram is quite a bit RAM consuming if you are using a PC
 which is not a monster spec. Each LedColor Structure takes about 16 bytes (actually would be more since
 sizeof function returns something less) And we assign about 1000 LedColor values, since official Corsair
 supports up to 1000 (actually less but) LED channels. So, that means that it will take about 16kbs.

 But if you do not like to use 16kbs for your performance and sacrifice this program's stability, so be it.
 Replace NONEEDTOSAVERAM to PLEASESAVEMYRAM for that operation.
 */

#define PLEASESAVEMYRAM false
#define NONEEDTOSAVERAM true

using namespace std;

class Corsair {
public:
    CorsairInfo DevInfo;
    int DeviceCount;
    bool DidEtcInit; // Checking if ETC Led array assign was done to avoid calling twice.
    ConnectedDeviceBool Connected;
    LedIdArray LedArray;
    typedef void (Corsair::* SetLedFunctionPointer)(RGBVAL);// Declared a function pointer typedef for later purpose.
    //typedef void (Corsair::*SetLedFunctionPointer)(int, int, int);// Declared a function pointer typedef for later purpose.
    SetLedFunctionPointer* SetLedFunctionPointerArray;

    Corsair() {
        DeviceCount = 0;
        initStructures();
        DidEtcInit = false;
        CorsairPerformProtocolHandshake(); // Need to perform handshake first!
        CorsairRequestControl(CAM_ExclusiveLightingControl);// Requesting Full control to ICUE
        std::cout << "[Corsair] Successfully Requested Control" << std::endl;
        SetDeviceInfo(&DevInfo);
        MakeSetAllLedFunction();
        std::cout << "[Corsair] Dumped Files to RAM" << std::endl;
        std::cout << "[Corsair] Initialization Process Complete" << std::endl;

    }

    /// A function that reads Corsair Device list and saves to structure CorsairInfo
    /// @param DevInfo The pointer CorsairInfo structure to save our connected devices data.
    void SetDeviceInfo(CorsairInfo* DevInfo) {
        DeviceCount = CorsairGetDeviceCount(); // Getting total number of counts of devices
        if (DeviceCount == 0) std::cout << "[Corsair] No Connected Corsair Devices" << std::endl;
        else if (DeviceCount == -1) {
            std::cout << "[Corsair] ICUE SDK Error" << std::endl;
            std::cout << "[Corsair] Please check if ICUE is running or you have enabled SDK option" << std::endl;
        }
        else std::cout << "[Corsair] Total Connected  Devices : " << DeviceCount << endl;

        for (int i = 0; i < DeviceCount; i++) { // For save the information to the structure.
            CorsairDeviceInfo* tempDevInfo = CorsairGetDeviceInfo(i);
            switch (tempDevInfo->type) {
            case CDT_Mouse:
                DevInfo->Indexes.Mouse = i;
                DevInfo->Counts.Mouse = tempDevInfo->ledsCount;
                AssignMouseLedArrays();
                cout << "[Corsair] Mouse : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Mouse = true;
                break;

            case CDT_Keyboard:
                DevInfo->Indexes.Keyboard = i;
                DevInfo->Counts.Keyboard = tempDevInfo->ledsCount;
                AssignKeyboardLedArrays();
                cout << "[Corsair] Keyboard : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Keyboard = true;
                break;

            case CDT_Headset:
                DevInfo->Indexes.Headset = i;
                DevInfo->Counts.Headset = tempDevInfo->ledsCount;
                AssignHeadsetLedArrays();
                cout << "[Corsair] Headset : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Headset = true;
                break;

            case CDT_Cooler:
                DevInfo->Indexes.Cooler = i;
                DevInfo->Counts.Cooler = tempDevInfo->ledsCount;
                AssignEtcLedArrays();
                cout << "[Corsair] Cooler : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Etc = true;
                break;

            case CDT_MouseMat:
                DevInfo->Indexes.MouseMat = i;
                DevInfo->Counts.MouseMat = tempDevInfo->ledsCount;
                AssignMouseMatLedArrays();
                cout << "[Corsair] MouseMat : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.MouseMat = true;
                break;

            case CDT_CommanderPro:
                DevInfo->Indexes.CommanderPro = i;
                DevInfo->Counts.CommanderPro = tempDevInfo->ledsCount;
                AssignEtcLedArrays();
                cout << "[Corsair] CommanderPro : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Etc = true;
                break;

            case CDT_HeadsetStand:
                DevInfo->Indexes.HeadsetStand = i;
                DevInfo->Counts.HeadsetStand = tempDevInfo->ledsCount;
                AssignHeadSetStandLedArrays();
                cout << "[Corsair] HeadsetStand : " << tempDevInfo->model << endl;
                //cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.HeadsetStand = true;
                break;

            case CDT_MemoryModule:
                DevInfo->Indexes.MemoryModule = i;
                DevInfo->Counts.MemoryModule = tempDevInfo->ledsCount;
                AssignEtcLedArrays();
                cout << "[Corsair] MemoryModule : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Etc = true;
                break;

            case CDT_LightingNodePro:
                DevInfo->Indexes.LightingNode = i;
                DevInfo->Counts.LightingNode = tempDevInfo->ledsCount;
                AssignEtcLedArrays();
                cout << "[Corsair] LightingNodePro : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Etc = true;
                break;

            case CDT_Unknown:
                DevInfo->Indexes.Unknown = i;
                DevInfo->Counts.Unknown = tempDevInfo->ledsCount;
                AssignEtcLedArrays();
                cout << "[Corsair] Unknown : " << tempDevInfo->model << endl;
                // cout << "Led Counts : " << tempDevInfo->ledsCount << endl;
                Connected.Etc = true;
                break;

            default:
                break;
            }
        }
        if (NONEEDTOSAVERAM) {
            if (!Connected.MouseMat) AssignMouseMatLedArrays();
            if (!Connected.Mouse) AssignMouseLedArrays();
            if (!Connected.Headset) AssignHeadsetLedArrays();
            if (!Connected.Etc) AssignEtcLedArrays();
            if (!Connected.HeadsetStand) AssignHeadsetLedArrays();
            if (!Connected.Keyboard) AssignKeyboardLedArrays();
        }

        return;
    }

    void initStructures(void) {
        DevInfo.AlreadyInitialized = false;
        DevInfo.TotalCounts = 0;

        Connected.Etc = false;
        Connected.Headset = false;
        Connected.HeadsetStand = false;
        Connected.Keyboard = false;
        Connected.Mouse = false;
        Connected.MouseMat = false;

    }

    /// A function that sets a LED to a specific color. This function is depreciated since the official Corsair offers us to use
    /// CorsairSetLedsColorsBufferByDeviceIndex instead. This function is meant to set multiple LED colors with For loop.
    /// If you would like to set a specific color as some value, please use SetLedColor instead.
    /// @param LedID The LED ID to set color as
    /// @param R The RED value of the color to set as
    /// @param G The Green value of the color to set as
    /// @param B The Blue value of the color to set as
    void SetLedColorByID(CorsairLedId LedID, int R, int G, int B) {
        CorsairLedColor tempColor;
        tempColor.ledId = LedID;
        tempColor.r = R;
        tempColor.g = G;
        tempColor.b = B;

        CorsairSetLedsColors(1, &tempColor); // I do know that using this function is depreciated.
        return;

    }

    /// A function that sets a LED or series of LEDs to a specific color. Use this function insted of SetLedColorByID
    /// @param DeviceIndex The index of the device that you would like to set color
    /// @param size The length of the LedColor Array.
    /// @param LedColorArray The LedColor Array.
    void SetLedColors(int DeviceIndex, int size, CorsairLedColor* LedColorArray) {
        CorsairSetLedsColorsBufferByDeviceIndex(DeviceIndex, size, LedColorArray);
        CorsairSetLedsColorsFlushBuffer(); // We need to flash buffer in order to set led color.
        return;
    }

    /// A function that sets all LEDs of Corsair Headset to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as

    void SetHeadsetColors(RGBVAL Value) {
        //void SetHeadsetColors(int R, int G, int B){
        for (int i = 0; i < 2; i++) {
            LedArray.Headset[i].r = Value.R;
            LedArray.Headset[i].g = Value.G;
            LedArray.Headset[i].b = Value.B;
        }
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Headset, 2, LedArray.Headset);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all LEDs of Corsair Keyboard to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as
    void SetKeyboardColors(RGBVAL Value) {
        //void SetKeyboardColors(int R, int G, int B){

        for (int i = 0; i < 167; i++) {
            LedArray.Keyboard[i].r = Value.R;
            LedArray.Keyboard[i].g = Value.G;
            LedArray.Keyboard[i].b = Value.B;
        }

        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Keyboard, 167, LedArray.Keyboard);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all LEDs of Corsair Mouse to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as

    void SetMouseColors(RGBVAL Value) {
        //void SetMouseColors(int R, int G, int B){

        for (int i = 0; i < 4; i++) {
            LedArray.Mouse[i].r = Value.R;
            LedArray.Mouse[i].g = Value.G;
            LedArray.Mouse[i].b = Value.B;
        }

        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Mouse, 4, LedArray.Mouse);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all LEDs of Corsair Headset Stand to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as

    void SetHeadSetStandColors(RGBVAL Value) {
        //void SetHeadSetStandColors(int R, int G, int B){

        for (int i = 0; i < 9; i++) {
            LedArray.HeadsetStand[i].r = Value.R;
            LedArray.HeadsetStand[i].g = Value.G;
            LedArray.HeadsetStand[i].b = Value.B;
        }

        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Keyboard, 9, LedArray.HeadsetStand);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all LEDs of Corsair MouseMat to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as

    void SetMouseMatColors(RGBVAL Value) {
        //void SetMouseMatColors(int R, int G, int B){

        for (int i = 0; i < 15; i++) {
            LedArray.MouseMat[i].r = Value.R;
            LedArray.MouseMat[i].g = Value.G;
            LedArray.MouseMat[i].b = Value.B;
        }
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.MouseMat, 15, LedArray.MouseMat);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all LEDs of Corsair Etc devices to a specific LED value.
    /// @param Value The RGBVAL type of data to set color as

    void SetEtcColors(RGBVAL Value) {
        //void SetEtcColors(int R, int G, int B){
        for (int i = 0; i < 730; i++) {
            LedArray.Etc[i].r = Value.R;
            LedArray.Etc[i].g = Value.G;
            LedArray.Etc[i].b = Value.B;
        }
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.CommanderPro, 730, LedArray.Etc);
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Cooler, 730, LedArray.Etc);
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.MemoryModule, 730, LedArray.Etc);
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.LightingNode, 730, LedArray.Etc);
        CorsairSetLedsColorsBufferByDeviceIndex(DevInfo.Indexes.Unknown, 730, LedArray.Etc);
        CorsairSetLedsColorsFlushBuffer();
        return;
    }

    /// A function that sets all keyboard Enum Ids., Each CorsairLedColor has 16bytes.
    void AssignKeyboardLedArrays(void) {
        LedArray.Keyboard = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 167);
        for (int i = 0; i < 147; i++) LedArray.Keyboard[i].ledId = static_cast<CorsairLedId>(i + 1);
        LedArray.Keyboard[147].ledId = static_cast<CorsairLedId>(154);
        for (int i = 148; i < 167; i++) LedArray.Keyboard[i].ledId = static_cast<CorsairLedId>(i + 22);
        return;
    }
    /// A function that sets all Mouse Enum ids.
    void AssignMouseLedArrays(void) {
        LedArray.Mouse = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 4);
        for (int i = 0; i < 4; i++) LedArray.Mouse[i].ledId = static_cast<CorsairLedId>(i + 148);
        return;
    }
    /// A function that sets all headset enum ids.
    void AssignHeadsetLedArrays(void) {
        LedArray.Headset = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 2);
        for (int i = 0; i < 2; i++) LedArray.Headset[i].ledId = static_cast<CorsairLedId>(i + 152);
        return;
    }
    /// A function  that sets all mousemat enum ids.
    void AssignMouseMatLedArrays(void) {
        LedArray.MouseMat = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 15);
        for (int i = 0; i < 15; i++) LedArray.MouseMat[i].ledId = static_cast<CorsairLedId>(i + 155);
        return;
    }
    /// A function that sets all headsetstand enum ids.
    void AssignHeadSetStandLedArrays(void) {
        LedArray.HeadsetStand = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 9);
        for (int i = 0; i < 9; i++) LedArray.HeadsetStand[i].ledId = static_cast<CorsairLedId>(i + 191);
        return;
    }
    /// A function that sets all other etc device enum ids.
    void AssignEtcLedArrays(void) {
        if (!DidEtcInit) {
            LedArray.Etc = (CorsairLedColor*)malloc(sizeof(CorsairLedColor) * 730);
            for (int i = 0; i < 730; i++) LedArray.Etc[i].ledId = static_cast<CorsairLedId>(i + 189);
            DidEtcInit = true;
        }
        return;
    }

    /// This function is for making SetAllLedColor function.
    /// Since the user might not have or might have some devices, flashing all the devices into one color can be a huge task and
    /// time consuming task. So I have made a member function pointer array to run each correspoing code to save resource.
    /// For Example, if we have only Mouse, then we will get only SetMouseColor function's address to our function pointer array.
    /// After running SetAllLedColor, the function will just run SetMouseColor. Which means that any unecessary or unconnected devices
    /// would not be asked to set LED to specific color. Please check documentation more.
    void MakeSetAllLedFunction(void) {

        SetLedFunctionPointerArray = (SetLedFunctionPointer*)malloc(sizeof(SetLedFunctionPointer) * 6);

        if (Connected.Headset) SetLedFunctionPointerArray[0] = &Corsair::SetHeadsetColors;
        if (Connected.Mouse) SetLedFunctionPointerArray[1] = &Corsair::SetMouseColors;
        if (Connected.Keyboard) SetLedFunctionPointerArray[2] = &Corsair::SetKeyboardColors;
        if (Connected.MouseMat) SetLedFunctionPointerArray[3] = &Corsair::SetMouseMatColors;
        if (Connected.HeadsetStand) SetLedFunctionPointerArray[4] = &Corsair::SetHeadSetStandColors;
        if (Connected.Etc) SetLedFunctionPointerArray[5] = &Corsair::SetEtcColors;
        //Storing bunch of member function pointers to the pointer array.

        DevInfo.TotalFunctionPointerCounts = Connected.HeadsetStand + Connected.Etc + Connected.Headset + Connected.Keyboard + Connected.Mouse + Connected.MouseMat;
        //TotalFunctionPointerCounts would be used to check how many times to iterate when performing SetAllLedColor function below.
        return;
    }

    /// A Function that sets all Corsair's devices into one color.
    /// This function is kind of dynamic in order to save the computer's resource.
    /// @param Value The RGBVAL type of data to set color as

    void SetAllLedColor(RGBVAL Value) {
        //void SetAllLedColor(int R, int G, int B){
        for (int i = 0; i < DevInfo.TotalFunctionPointerCounts; i++) {
            (this->*SetLedFunctionPointerArray[i])(Value);
            //(this->*SetLedFunctionPointerArray[i])(R,G,B);
        }
        return;
    }
};