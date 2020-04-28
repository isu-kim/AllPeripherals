#pragma once
#include "CorsairWrapper.cpp"
#include "RazerWrapper.cpp"

#include <iostream>

#define CORSAIR 1
#define RAZER 2

#define SUPPORTEDSDKCOUNT 2 // This is currently 2 since only Corsair and Razer SDKs are supported.


typedef struct _WrapperSDKInfo{ // This would be used for indicating which SDK should be used.
	bool Corsair;
	bool Razer;	
}WrapperSDKInfo;

typedef struct _WraperDeviceInfo { // This would be used for making set All function for the future.
	int Mouse[SUPPORTEDSDKCOUNT];
	int Keyboard[SUPPORTEDSDKCOUNT];
	int Mousemat[SUPPORTEDSDKCOUNT];
	int Headset[SUPPORTEDSDKCOUNT];
	int Etc[SUPPORTEDSDKCOUNT];
}WrapperDeviceInfo;