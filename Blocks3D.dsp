# Microsoft Developer Studio Project File - Name="Blocks3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Blocks3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Blocks3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Blocks3D.mak" CFG="Blocks3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Blocks3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Blocks3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Blocks3D - Win32 Release"
# Name "Blocks3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DataModelV2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\source\DataModelV2\BaseButtonInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\BaseGuiInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\DataModelInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\GroupInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\GuiRootInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\ImageButtonInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\Instance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\LevelInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\LightingInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\PartInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\PVInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\SelectionService.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\SoundInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\SoundService.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\TextButtonInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\ToggleImageButtonInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\DataModelV2\WorkspaceInstance.cpp
# End Source File
# End Group
# Begin Group "Listener"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\source\Listener\ButtonListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\CameraButtonListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\DeleteListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\GUDButtonListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\MenuButtonListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\ModeSelectionListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\RotateButtonListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Listener\ToolbarListener.cpp
# End Source File
# End Group
# Begin Group "Tool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\source\Tool\ArrowTool.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Tool\DraggerTool.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Tool\SurfaceTool.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Tool\Tool.cpp
# End Source File
# End Group
# Begin Group "Reflection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\source\Reflection\ReflectionDataTable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\source\Reflection\ReflectionProperty.cpp
# End Source File
# End Group
# Begin Group "XplicitNgine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\source\XplicitNgine\XplicitNgine.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\source\Application.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\AudioPlayer.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\ax.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\base64.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\BrowserCallHandler.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\CameraController.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\ErrorFunctions.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\Globals.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\IEBrowser.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\IEDispatcher.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\main.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\Mouse.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\propertyGrid.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\PropertyWindow.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\Renderer.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\StringFunctions.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\TextureHandler.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\source\WindowFunctions.cpp

!IF  "$(CFG)" == "Blocks3D - Win32 Release"

# ADD CPP /I ".\src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ELSEIF  "$(CFG)" == "Blocks3D - Win32 Debug"

# ADD CPP /I "src\include" /D "NO_SDL_MAIN"
# SUBTRACT CPP /X

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "DataModelV2_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\DataModelV2\BaseButtonInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\BaseGuiInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\DataModelInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\GroupInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\GuiRootInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\ImageButtonInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\Instance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\LevelInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\LightingInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\PartInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\PVInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\SelectionService.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\SoundInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\SoundService.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\TextButtonInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\ThumbnailGeneratorInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\ToggleImageButtonInstance.h
# End Source File
# Begin Source File

SOURCE=.\src\include\DataModelV2\WorkspaceInstance.h
# End Source File
# End Group
# Begin Group "Listener_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\Listener\ButtonListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\CameraButtonListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\DeleteListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\GUDButtonListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\MenuButtonListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\ModeSelectionListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\RotateButtonListener.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Listener\ToolbarListener.h
# End Source File
# End Group
# Begin Group "Tool_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\Tool\ArrowTool.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Tool\DraggerTool.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Tool\SurfaceTool.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Tool\Tool.h
# End Source File
# End Group
# Begin Group "Reflection_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\Reflection\Reflection.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Reflection\ReflectionDataTable.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Reflection\ReflectionProperty.h
# End Source File
# End Group
# Begin Group "XplicitNgine_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\XplicitNgine\XplicitNgine.h
# End Source File
# End Group
# Begin Group "rapidxml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\include\rapidxml\rapidxml.hpp
# End Source File
# Begin Source File

SOURCE=.\src\include\rapidxml\rapidxml_iterators.hpp
# End Source File
# Begin Source File

SOURCE=.\src\include\rapidxml\rapidxml_print.hpp
# End Source File
# Begin Source File

SOURCE=.\src\include\rapidxml\rapidxml_utils.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\include\Application.h
# End Source File
# Begin Source File

SOURCE=.\src\include\AudioPlayer.h
# End Source File
# Begin Source File

SOURCE=.\src\include\ax.h
# End Source File
# Begin Source File

SOURCE=.\src\include\base64.h
# End Source File
# Begin Source File

SOURCE=.\src\include\BrowserCallHandler.h
# End Source File
# Begin Source File

SOURCE=.\src\include\CameraController.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Enum.h
# End Source File
# Begin Source File

SOURCE=.\src\include\ErrorFunctions.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Faces.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Globals.h
# End Source File
# Begin Source File

SOURCE=.\src\include\IEBrowser.h
# End Source File
# Begin Source File

SOURCE=.\src\include\IEDispatcher.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\src\include\propertyGrid.h
# End Source File
# Begin Source File

SOURCE=.\src\include\PropertyWindow.h
# End Source File
# Begin Source File

SOURCE=.\src\include\Renderer.h
# End Source File
# Begin Source File

SOURCE=.\src\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\src\include\StringFunctions.h
# End Source File
# Begin Source File

SOURCE=.\src\include\TextureHandler.h
# End Source File
# Begin Source File

SOURCE=.\src\include\ToolEnum.h
# End Source File
# Begin Source File

SOURCE=.\src\include\versioning.h
# End Source File
# Begin Source File

SOURCE=.\src\include\VS2005CompatShim.h
# End Source File
# Begin Source File

SOURCE=.\src\include\win32Defines.h
# End Source File
# Begin Source File

SOURCE=.\src\include\WindowFunctions.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
