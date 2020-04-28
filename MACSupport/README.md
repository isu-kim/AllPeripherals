
## Mac Support
I am personally a huge fan of apple. Those are Mac devices that I own personally. Just to let you know.

- MBP "15 CTO 2010 - Retired... A good old friend of mine.
- MBP "15 CTO 2016 - For Camera and Other Works.
 - MBP "15 CTO 2017 - For YouTube watching and Music Production
 - MBP "15 CTO 2018 - For Development. 

I did not think those peripheral device companies would support any MacOS supports until last week. However, it seems they do. So I would be offering MacOS supports. 

**Fully supported SDKs**
 - Corsair - ICUE SDK. Fully working on 10.15
 - RAZER - Working on it. Would not work above 10.15 (Catalina)

**Currently Supported Mac Devices**
- MacBook Pro "15 TouchBar 2018 CTO - 10.15
- iMac - 10.15  (By Christopher Dillard)

**Confirmed Working Devices**

 - Corsair K95 RGB Platinum 
 - Corsair Glaive RGB Pro
 - Corsair MM800 RGB Pro
 - Corsair VOID RGB Pro
 - Corsair NightSword RGB (By Christopher Dillard)
- Corsair K57 RGB WIRELESS (By Christopher Dillard)

## Installation Guide - For Normal Users
In order to run this program, you should have Python3 (I would suggest you using Python 3.7.x) installed in your Mac. Nowadays there is a default python installed in your MacOS which is 2.7.x version. However, the version is **NOT** compatible with my program. Also there are several dependency modules and libraries for this script to work. 

 - MSS - for Taking screenshots
 - PIL or PILLOW - for Processing that taken screenshot
 - Numpy - for Clustering Purpose
 - Scipy - for Clustering Purpose

I would be offering a step by step install below. 

 1. Download Python3 from the official [link](https://www.python.org/downloads/) Please please download 3.7.6 version. I have not checked any other version working. 
 2. After you have installed Python3, please open "Terminal" app
 3. Enter `python3 --version` and verify the version installed. If you happen to have error something like `command not found: python3` it means that Python is not successfully installed.
 4. Then enter following codes to install our dependency modules. 
 5. `python3 -m pip install MSS`
 6. `python3 -m pip install pillow`
7. `python3 -m pip install numpy`
8. `python3 -m pip install scipy`
9. If you have successfully installed those packages, it would be working soon!
10. Please download the Release zip file from [link](https://github.com/gooday2die/AllPeripherals/releases) and unzip it in a directory you want. Please check if you are installing the right version!
11. If you unzip the zip file, there would be two directories and two files. (In version Mac.v.1.0)
- CppSide
- PythonSide
- Rainbow.sh
- ScreenReactive.sh
12. If you do know how to run Python files and Binary executable files through terminal commands, please do it so. Run CppSide first and the run PythonSide main.py.
13. If you do not know how to run those files manually, please doubleclick ScreenReactive.sh and then it would launch Screen Reactive lighting. Rainbow.sh would launch shifting Rainbow color## Installation Guide
In order to run this program, you should have Python3 (I would suggest you using Python 3.7.x) installed in your Mac. Nowadays there is a default python installed in your MacOS which is 2.7.x version. However, the version is **NOT** compatible with my program. Also there are several dependency modules and libraries for this script to work. 

 - MSS - for Taking screenshots
 - PIL or PILLOW - for Processing that taken screenshot
 - Numpy - for Clustering Purpose
 - Scipy - for Clustering Purpose

I would be offering a step by step install below. 

 1. Download Python3 from the official [link](https://www.python.org/downloads/) Please please download 3.7.6 version. I have not checked any other version working. 
 2. After you have installed Python3, please open "Terminal" app
 3. Enter `python3 --version` and verify the version installed. If you happen to have error something like `command not found: python3` it means that Python is not successfully installed.
 4. Then enter following codes to install our dependency modules. 
 5. `python3 -m pip install MSS`
 6. `python3 -m pip install pillow`
7. `python3 -m pip install numpy`
8. `python3 -m pip install scipy`
9. If you have successfully installed those packages, it would be working soon!
10. Please download the Release zip file below and unzip it in a directory you want.
11. If you unzip the zip file, there would be two directories and two files. (In version Mac.v.1.0)
- CppSide
- PythonSide
- Rainbow.sh
- ScreenReactive.sh
12. If you do know how to run Python files and Binary executable files through terminal commands, please do it so. Run CppSide first and the run PythonSide main.py.
13. If you do not know how to run those files manually, please doubleclick ScreenReactive.sh and then it would launch Screen Reactive lighting. Rainbow.sh would launch shifting Rainbow color

## For Devs

**Before you start...**

This Installation guide is for developers who would like to modify or make use of my project for their future projects. The low-level of the program is written in C++ with Xcode IDE and high-level of the program is written in Python. Also, since the MacOS itself is based on UNIX system, I expect minimal Linux or UNIX understanding for editing this code. So, if you are unfamiliar with C++ or Python, please study or follow some guides and then come back to this code. I am personally a sophomore student in Computer Science and Engineering Field, so the code here might not be perfect or the code might be a complete nonsense for Pro developers who are working in the field. I have made as much as comments in the code for everyone wanting to modify or edit this code. If you are not sure about what is going on, please contact me via email, edina00@naver.com.


**Suggested Environments**
- **C++** : Xcode IDE 11 Version (any other versions are just fine.  But for 100% compatibility, please consider using 11 version since I have developed this code using that version.
- **Python** : PyCharm or VIM as IDE with Version 3.7.6 (actually IDE does not matter that much. However, please use 3.7.6 Python for better compatibility, 2.x is not supported and 3.8.x might not be supported as well.


**Main Notice here**
- Please DO NOT EVER change or modify the CUESDK.framework which is included in the program. I mean that unless you are 100% familiar with Apple's Dynamic library linking Frameworks, please do not touch anything regarding this one. You may edit CorsairWrapper.cpp if you would like. However, I would not suggest you modifying anything regarding Linking or Building process of this program. Main writer me myself am not 100% why this program is working :b
- You can use some external makefile or build systems such as g++, however the linking process would return you errors about external framework dependency. Please consider building the project using Xcode Archive Export system.
- Please leave any small comments in the code for future developers. It really helps alot.

**How to build your program successfully**
- Please use the Apple Archive system and Distribution system for better and stable purpose.

**Function Documents and Code structures**

I would be uploading function documents and code structures in the link here!
[https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/DocumentsForDevs.md](https://github.com/gooday2die/AllPeripherals/blob/master/MACSupport/DocumentsForDevs.md)


**Again...**
Please feel free to make any contact to me via edina00@naver.com at any time.

## Notice
This is my first time with Xcode environment development. I have done many small projects on Xcode, however this is my first time with Frameworks and all those external dynamic libraries. So, the code might not be perfect. If you happen to find any crashes or bugs, please please let me know. I will be modifying as soon as possible. 

Contacts via email edina00@naver.com

Also, Currently I have checked it working on Xcode environment, however was not able to export this project successfully. I am trying as much as possible. It would take some time. If you know well about Xcode,, please please let me know.  Any help would be appreciated very much!



