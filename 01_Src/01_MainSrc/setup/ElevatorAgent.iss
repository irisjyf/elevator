[Setup]
OutputBaseFilename=KiwiElevatorAgent V3.0
VersionInfoVersion=3.0.0.1
VersionInfoCompany=双人鱼科技
VersionInfoDescription=电梯IC卡管理软件
VersionInfoCopyright=双人鱼科技,保留所有权利
AppCopyright=双人鱼科技,保留所有权利
AppName=KiwiElevator V3.0
AppVerName=KiwiElevator V3.0.0.1
DefaultDirName={pf}\Elevator\KiwiElevator
DefaultGroupName=Elevator\KiwiElevator
OutputDir=Setup     

[Dirs]
Name: {app}\ 

[Files]         
Source: ..\bin\ElevatorMgr.exe; DestDir: {app}\; Flags: ignoreversion  
Source: ..\bin\dzs.mdb; DestDir: {app}\; Flags: ignoreversion 
Source: ..\bin\skinppwtl.dll; DestDir: {app}\; Flags: ignoreversion   
Source: ..\bin\setpara.cfg; DestDir: {app}\; Flags: ignoreversion   
Source: ..\bin\log4cpp.dll; DestDir: {app}\; Flags: ignoreversion  
;Source: ..\bin\AgentMgr.exe; DestDir: {app}\; Flags: ignoreversion  
Source: ..\bin\mfc100d.dll; DestDir: {app}\; Flags: ignoreversion
Source: ..\bin\mfc100ud.dll; DestDir: {app}\; Flags: ignoreversion 
Source: ..\bin\msvcp100d.dll; DestDir: {app}\; Flags: ignoreversion    
Source: ..\bin\msvcr100d.dll; DestDir: {app}\; Flags: ignoreversion     

Source: vcredist_x86.exe; DestDir: {app}\Package  

[Run]
Filename: {app}\Package\vcredist_x86.exe; WorkingDir: {app}\Package; StatusMsg: 正在安装运行库.; Flags: runminimized runhidden; Check: VCRCheck

[UninstallRun]

[LangOptions]
LanguageName=Chinese
LanguageID=$0804

[Tasks]
Name: desktopicon; Description: 创建桌面快捷方式; GroupDescription: 添加快捷方式:; Flags: checkedonce

[Icons]
Name: {group}\KiwiElevator; Filename: {app}\ElevatorMgr.exe; WorkingDir: {app}\; IconFilename: {app}\ElevatorMgr.exe; IconIndex: 0
Name: {group}\{cm:UninstallProgram, TestSkin V3.0}; Filename: {uninstallexe}
Name: {userdesktop}\Elvator 3.0; Filename: {app}\ElevatorMgr.exe; Tasks: desktopicon
;Name: {userdesktop}\代理商管理 3.0; Filename: {app}\AgentMgr.exe; Tasks: desktopicon

;[Languages]  
;Name: "ChineseSimp"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Code]
function VCRCheck(): Boolean;
begin
  Result := not RegKeyExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{710f4c1c-cc18-4c49-8cbf-51240c89a1a2}');
end;