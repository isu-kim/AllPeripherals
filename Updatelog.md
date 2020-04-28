## Update Log
**- 20.04.28 : Fixed `segmentation fault` when calling `SetAllLedColor`  in `CorsairWrapper.cpp`**
This Error was happening due to function pointer array. When a specific Corsair device is not connected, `MakeSetAllLedFunction` sets the function pointer as `NULL` pointer. `SetAllLedColor` calls this `NULL` pointer and results `segmentation fault`. I have added a function called `UselessFunction(RGBVAL)` to make not connected device function pointer to this function for safety. Reported by  a good friend of mine Christopher Dillard

**- 20.04.28 : Changed how `RainbowAll` function works**
The previous version does run `RainbowAll` effect pretty well. However, the Python Handle Script sends too much repetitive information. So I have turned the `RainbowAll` function into C++ engine function. So, the Python Handle Script now just needs to send C++ engine program to run `RainbowAll` effect and then closes connection. All the `RainbowAll` effect is done by C++ engine program now.
