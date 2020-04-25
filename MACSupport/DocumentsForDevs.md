## Program Structure Documentations for Developers
Welcome to Program Structure Documentations for developers section here. As you know, the program is written with two major parts; Python and C++.

 - **Python**  : For High-Level process, such as screen reactive projects. 
 - **C++** : For Low-Level LED Controlling process, such as setting LEDs.

Both two programs are connected via socket communications in port 37716 by default. I do know that this is not the best option, however using share memory as a single process is more complicated and I cannot make that kind of high skill based program yet. 

I am going to call C++ side of the program as **Engine**, and Python side of the program as **Handle Script**. The connection between **Engine** and the **Handle Script** would be called as a **Bridge**.

The Diagram would be something like this below.

![enter image description here](https://raw.githubusercontent.com/gooday2die/AllPeripherals/master/MACSupport/GithubAssets/MacFunctionStructureVer1.png)

## Function Documentations for Developers - C++
Welcome to this function documentations here. I expect you having some C++ knowledge in order to use my functions here. The hierarchy workflow of C++ side is something like below

![enter image description here](https://raw.githubusercontent.com/gooday2die/AllPeripherals/master/MACSupport/GithubAssets/C++.png)

**Functions of main.cpp**
This is the source code file that contains the main entry point of the program. 
 - **void SyncAllColors(Corsair, ConnectionBridge)**
A function that syncs all colors automatically.
@param : Corsair object type to control Corsair devices
@param : ConnectionBridge type object to receive transmissions.

 - **int main(int argc, const char * argv[])**
The main entry of this C++ program. Argv and Argc would not be used currently. However left those two parameters just in case for the future.


**Functions of Wrappers/CorsairWrapper.cpp**
This is the source code file that contains everything related to the Corsair LED control of the program.

 - **`Class Corsair`**
The main class of Corsair LED control module. All those following listed items are member function of class Corsair.

1. **`Corsair()`**
A constructor member function for class Corsair. This automatically initializes all the needed variables and structure datatypes for the program to operate. Also performs some major Corsair control Requests for device control.

 2. **`void SetDeviceInfo(CorsairInfo DevInfo)`**
A member function that reads all the connected devices and assigns ColorLedArrays for future use. This function shows device counts and all those necessary details. 

3. **`void initStructures(void)`**
A member function that initializes all necessary structure data type variables for stable and safer operation of this program.

4. **`void SetLedColorByID(CorsairLedId LedID, int R, int G, int B)`**
A member function that sets a specific LED into specific color. The LED information is noted somewhere in the [CorsairLedIdEnum.h](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CUESDK.framework/Versions/A/Headers/CorsairLedIdEnum.h) Please note that using this function is depreciated by Official Corsair SDK documentation. The only warning of this whole program was due to this function. 

5. **`void  SetLedColors(int DeviceIndex, int size, CorsairLedColor* LedColorArray)`** 
A member function that sets a specific LED into specific color using CorsairLedColor Structure. This can set multiple colors at once if you use parameter `int size` and make `CorsairLedColor* LedColorArray` an array type of CorsairLedColor. The CorsairLedColor structure is written by Official Corsair themselves and is noted in [CUESDK.h](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CUESDK.framework/Versions/A/Headers/CUESDK.h) in line 196.

6. **`void  SetHeadsetColors(RGBVAL Value)`**
A member function that sets All LEDs in your HeadSet to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)  If this function is called before `AssignHeadsetLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

7. **`void  SetKeyboardColors(RGBVAL Value)`**
A member function that sets All LEDs in your Keyboard to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)   If this function is called before `AssignKeyboardLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

8. **`void  SetMouseColors(RGBVAL Value)`**
A member function that sets All LEDs in your Mouse to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)   If this function is called before `AssignMouseLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

9. **`void  SetHeadSetStandColors(RGBVAL Value)`**
A member function that sets All LEDs in your HeadSetStand to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)   If this function is called before `AssignHeadSetStandLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

10. **`void  SetMouseMatColors(RGBVAL Value)`**
A member function that sets All LEDs in your MouseMat to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)   If this function is called before `AssignMouseMatLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

11. **`void  SetEtcColors(RGBVAL Value)`**
A member function that sets All LEDs in your ETC Devices to a specific `RGBVAL` format. The declaration of RGBVAL Structure is set in [RGBColor.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/RGBColor.hpp)   If this function is called before `AssignEtcLedArrays` it would cause Segmentation fault due to accessing uninitialized and not allocated memory address. 

12. **`void  AssignKeyboardLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

13. **`void  AssignMouseLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

14. **`void  AssignHeadsetLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

15. **`void  AssignMouseMatLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

16. **`void  AssignHeadSetStandLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

17. **`void  AssignEtcLedArrays(void)`**
A member function that assigns LedArray. In order for this program to set a whole device's color into one color, we make an array of CorsairLedColor structure. Since the SDK offers us multiple LED settings at once using array  and size, we do that this way. We save the CorsairLedColor array into another Strucuture called `LedIdArray` please check Structure information at [CorsairWrapper.hpp](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/cppSide/AllPheriperalsCPP/Wrappers/CorsairWrapper.hpp) in line 56

18. **`void  MakeSetAllLedFunction(void)`**
A member function that makes a function called `SetAllColor`. Since querying not connected devices into one color is not a good idea, I had decied to make custom functions using Function Pointers. This function generates Function Pointer array and sets those array with function addresses. 

19. **`void  SetAllLedColor(RGBVAL Value)`**
A member function that sets all color of all Corsair Devices into one color assigned. This function should be called after running `MakeSetAllLedFunction` function up above. If not, it would cause Segmentation fault due to accessing uninitialized memory address.

**Functions of Networks/Bridge.cpp**
This is the source code file that contains everything related to the communication bridge between C++ Engine and Python Handle Script. 

**- Class ConnectionBridge**
The main class of communication Bridge module. All those following listed items are member function of class ConnectionBridge.

1. **`ConnectrionBridge(void)`**
A constructor member function for class ConnectionBridge

2. **`void  intializeBeforeColor(void)`**
A member function that initialzes the main Structure of `RGBColor` in order to make everything work safe. I do know that just initializing the Structure datatype in the declaration would be another option, however It results warnings. So I have decided to do it so.

3. **`void  getOperationMode(void)`**
A member function that gets operation mode from Python Handle Script and decides which mode this C++ Engine should take right now.

4. **`RGBVAL getRGBValues(void)`**
A member function that gets RGBValues from Python Handle Script and stores it in a local instance structure and returns as its return value.

5. **`bool  isDifferentColor(RGBVAL newVal)`**
A member function that decides whether the received color is new color or not. If received color is the same as the last color, it returns `false`. If received color is different from the previous one, it returns `true` and sets `BeforeColor` to `newVal`. This function is important in terms of deciding whether to set a new color or keep lighting the same color. If we can do a little less query to the Engine itself, it would save some resource.

## Function Documentations for Developers - Python
 Welcome to this function documentations here. I expect you having some Python knowledge in order to use my functions here. The hierarchy workflow of Python side is something like below
 
![enter image description here](https://raw.githubusercontent.com/gooday2die/AllPeripherals/master/MACSupport/GithubAssets/Pythonside.png)

**Functions of main.py**
A source code that stores all the necessary code for running the whole Python Handle Script of this program.
 - **`print_logo(easter_egg_on)`**
A function that prints logo when starting. I will not tell you what an Easter egg is :b If you want to turn it on, then true. If not, false

 - **`parse_argv()`**
A function that parses argv and argcs. This Python script 'can' receive some arguments when called at the first place. This function receives those arguments and parses in the right way we want. The parameters are `-easteregg` and`-operationmode`. First parameter decides to show Easter egg or not by `true` or `false` values. Second parameter decides which mode to operate without asking the user in the program runtime. There are currently two running modes `1 : Screen Reactive, 2 : RainbowAll` . If you enter wrong arguments here, the program would exit itself and return to OS.

- **`screen_reactive()`**
A function that sets itself on ScreenReactive mode. It will automatically set itself on Screen Reactive mode and do all the things needed by calling this function.

 - **`rainbow_all()`**
A function that sets itself on RainbowAll mode. It will automatically set itself on Rainbow All mode and do all the things needed by calling this function. It will ask for the speed. Default speed is 0.005. The higher the slower. 

**Functions of Bridge.py**
A source code that stores all the necessary codes for running communication bridge of the program.

 - **Class Bridge**
 The main class of communication Bridge module. All those following listed items are methods of class Bridge.
 1. **`__init__(self, mode, port=37716)`**
A intialzer method for class Bridge. `mode` is the operating mode that we would like to run this script. `port` is the port of socket that the server would be listening on C++ Engine side of the program. Defaults to `37716`

2. **`connect_server(self)`**
A method that connects to server for the first time. It initializes the Socket object instance that would be used throughout this program. 


3. **`send_operation_mode(self)`**
A method that sends the server which operation mode that this program would be running right now. It would send the instance variable `self.operation_mode` in `bytearray` object through Socket.

4. **`send_rgb_value(self, r, g, b)`**
A method that sends RGB values to the server. It will generate a `bytearray` object and sent it through Socket.

**Functions of ScreenReactive.py**
A source code that stores all the necessary codes for running Handle Script ScreenReactive.

 - **Class ScreenReactive**
 The main class of ScreenReactive module. All those following listed items are methods of class ScreenReactive.
 1. **`__init__(self, period=0.1)`**
A intialzer method for class ScreenReactive. `period` is the parameter which indicates the time between each `return_rgb` method. The time usually taken when taking a screenshot of the screen and then calculates the most dominant color is about 0.15. So the period is default 0.1 

2. **`return_rgb(self)`**
A method that takes screenshot and then calculates the most dominant color of the screen. It returns the `list` object of most dominant color in `[R, G, B]` sequence.

**Functions of RainbowAll.py**
A source code that stores all the necessary codes for running Handle Script RainbowAll.

 - **Class RainbowAll**
 The main class of RainbowAll module. All those following listed items are methods of class RainbowAll.

1. **`__init__(self, BridgeObj, speed=0.005)`**
A intialzer method for class ScreenReactive. `BridgeObj` is the `Bridge` object from `Bridge.py` that contains information about server connection socket. `speed` is the speed between Rainbow Shifting effect.

2. **`rainbow_all(self)`**
A method that sets all colors into Rainbow shift mode in speed that is issued up above as instance variable `self.speed`. 
