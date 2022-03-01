## AllPeripheral
> Also an updated version with the same project in `cython` can be found [here](https://github.com/gooday2die/PyRGBDev)

A program written in C++ and Python for synchronizing all SDKs with one program. Supports Windows and MacOS.

## Basic Info 

Personally I use those Peripherals for my inputs into computer

 - Mouse 1 : Razer  DeathAdder Elite
 - Mouse 2 : Corsair Glaive RGB Pro
 - Keyboard : Corsair K95 RGB Platinum
 - Mouse Pad : Corsair MM800 RGB
 - Head Phones : Corsair Void RGB Pro
 - GPU : RTX 2080 TI Gaming X Trio
 - And more soon...

As you can see, Mouse 1 and all the other devices are using the different programs for their RGB LED controls. Mouse 1 uses Razer SDK for their RGB LED controls. Meanwhile, all the other devices use Corsair ICUE SDK  for their RGB LED controls. 

Some of you might have seen some programs that does sync all the devices regardless of the manufacturer. However, those programs do have unsupported devices for me, such as Mouse Pad.
So, I am planning to make a program that syncs all the LED of devices together.

Since I possess Razer and Corsair products right now, I am now planning to sync both SDKs. Also, I have tested some many things with my personal devices and confirmed working on Windows 10 64bit and MacOS 10.15

## References

Unlike my project before, which is PyPheriperals, I am currently developing everything by myself. From low-level SDK wrappers to high-level Python handle scripts.

- Corsair ICUE SDK
[http://forum.corsair.com/v3/showthread.php?t=179027](http://forum.corsair.com/v3/showthread.php?t=179027)
for main Corsair ICUE SDK

- Razer Chroma SDK
[https://developer.razer.com/works-with-chroma/download/](https://developer.razer.com/works-with-chroma/download/) 
for main Razer Chroma SDK
 
 ## Goals
 The main goal is to sync as many devices as possible just by using this software. I do know that there would be definitely bugs and unsupported devices as well. However, I will try my best for this program.

 - Sync SDKs
 - Support APIs for other developers in the future
 - Remote Lighting Controls via Socket Communications. (Works internally and externally as well)
 - Sectional LED controls
 - WS2812B LED strip support

## Supported SDKs

 - Corsair ICUE 
 50% Complete.
 Now able to control any LEDs via ICUE.
 Working on key input response.


 - Razer SDK
 50% Complete.
 Now able to control any LEDs via DLLs using C++

- MysticLight SDK
0% Complete.
Special thanks to MSI for not offering a single example code and bad documentations.

- more soon..

## Supported Devices
None yet. However, those following devices would be supported for sure.
 - Razer  DeathAdder Elite [Razer SDK]
 - Corsair Glaive RGB Pro [ICUE SDK]
 - Corsair K95 RGB Platinum [ICUE SDK]
 - Corsair MM800 RGB [ICUE SDK]
 - Corsair Void RGB Pro [ICUE SDK]
 - Corsair NightSword RGB (Checked by Christopher Dillard)
 - Corsair K57 RGB WIRELESS (Checked by Christopher Dillard)
 - ~~RTX 2080 TI MSI  Gaming X Trio[Mystic Light]~~ I gave up.


## Demo Images
For more demo images, please check https://github.com/gooday2die/AllPeripherals/blob/master/Demo.md

![enter image description here](https://github.com/gooday2die/AllPeripherals/blob/master/GithubAssets/video_0%20%281%29.gif?raw=true)
Image showing all the device's LED colors are synced.

![enter image description here](https://github.com/gooday2die/AllPeripherals/blob/master/GithubAssets/video_1%20%281%29.gif?raw=true)
Image showing two different mouse SDKs are being synced. 
Sorry for low Quality gif. Had to resize it a bit for me to upload in the github.

![Screen Reactive Demo 1](https://github.com/gooday2die/AllPeripherals/blob/master/GithubAssets/demo1.gif?raw=true)

Screen Reactive Demo #1 Night Vision. 
Might take some time for the gif to load, since the file is huge. 

![Screen Reactive Demo 2](https://github.com/gooday2die/AllPeripherals/blob/master/GithubAssets/demo2.gif?raw=true)

Screen Reactive Demo #2 Flash Bang

![Screen Reactive Demo 3](https://github.com/gooday2die/AllPeripherals/blob/master/GithubAssets/demo3.gif?raw=true)

Screen Reactive Demo #3 Blood 

## Then, What About PyPheperial?
[PyPheperial]([https://github.com/gooday2die/PyPheperial](https://github.com/gooday2die/PyPheperial)) is my project which has almost the same code written entirely in Python. Since all the SDKs provided by the official manufacturers support mainly C++ or C#, implementing those libraries for the Python script is not an easy work as well as not an efficient way to use SDK. So I have decided to make the low-level of this program with C++ and high-level side of the program with Python for efficiency.

I would be mainly focusing on this project, AllPeripherals. However, I am not planning to drop the previous project. It is my one of most loved project and still would like to develop much more. 

## Updatelog
You can check updatelog [Here]([https://github.com/gooday2die/AllPeripherals/blob/master/Updatelog.md])(https://github.com/gooday2die/AllPeripherals/blob/master/Updatelog.md)

## ETC
I do know that there would be bugs and unsupported devices. However, I will be trying very hard to keep those as minimum. If you happen to visit this repository, feel free to suggest some ideas for this project. Also, contributions are always welcomed. If you want to be a contributor, just contact me  edina00@naver.com. 

*If there are some issues regarding copyrights, or other things, I would be happy to remove or replace them with other things in the future. Just let me know. *

I would like to thank all those who have visited this repository. Thanks.


