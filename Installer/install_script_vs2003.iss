;InnoSetupVersion=5.4.3
;ONLY USE THIS IF YOU COMPILED WITH VISUAL STUDIO 2003!!!
#define AppVer GetFileVersion('..\Blocks3D.exe')

[Setup]
AppName=Blocks3D
AppVersion=v{#AppVer}
AppId={{4C5DF268-0208-4CDE-A7F0-65F7E2CB5067}
AppPublisherURL=http://blocks3d.com/
AppSupportURL=http://blocks3d.com/
AppUpdatesURL=http://blocks3d.com/
DefaultDirName={%localappdata}\Blocks3D
OutputBaseFilename=Blocks3D_Setup_v{#AppVer}
Compression=lzma2
PrivilegesRequired=lowest
WizardImageFile=setup.bmp
DefaultGroupName=Blocks3D


[UninstallDelete]
Type: filesandordirs; Name: "{app}"

[Files]
Source: "Redist\msvcp71.dll"; DestDir: "{app}"; Flags: ignoreversion 
Source: "Redist\msvcr71.dll"; DestDir: "{app}"; Flags: ignoreversion 
Source: "..\content\*"; DestDir: "{app}\content"; Flags: ignoreversion recursesubdirs
Source: "..\Blocks3D.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Registry]


[Run]
Filename: "iexplore.exe"; Parameters: "http://www.blocks3d.com/FirstInstall"; Description: Start playing Blocks3D; Flags: shellexec postinstall nowait skipifsilent

[Icons]
Name: "{group}\Play Blocks3D"; Filename: "{%programfiles}\Internet Explorer\iexplore.exe"; Parameters: "http://www.blocks3d.com/Games"; IconFilename: "{app}\Blocks3D.exe"; Tasks: startscut;
Name: "{group}\Blocks3D Editor"; Filename: "{app}\Blocks3D.exe"; Tasks: startscut;

Name: "{userdesktop}\Play Blocks3D"; Filename: "{%programfiles}\Internet Explorer\iexplore.exe"; Parameters: "http://www.blocks3d.com/Games"; IconFilename: "{app}\Blocks3D.exe"; Tasks: startscut;
Name: "{userdesktop}\Blocks3D Editor"; Filename: "{app}\Blocks3D.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Create Desktop Icons";
Name: "startscut"; Description: "Create Start Menu Icons";

