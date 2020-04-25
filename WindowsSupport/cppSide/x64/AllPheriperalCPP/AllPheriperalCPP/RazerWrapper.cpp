/**
	CPeripheral
	RazerWrapper.cpp
	Purpose: A wrapper of Razer Chroma SDK for my CPeripheral.

	@author Gooday2die(Isu Kim)
	@version 0.1 19/19/12
*/

#include "RazerWrapper.hpp"

class Razer {
public:
	bool debug = false;

	int request_amount;
	int request_wait;

	const COLORREF BLACK = RGB(0, 0, 0);
	const COLORREF WHITE = RGB(255, 255, 255);
	const COLORREF RED = RGB(255, 0, 0);
	const COLORREF GREEN = RGB(0, 255, 0);
	const COLORREF BLUE = RGB(0, 0, 255);
	const COLORREF YELLOW = RGB(255, 255, 0);
	const COLORREF PURPLE = RGB(128, 0, 128);
	const COLORREF CYAN = RGB(00, 255, 255);
	const COLORREF ORANGE = RGB(255, 165, 00);
	const COLORREF PINK = RGB(255, 192, 203);
	const COLORREF GREY = RGB(125, 125, 125);

	typedef RZRESULT(*INIT)(void);
	typedef RZRESULT(*UNINIT)(void);
	typedef RZRESULT(*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);
	typedef RZRESULT(*DELETEEFFECT)(RZEFFECTID EffectId);
	typedef RZRESULT(*REGISTEREVENTNOTIFICATION)(HWND hWnd);
	typedef RZRESULT(*UNREGISTEREVENTNOTIFICATION)(void);
	typedef RZRESULT(*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE& DeviceInfo);

	INIT Init = nullptr;
	UNINIT UnInit = nullptr;
	CREATEEFFECT CreateEffect = nullptr;
	CREATEKEYBOARDEFFECT CreateKeyboardEffect = nullptr;
	CREATEMOUSEEFFECT CreateMouseEffect = nullptr;
	CREATEHEADSETEFFECT CreateHeadsetEffect = nullptr;
	CREATEMOUSEPADEFFECT CreateMousepadEffect = nullptr;
	CREATEKEYPADEFFECT CreateKeypadEffect = nullptr;
	SETEFFECT SetEffect = nullptr;
	DELETEEFFECT DeleteEffect = nullptr;
	QUERYDEVICE QueryDevice = nullptr;
	HMODULE m_ChromaSDKModule = NULL;

	/**
	A constructor member function for Razer class.

	@param {int} amount how many requests should be sent for a command. Razer Chroma SDK seems not
			to register command at once. Thus it is necessary to try multiple times.
	@param {int} wait how much milisecond should be waited between requests.
	@return void
	*/

	Razer(int amount, int wait) {
		request_amount = amount;
		request_wait = wait;

		bool init_result;
		init_result = initalize();

		if (!init_result) {
			std::cout << "[Razer] Failed to initialize Razer Chroma SDK" << std::endl;
			exit(0);
		}
		std::cout << "[Razer] Successfully initialized Razer Chroma SDK" << std::endl;
		CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, nullptr, nullptr);
	}

	/**
	A function for initializing Razer SDK. Loads DLL and saves function address for future use.

	@param void
	@return bool
	*/

	bool initalize(void) {
		const bool already_called = false;

		if (!already_called) {
			if (m_ChromaSDKModule == nullptr)
			{
				m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);
				if (m_ChromaSDKModule == nullptr)
				{
					return FALSE;
				}
			}

			if (Init == nullptr)
			{
				auto Result = RZRESULT_INVALID;
				Init = reinterpret_cast<INIT>(GetProcAddress(m_ChromaSDKModule, "Init"));
				if (Init)
				{
					Result = Init();
					if (Result == RZRESULT_SUCCESS)
					{
						CreateEffect = reinterpret_cast<CREATEEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateEffect"));
						CreateKeyboardEffect = reinterpret_cast<CREATEKEYBOARDEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect"));
						CreateMouseEffect = reinterpret_cast<CREATEMOUSEEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateMouseEffect"));
						CreateHeadsetEffect = reinterpret_cast<CREATEHEADSETEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateHeadsetEffect"));
						CreateMousepadEffect = reinterpret_cast<CREATEMOUSEPADEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateMousepadEffect"));
						CreateKeypadEffect = reinterpret_cast<CREATEKEYPADEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateKeypadEffect"));
						SetEffect = reinterpret_cast<SETEFFECT>(GetProcAddress(m_ChromaSDKModule, "SetEffect"));
						DeleteEffect = reinterpret_cast<DELETEEFFECT>(GetProcAddress(m_ChromaSDKModule, "DeleteEffect"));
						QueryDevice = reinterpret_cast<QUERYDEVICE>(GetProcAddress(m_ChromaSDKModule, "QueryDevice"));

						if (CreateEffect &&
							CreateKeyboardEffect &&
							CreateMouseEffect &&
							CreateHeadsetEffect &&
							CreateMousepadEffect &&
							CreateKeypadEffect &&
							SetEffect &&
							DeleteEffect &&
							QueryDevice)
						{
							return TRUE;
						}
						else
						{
							return FALSE;
						}
					}
				}
			}

			return TRUE;
		}

		else {
			return TRUE;
		}
	}

	/**
	A function for setting mouse color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@param {ChromaSDK::Mouse::RZLED} led_posit Mouse LED position.
	@return void
	*/

	void SetMouseColor(RGBVAL tempVal, ChromaSDK::Mouse::RZLED led_posit) {
		ChromaSDK::Mouse::STATIC_EFFECT_TYPE StaticEffect = {};
		RZEFFECTID effect_id;
		RZRESULT result;

		StaticEffect.Color = RGB(tempVal.R, tempVal.G, tempVal.B);
		StaticEffect.LEDId = led_posit;

		CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &StaticEffect, &effect_id);
		result = (RZRESULT)SetEffect(effect_id);

		/*
		if (debug) {
			if (!(RZRESULT)result) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Mouse." << std::endl;
			else std::cout << "[CPeripheral] Failed to set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Mouse." << std::endl;
		}
		*/

		for (int i = 0; i < request_amount; i++) { // Razer devices do not light up at the first time.  you may change this.
			SetEffect(effect_id);
			Sleep(request_wait); // Spamming SDK does not seem to work. Setting 1 milisecond delay.
		}

		return;
	}

	/**
	A function for setting keyboard color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
	*/

	void SetKeyboardColor(RGBVAL tempVal) {
		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
		RZEFFECTID effect_id;
		RZRESULT result;

		StaticEffect.Color = RGB(tempVal.R, tempVal.G, tempVal.B);

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, &effect_id);
		result = (RZRESULT)SetEffect(effect_id);

		/*
		if (debug) {
			if (!(RZRESULT)result) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Keyboard." << std::endl;
			else std::cout << "[CPeripheral] Failed to set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Keyboard." << std::endl;
		}
		*/

		for (int i = 0; i < request_amount; i++) { // Razer devices do not light up at the first time.  you may change this.
			SetEffect(effect_id);
			Sleep(request_wait); // Spamming SDK does not seem to work. Setting 1 milisecond delay.
		}

		return;
	}

	/**
	A function for setting headset color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
	*/

	void SetHeadsetColor(RGBVAL tempVal) {
		ChromaSDK::Headset::STATIC_EFFECT_TYPE StaticEffect = {};
		RZEFFECTID effect_id;
		RZRESULT result;

		StaticEffect.Color = RGB(tempVal.R, tempVal.G, tempVal.B);

		CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &StaticEffect, &effect_id);
		result = (RZRESULT)SetEffect(effect_id);

		/*
		if (debug) {
			if (!(RZRESULT)result) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Headset." << std::endl;
			else std::cout << "[CPeripheral] Failed to set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Headset." << std::endl;
		}
		*/

		for (int i = 0; i < request_amount; i++) { // Razer devices do not light up at the first time.  you may change this.
			SetEffect(effect_id);
			Sleep(request_wait); // Spamming SDK does not seem to work. Setting 1 milisecond delay.
		}

		return;
	}

	/**
	A function for setting mousepad color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
*/

	void SetMousepadColor(RGBVAL tempVal) {
		ChromaSDK::Mousepad::STATIC_EFFECT_TYPE StaticEffect = {};
		RZEFFECTID effect_id;
		RZRESULT result;

		StaticEffect.Color = RGB(tempVal.R, tempVal.G, tempVal.B);

		CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &StaticEffect, &effect_id);
		result = (RZRESULT)SetEffect(effect_id);

		/*
		if (debug) {
			if (!(RZRESULT)result) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Mousepad." << std::endl;
			else std::cout << "[CPeripheral] Failed to set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Mousepad." << std::endl;
		}
		*/

		for (int i = 0; i < request_amount; i++) { // Razer devices do not light up at the first time.  you may change this.
			SetEffect(effect_id);
			Sleep(request_wait); // Spamming SDK does not seem to work. Setting 1 milisecond delay.
		}

		return;
	}

	/**
	A function for setting keypad color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
	*/

	void SetKeypadColor(RGBVAL tempVal) {
		ChromaSDK::Keypad::STATIC_EFFECT_TYPE StaticEffect = {};
		RZEFFECTID effect_id;
		RZRESULT result;

		StaticEffect.Color = RGB(tempVal.R, tempVal.G, tempVal.B);

		CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &StaticEffect, &effect_id);
		result = (RZRESULT)SetEffect(effect_id);

		/*
		if (debug) {
			if (!(RZRESULT)result) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Keypad." << std::endl;
			else std::cout << "[CPeripheral] Failed to set color " << (int)r << ", " << (int)g << ", " << (int)b << " to Razer Keypad." << std::endl;
		}
		*/

		for (int i = 0; i < request_amount; i++) { // Razer devices do not light up at the first time.  you may change this.
			SetEffect(effect_id);
			Sleep(request_wait); // Spamming SDK does not seem to work. Setting 1 milisecond delay.
		}

		return;
	}

	/**
	A function for setting all Razer device color to specific color

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
*/

	void SetAllColor(RGBVAL tempVal) {
		// if (debug) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to All Razer Devices." << std::endl;

		SetMouseColor(tempVal, ChromaSDK::Mouse::RZLED_ALL);
		SetKeyboardColor(tempVal);
		SetMousepadColor(tempVal);
		SetHeadsetColor(tempVal);
		SetKeypadColor(tempVal);

		return;
	}
};
