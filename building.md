# Building Setup

##### G3D is super delicate, meaning that you have to go about building in a special way

#### Skip to steps 7-13 if you have already built this program

1. Install Visual Studio 2005. [This link here](http://download.microsoft.com/download/8/3/a/83aad8f9-38ba-4503-b3cd-ba28c360c27b/ENU/vcsetup.exe) is a web installer, but it works.

* The above link is for Visual Studio Express, which is faster to download and install. If you'd like to skip some steps, but have a slower download, get [Visual Studio Professional](https://archive.org/details/Microsoft_Visual_Studio_2005_180-Days_Trial) and skip steps 7-11.

2. Download and install G3D from [this link here](https://sourceforge.net/projects/g3d/files/g3d-cpp/6.10/g3d-6_10_win32.exe/download).

3. Make sure G3D is included under your build directories by going under Tools -> Options -> Projects and Solutions -> VC++ Directories and check and see if:

* `g3d-6_10\bin` is under executable files

* `g3d-6_10\include` is under include files

* `g3d-6_10\bin` is under executable files

* `g3d-6_10\win32-vc8-lib` is under library files

* Ex: `C:\libraries\g3d-6_10\bin`

4. Download SDL version 1.2.7 from [this link](http://www.libsdl.org/release/SDL-devel-1.2.7-VC6.zip)

5. Extract the file to a folder on your computer. Keep note of this folder.

6. Include the extracted files by going to Tools -> Options -> Projects and Solutions -> VC++ Directories and adding the following links:

* Include files - extractpath\`include`

* Library files - extractpath\`lib`

* Ex: `C:\libraries\SDL-1.2.7\bin`

#### Steps 7-11 are optional if you are using Visual Studio Professional. Check the Error stuff section if it doesn't work, most reference steps from here.

7. Download and install the [platform SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6510).

8. Put the platform SDK into your directories (Tools -> Options -> Projects and Solutions -> VC++ Directories) by replacing all mentions of $(VCInstallDir)PlatformSDK with the actual path. 
Ex: `$(VCInstallDir)PlatformSDK\include` -> `C:\Program Files\Microsoft Platform SDK\Include`

9. Right click Source files -> Dialogs.rc -> View Code

10. Edit line 10 to say
```cpp
#include "WinResrc.h"
#define IDC_STATIC  -1
```

instead of

```cpp
#include "afxres.h"
```

11. Right click the project -> Properties -> Configuration Properties -> Linker -> Input, and add `AdvAPI32.lib` under Additional Dependencies. 

### Continue back here if you're skipping steps 7-11

12. Right click the project -> Properties -> Configuration Properties -> Linker -> General, and make sure Additional Library Directories is blank.

13. Try building using Build -> Build G3DTest.


## Error stuff

```c:\libraries\g3d-6_10\include\G3D/platform.h(235) : fatal error C1083: Cannot open include file: 'windows.h': No such file or directory``` > Download and install platform SDK (lines 7-8)

```G3D-debug.lib(RegistryUtil.obj) : error LNK2019: unresolved external symbol __imp__RegCloseKey@4 referenced in function "public: static bool __cdecl G3D::RegistryUtil::keyExists(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)" (?keyExists@RegistryUtil@G3D@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z)``` > Add AdvAPI32.lib under Additional Dependencies (step 11)

```.\Dialogs.rc(10) : fatal error RC1015: cannot open include file 'afxres.h'.``` > Perform steps 9-10

Enjoy!

please report unfriendliness of this page
