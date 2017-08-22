[Setup]
OutputBaseFilename=KiwiElevatorAgent V3.0
VersionInfoVersion=3.0.0.1
VersionInfoCompany=˫����Ƽ�
VersionInfoDescription=����IC���������
VersionInfoCopyright=˫����Ƽ�,��������Ȩ��
AppCopyright=˫����Ƽ�,��������Ȩ��
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
Filename: {app}\Package\vcredist_x86.exe; WorkingDir: {app}\Package; StatusMsg: ���ڰ�װ���п�.; Flags: runminimized runhidden; Check: VCRCheck

[UninstallRun]

[LangOptions]
LanguageName=Chinese
LanguageID=$0804

[Tasks]
Name: desktopicon; Description: ���������ݷ�ʽ; GroupDescription: ��ӿ�ݷ�ʽ:; Flags: checkedonce

[Icons]
Name: {group}\KiwiElevator; Filename: {app}\ElevatorMgr.exe; WorkingDir: {app}\; IconFilename: {app}\ElevatorMgr.exe; IconIndex: 0
Name: {group}\{cm:UninstallProgram, TestSkin V3.0}; Filename: {uninstallexe}
Name: {userdesktop}\Elvator 3.0; Filename: {app}\ElevatorMgr.exe; Tasks: desktopicon
;Name: {userdesktop}\�����̹��� 3.0; Filename: {app}\AgentMgr.exe; Tasks: desktopicon

;[Languages]  
;Name: "ChineseSimp"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Code]
function VCRCheck(): Boolean;
begin
  Result := not RegKeyExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{710f4c1c-cc18-4c49-8cbf-51240c89a1a2}');
end;