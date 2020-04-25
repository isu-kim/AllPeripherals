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
