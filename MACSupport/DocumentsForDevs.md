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
