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



	bool InitResult;
	bool ShouldRazerBeUsed;
	RazerConnectedDeviceBool ConnectedDevices;

	/**
	A constructor member function for Razer class.

	@param {int} amount how many requests should be sent for a command. Razer Chroma SDK seems not
			to register command at once. Thus it is necessary to try multiple times.
	@param {int} wait how much milisecond should be waited between requests.
	@return void
	*/

	Razer() {
		request_amount = 0;
		request_wait = 0;

		InitResult = initalize();

		if (!InitResult) {
			std::cout << "[Razer] Failed to initialize Razer Chroma SDK" << std::endl;
		}
		std::cout << "[Razer] Successfully initialized Razer Chroma SDK" << std::endl;
		CheckRazerDeviceConnection();
		ShouldRazerBeUsed = DecideRazerSDKEnable();
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

	void SetAllLedColor(RGBVAL tempVal) {
		// if (debug) std::cout << "[CPeripheral] Set color " << (int)r << ", " << (int)g << ", " << (int)b << " to All Razer Devices." << std::endl;

		SetMouseColor(tempVal, ChromaSDK::Mouse::RZLED_ALL);
		SetKeyboardColor(tempVal);
		SetMousepadColor(tempVal);
		SetHeadsetColor(tempVal);
		SetKeypadColor(tempVal);

		return;
	}

	void InitializeConnectedDeviceStructure(void) {
		ConnectedDevices.Mouse = false;
		ConnectedDevices.Keyboard = false;
		ConnectedDevices.Etc = false;
		ConnectedDevices.Headset = false;
		ConnectedDevices.Keypads = false;
		ConnectedDevices.MouseMat = false;

		return;
	}

	bool IsDeviceConnected(RZDEVICEID DeviceId)
	{
		if (QueryDevice != NULL)
		{
			ChromaSDK::DEVICE_INFO_TYPE DeviceInfo = {};
			RZRESULT Result = QueryDevice(DeviceId, DeviceInfo);
			return DeviceInfo.Connected;
		}

		return false;
	}

	void CheckRazerMouseConnection(void) {
		bool IsMouseConnected;
		IsMouseConnected = IsDeviceConnected(ChromaSDK::DEATHADDER_CHROMA) |
			IsDeviceConnected(ChromaSDK::MAMBA_CHROMA_TE) |
			IsDeviceConnected(ChromaSDK::DIAMONDBACK_CHROMA) |
			IsDeviceConnected(ChromaSDK::MAMBA_CHROMA) |
			IsDeviceConnected(ChromaSDK::NAGA_EPIC_CHROMA) |
			IsDeviceConnected(ChromaSDK::NAGA_CHROMA) |
			IsDeviceConnected(ChromaSDK::OROCHI_CHROMA) |
			IsDeviceConnected(ChromaSDK::NAGA_HEX_CHROMA) |
			IsDeviceConnected(ChromaSDK::DEATHADDER_ELITE_CHROMA); // For checking any of Razer devices are connected

		if (IsMouseConnected) { // This is literally stupid idea, however there seems to be no option to show devices other than this...
			if (IsDeviceConnected(ChromaSDK::DEATHADDER_CHROMA)) std::cout << "[Razer] Mouse : Deathadder Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::MAMBA_CHROMA_TE)) std::cout << "[Razer] Mouse : Mamba Chroma TE" << std::endl;
			if (IsDeviceConnected(ChromaSDK::DIAMONDBACK_CHROMA)) std::cout << "[Razer] Mouse : Diamondback Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::MAMBA_CHROMA)) std::cout << "[Razer] Mouse : Mamba Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::NAGA_EPIC_CHROMA)) std::cout << "[Razer] Mouse : Naga Epic Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::NAGA_CHROMA)) std::cout << "[Razer] Mouse : Naga Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::NAGA_HEX_CHROMA)) std::cout << "[Razer] Mouse : Naga Hex Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::DEATHADDER_ELITE_CHROMA)) std::cout << "[Razer] Mouse : Deathadder Elite Chroma" << std::endl;
		}
		ConnectedDevices.Mouse = IsMouseConnected;
	}

	void CheckRazerKeyboardConnection(void) {
		bool IsKeyboardConnected; 
		IsKeyboardConnected = IsDeviceConnected(ChromaSDK::BLACKWIDOW_CHROMA) |
			IsDeviceConnected(ChromaSDK::BLACKWIDOW_CHROMA_TE) |
			IsDeviceConnected(ChromaSDK::DEATHSTALKER_CHROMA) |
			IsDeviceConnected(ChromaSDK::OVERWATCH_KEYBOARD) |
			IsDeviceConnected(ChromaSDK::BLACKWIDOW_X_CHROMA) |
			IsDeviceConnected(ChromaSDK::BLACKWIDOW_X_TE_CHROMA) |
			IsDeviceConnected(ChromaSDK::ORNATA_CHROMA) |
			IsDeviceConnected(ChromaSDK::BLADE_STEALTH) |
			IsDeviceConnected(ChromaSDK::BLADE); // For checking any of Razer devices are connected

		if (IsKeyboardConnected) { // This is literally stupid idea, however there seems to be no option to show devices other than this...
			if (IsDeviceConnected(ChromaSDK::BLACKWIDOW_CHROMA)) std::cout << "[Razer] Keyboard : Blackwindow Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::BLACKWIDOW_CHROMA_TE)) std::cout << "[Razer] Keyboard : Blackwidow Chroma TE" << std::endl;
			if (IsDeviceConnected(ChromaSDK::DEATHSTALKER_CHROMA)) std::cout << "[Razer] Keyboard : Deathstalker Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::OVERWATCH_KEYBOARD)) std::cout << "[Razer] Keyboard : Overwatch Keyboard" << std::endl;
			if (IsDeviceConnected(ChromaSDK::BLACKWIDOW_X_CHROMA)) std::cout << "[Razer] Keyboard : Blackwidow X Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::BLACKWIDOW_X_TE_CHROMA)) std::cout << "[Razer] Keyboard : Blackwidow X Chroma TE" << std::endl;
			if (IsDeviceConnected(ChromaSDK::ORNATA_CHROMA)) std::cout << "[Razer] Keyboard : Ornata Chroma" << std::endl;
			if (IsDeviceConnected(ChromaSDK::BLADE_STEALTH)) std::cout << "[Razer] Keyboard : Blade Stealth" << std::endl;
			if (IsDeviceConnected(ChromaSDK::BLADE)) std::cout << "[Razer] Keyboard : Blade" << std::endl;
		}
		ConnectedDevices.Keyboard = IsKeyboardConnected;
	}

	void CheckRazerHeadsetConnection(void) {
		bool IsHeadsetConnected;
		IsHeadsetConnected = IsDeviceConnected(ChromaSDK::KRAKEN71_CHROMA) |
			IsDeviceConnected(ChromaSDK::MANOWAR_CHROMA); // For checking any of Razer devices are connected

		if (IsHeadsetConnected) {
			if(IsDeviceConnected(ChromaSDK::KRAKEN71_CHROMA)) std::cout << "[Razer] Headset : Kraken 7.1 Chroma" << std::endl;
			if(IsDeviceConnected(ChromaSDK::MANOWAR_CHROMA)) std::cout << "[Razer] Headset : Manowar Chroma" << std::endl;
		}
		ConnectedDevices.Headset = IsHeadsetConnected;
	}

	void CheckRazerMousematConnection(void) {
		bool IsMousematConnected;
		IsMousematConnected = IsDeviceConnected(ChromaSDK::FIREFLY_CHROMA) ; // For checking any of Razer devices are connected

		if (IsMousematConnected) std::cout << "[Razer] Mousemat : Firefly Chroma" << std::endl;
		ConnectedDevices.MouseMat = IsMousematConnected;
	}

	void CheckRazerKeypadConnection(void) {
		bool IsKeypadConnected;
		IsKeypadConnected = IsDeviceConnected(ChromaSDK::TARTARUS_CHROMA)|
			IsDeviceConnected(ChromaSDK::ORBWEAVER_CHROMA); // For checking any of Razer devices are connected

		if (IsKeypadConnected) {
			if(IsDeviceConnected(ChromaSDK::TARTARUS_CHROMA)) std::cout << "[Razer] Keypad : Tartaus Chroma" << std::endl;
			if(IsDeviceConnected(ChromaSDK::ORBWEAVER_CHROMA)) std::cout << "[Razer] Keypad : Orbweaver Chroma" << std::endl;
		}
		ConnectedDevices.Keypads = IsKeypadConnected;
	}

	void CheckRazerEtcConnection(void) {
		bool IsEtcConnected;
		IsEtcConnected = IsDeviceConnected(ChromaSDK::LENOVO_Y900) |
			IsDeviceConnected(ChromaSDK::LENOVO_Y27) | 
			IsDeviceConnected(ChromaSDK::CORE_CHROMA); // For checking any of Razer devices are connected

		if (IsEtcConnected) {
			if (IsDeviceConnected(ChromaSDK::LENOVO_Y900)) std::cout << "[Razer] ETC : Lenovo Y900" << std::endl;
			if (IsDeviceConnected(ChromaSDK::LENOVO_Y27)) std::cout << "[Razer] ETC : Lenovo Y27" << std::endl;
			if (IsDeviceConnected(ChromaSDK::CORE_CHROMA)) std::cout << "[Razer] ETC : Core Chroma (Accessories)" << std::endl;
		}
		ConnectedDevices.Etc = IsEtcConnected;
	}

	void CheckRazerDeviceConnection(void) {
		CheckRazerMouseConnection();
		CheckRazerHeadsetConnection();
		CheckRazerKeyboardConnection();
		CheckRazerKeypadConnection();
		CheckRazerMousematConnection();
		CheckRazerEtcConnection();

		std::cout << "[Razer] Finished detecting Razer devices." << std::endl;
	}

	bool DecideRazerSDKEnable(void) {
		return ConnectedDevices.Etc |
			ConnectedDevices.Headset |
			ConnectedDevices.Keyboard |
			ConnectedDevices.Keypads |
			ConnectedDevices.Mouse |
			ConnectedDevices.MouseMat;
	}
};
