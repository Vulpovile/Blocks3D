;InnoSetupVersion=5.5.7

[Setup]
AppName=Blocks3D
AppId={{4C5DF268-0208-4CDE-A7F0-65F7E2CB5067}
AppVersion=v0_0_104_3
AppPublisherURL=http://blocks3d.com/
AppSupportURL=http://blocks3d.com/
AppUpdatesURL=http://blocks3d.com/
DefaultDirName={%localappdata}\Blocks3D
OutputBaseFilename=Blocks3D_Setup_{#SetupSetting("AppVersion")}
Compression=lzma2
PrivilegesRequired=lowest
WizardImageFile=setup.bmp

[UninstallDelete]
Type: filesandordirs; Name: "{app}"

[Files]
Source: "Redist\vcredist_x86.exe"; DestDir: "{tmp}"; Flags: ignoreversion 
Source: "Redist\vcredist_x64.exe"; DestDir: "{tmp}"; Check: "IsWin64"; Flags: ignoreversion 
Source: "..\content\*"; DestDir: "{app}\content"; Flags: ignoreversion recursesubdirs
Source: "..\SDL.DLL"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "..\Blocks3D.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Registry]


[Run]
Filename: "{tmp}\vcredist_x86.exe"; Parameters: "/q"; Tasks: instvc; 
Filename: "{tmp}\vcredist_x64.exe"; Parameters: "/q"; Tasks: instvc; Check: "IsWin64";
Filename: "iexplore.exe"; Parameters: "http://www.blocks3d.com/FirstInstall"; Description: Start playing Blocks3D; Flags: shellexec postinstall nowait skipifsilent

[Tasks]
Name: "instvc"; Description: "Install Visual C++ Redistributable 2005 SP1 (Requires elevated permissions)";

