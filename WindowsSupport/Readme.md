## Windows Support
This program is supposed to be ran in WindowsOS. I have some PCs with Windows 10 64 bitinstalled. I have confirmed this program working with the following spec.


Currently Supported SDKS
- Corsair ICUE SDK
- Razer Chroma SDK

Currently Checked Devices
- Corsair K95 Platinum RGB
- Corsair Glaive Pro RGB
- Corsair Void Pro RGB
- Corsair MM800 RGB
- Razer DeathAdder Chroma
- Corsair NightSword RGB (By Christopher Dillard)
- Corsair K57 RGB WIRELESS (By Christopher Dillard)

## Installation Guide
In order to run this program, you should have Python3(I would suggest you using  Python 3.7.x) installed in your PC. Also there are several dependency modules and libraries for this script to work. I would explain those modules and their purposes as well as installation guide. 

 - MSS - for Taking screenshots
 - PIL or PILLOW - for Processing that taken screenshot
 - Numpy - for Clustering Purpose
 - Scipy - for Clustering Purpose

I would be offering a step by step install below. 

 1. Download Python3 from the official [link](https://www.python.org/downloads/) Please please download `3.7.6` or `3.7.7` version. I have not checked any other version working. Please make sure if you are downloading the correct version bit (32bit or 64bit) for your PC. 
 2. After you have installed Python3, please run `cmd` by using `Windows + R` shortcut and entering `cmd` . If you do know how to execute `cmd`, then do it so as you are used to.
 3. Enter `python --version` and verify the version installed. If you happen to have error something like `'python' is not recognized as an internal or external command,
operable program or batch file.`  it means that Python is not correctly installed, or the PATH variables were not set during the installation phase. Please check [https://stackoverflow.com/questions/17953124/python-is-not-recognized-as-an-internal-or-external-command](https://stackoverflow.com/questions/17953124/python-is-not-recognized-as-an-internal-or-external-command) here for more info. Also, if you cannot find solution for this, please let me know. I will help you as much as possible.
 4. Then enter following codes to install our dependency modules. 
 5. `python -m pip install mss`
 6. `python -m pip install pillow`
7. `python -m pip install numpy`
8. `python -m pip install scipy`
9. If you have successfully installed those packages, it would be working soon!
10. Please download the Release zip file below and unzip it in a directory you want. Please check the bit `x64` or `x86` depending on your OS. `x64` is for 64bit machine, and `x86` is for 32bit machine. I have checked both programs working on 64bit PC on Windows 10. I am not 100% sure that `x86` version would work on a real 32bit machine. Please report me if it does or does not through email. 
11. If you unzip the zip file, there would be two directories and two runner files.
- CppSide
- PythonSide
- Rainbow.bat
- ScreenReactive.bat
12. If you do know how to run Python files and Binary executable files through cmd commands, please do it so. Run CppSide first and the run PythonSide main.py.
13. If you do not know how to run those files manually, please doubleclick ScreenReactive.bat and then it would launch Screen Reactive lighting. Rainbow.bat would launch shifting Rainbow color.
14. If the Windows OS asks you for permission of using networks, please allow them in order for C++ side of the program and Python side of the program to communicate.

## Troubleshooting
If you are getting some errors such as `MSCVP140.dll is missing`, please download **Microsoft Visual C++ 2015 Redistributable Update 3** from here https://www.microsoft.com/en-us/download/details.aspx?id=53840 and reboot, and then run the program again. It is due to C++ related program not installed in your PC. (This issue was reported by Daryl Drummond via my email)


## For Devs

**Before you start...**

This Installation guide is for developers who would like to modify or make use of my project for their future projects. The low-level of the program is written in C++ with Visual Studio 2019 IDE and high-level of the program is written in Python.  So, if you are unfamiliar with C++ or Python, please study or follow some guides and then come back to this code. I am personally a sophomore student in Computer Science and Engineering Field, so the code here might not be perfect or the code might be a complete nonsense for Pro developers who are working in the field. I have made as much as comments in the code for everyone wanting to modify or edit this code. If you are not sure about what is going on, please contact me via email, edina00@naver.com.


**Suggested Environments**
- **C++** : Visual Studio 2019 (any other versions are just fine.  But for 100% compatibility, please consider using 2019 version since I have developed this code using that version.
- **Python** : PyCharm or IDLE(default Python IDE) as IDE with Version 3.7.6 (actually IDE does not matter that much. However, please use 3.7.6 Python for better compatibility, 2.x is not supported and 3.8.x might not be supported as well.


## TroubleShooting
Please note that this program is beta version and being heavily developed at the moment! So it might have some unstable issues or minor or major bugs. Please report those issues to me. 

If you cannot manage to face any other issues or have any questions, please contact me via edina00@naver.com. I will provide help as much as possible. Please feel free to contact me! 
