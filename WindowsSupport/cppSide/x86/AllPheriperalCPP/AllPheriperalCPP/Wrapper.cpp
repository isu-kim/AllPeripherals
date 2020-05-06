#include "Wrapper.hpp"

class Wrapper {
public:

	int a = printf("[Wrapper] Initializng all SDK wrappers...\n"); // This is stupid expression. But I will do this to show this message first.
	Corsair CorsairObj = Corsair();
	Razer RazerObj = Razer();
	WrapperSDKInfo SDKInfo;
	WrapperDeviceInfo DeviceInfo;

	Wrapper(void) {
		InitWrapperSDKInfo();
	}

	/// A member function that intializes which SDK wrappers should be called during the program.
	void InitWrapperSDKInfo(void) {
		SDKInfo.Corsair = false; 
		SDKInfo.Razer = false;

		if (CorsairObj.DeviceCount > 0) {
			SDKInfo.Corsair = true;
			std::cout << "[Wrapper] Using Corsair SDK" << std::endl;
		}
		if (RazerObj.InitResult) {
			SDKInfo.Razer = true;
			std::cout << "[Wrapper] Using Razer SDK" << std::endl;
		}
		return;
	}

	void SetAllLedColor(RGBVAL value) {
		CorsairObj.newSetAllLedColor(value);
		RazerObj.SetAllLedColor(value);
	}

	void test(void) {
	}
};