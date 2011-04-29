# Auto-generated by EclipseNSIS Script Wizard
# 2009/05/01 12:30:48

Name VE

SetCompressor /SOLID lzma

# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 0.1a
!define COMPANY "CS Dept SU"
!define URL www.cs.sun.ac.za

# MUI Symbol Definitions
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install-colorful.ico"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER VE
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall-colorful.ico"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile VESetup.exe
InstallDir $PROGRAMFILES\VE
CRCCheck on
XPStyle on
ShowInstDetails show
VIProductVersion 0.1.0.0
VIAddVersionKey ProductName VE
VIAddVersionKey ProductVersion "${VERSION}"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "${VERSION}"
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
ShowUninstDetails show

# Installer sections
Section "Microsoft Visual C++ 2005 SP1 Redist" SEC0000
    SetOutPath $INSTDIR\redist
    SetOverwrite on
    File C:\Users\TheFreeman\Downloads\vcredist_x86_2005_sp1.exe
    ExecWait '"$INSTDIR\redist\vcredist_x86_2005_sp1.exe" /Q'
    WriteRegStr HKLM "${REGKEY}\Components" "Microsoft Visual C++ 2005 SP1 Redist" 1
SectionEnd

Section "Microsoft Visual C++ 2008 SP1 Redist" SEC0001
    SetOutPath $INSTDIR\redist
    SetOverwrite on
    File C:\Users\TheFreeman\Downloads\vcredist_x86_2008_sp1.exe
    ExecWait '"$INSTDIR\redist\vcredist_x86_2008_sp1.exe" /Q'
    WriteRegStr HKLM "${REGKEY}\Components" "Microsoft Visual C++ 2008 SP1 Redist" 1
SectionEnd

Section DirectX SEC0002
    SetOutPath $INSTDIR\redist
    SetOverwrite on
    File C:\Users\TheFreeman\Downloads\directx_aug2008_redist.exe
    ExecWait '"$INSTDIR\redist\directx_aug2008_redist.exe" /Q /T:"$INSTDIR\redist\DirectX"'
    ExecWait "$INSTDIR\redist\DirectX\dxsetup.exe"
    RmDir /r $INSTDIR\redist\DirectX
    WriteRegStr HKLM "${REGKEY}\Components" DirectX 1
SectionEnd

Section "Nvidia PhysX System Software" SEC0003
    SetOutPath $INSTDIR\redist
    SetOverwrite on
    File C:\Users\TheFreeman\Downloads\PhysX_8.04.25_SystemSoftware.exe
    ExecWait '"$INSTDIR\redist\PhysX_8.04.25_SystemSoftware.exe" /passive'
    WriteRegStr HKLM "${REGKEY}\Components" "Nvidia PhysX System Software" 1
SectionEnd

Section "OpenAL Redistributable" SEC0004
    SetOutPath $INSTDIR\redist
    SetOverwrite on
    File C:\Users\TheFreeman\Downloads\oalinst.exe
    ExecWait '"$INSTDIR\redist\oalinst.exe"'
    WriteRegStr HKLM "${REGKEY}\Components" "OpenAL Redistributable" 1
SectionEnd

!macro CREATE_SMGROUP_SHORTCUT NAME PATH WORK_DIR
    Push "${NAME}"
    Push "${PATH}"
    Push "${WORK_DIR}"
    Call CreateSMGroupShortcut
!macroend

Section "API Documentation" SEC0005
    SetOutPath $INSTDIR\doc
    SetOverwrite on
    File /r ..\Myoushu\doc\*
    #!insertmacro CREATE_SMGROUP_SHORTCUT "API Documentation" $INSTDIR\doc\html\index.html $INSTDIR\doc\html
    WriteRegStr HKLM "${REGKEY}\Components" "API Documentation" 1
SectionEnd

Section -Main SEC0006
    SetOutPath $INSTDIR\redist
    File ..\..\UpdatePath\Release\UpdatePath.exe
    SetOutPath $INSTDIR
    SetOverwrite on
    File /r ..\temp\VE\*
    SetOutPath $INSTDIR\bin\windows
    File "C:\Program Files\NVIDIA Corporation\Cg\bin\cg.dll"
    File "C:\Program Files\NVIDIA Corporation\Cg\bin\cgD3D8.dll"
    File "C:\Program Files\NVIDIA Corporation\Cg\bin\cgD3D9.dll"
    File "C:\Program Files\NVIDIA Corporation\Cg\bin\cgD3D10.dll"
    File "C:\Program Files\NVIDIA Corporation\Cg\bin\cgGL.dll"
    File C:\Windows\System32\OpenAL32.dll
    #!insertmacro CREATE_SMGROUP_SHORTCUT SampleLua $INSTDIR\Samples\Myoushu\SampleLua\bin\windows\SampleLua.exe $INSTDIR\Samples\Myoushu\SampleLua\bin\windows
    ExecWait '"$INSTDIR\redist\UpdatePath.exe" /A "$INSTDIR\bin\windows"' 
    WriteRegStr HKLM "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0007
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    SetOutPath $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk" $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_END
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
!macro DELETE_SMGROUP_SHORTCUT NAME
    Push "${NAME}"
    Call un.DeleteSMGroupShortcut
!macroend

Section /o -un.Main UNSEC0006
    #!insertmacro DELETE_SMGROUP_SHORTCUT SampleLua
    Delete /REBOOTOK $INSTDIR\bin\windows\OpenAL32.dll
    Delete /REBOOTOK $INSTDIR\bin\windows\cgGL.dll
    Delete /REBOOTOK $INSTDIR\bin\windows\cgD3D10.dll
    Delete /REBOOTOK $INSTDIR\bin\windows\cgD3D9.dll
    Delete /REBOOTOK $INSTDIR\bin\windows\cgD3D8.dll
    Delete /REBOOTOK $INSTDIR\bin\windows\cg.dll
    ExecWait '"$INSTDIR\redist\UpdatePath.exe" /R "$INSTDIR\bin\windows"' 
    Delete /REBOOTOK $INSTDIR\redist\UpdatePath.exe
    RmDir /r /REBOOTOK $INSTDIR
    DeleteRegValue HKLM "${REGKEY}\Components" Main
SectionEnd

Section /o "-un.API Documentation" UNSEC0005
    #!insertmacro DELETE_SMGROUP_SHORTCUT "API Documentation"
    RmDir /r /REBOOTOK $INSTDIR\doc
    DeleteRegValue HKLM "${REGKEY}\Components" "API Documentation"
SectionEnd

Section /o "-un.OpenAL Redistributable" UNSEC0004
    Delete /REBOOTOK $INSTDIR\redist\oalinst.exe
    DeleteRegValue HKLM "${REGKEY}\Components" "OpenAL Redistributable"
SectionEnd

Section /o "-un.Nvidia PhysX System Software" UNSEC0003
    Delete /REBOOTOK $INSTDIR\redist\PhysX_8.04.25_SystemSoftware.exe
    DeleteRegValue HKLM "${REGKEY}\Components" "Nvidia PhysX System Software"
SectionEnd

Section /o -un.DirectX UNSEC0002
    Delete /REBOOTOK $INSTDIR\redist\directx_aug2008_redist.exe
    DeleteRegValue HKLM "${REGKEY}\Components" DirectX
SectionEnd

Section /o "-un.Microsoft Visual C++ 2008 SP1 Redist" UNSEC0001
    Delete /REBOOTOK $INSTDIR\redist\vcredist_x86_2008_sp1.exe
    DeleteRegValue HKLM "${REGKEY}\Components" "Microsoft Visual C++ 2008 SP1 Redist"
SectionEnd

Section /o "-un.Microsoft Visual C++ 2005 SP1 Redist" UNSEC0000
    Delete /REBOOTOK $INSTDIR\redist\vcredist_x86_2005_sp1.exe
    DeleteRegValue HKLM "${REGKEY}\Components" "Microsoft Visual C++ 2005 SP1 Redist"
SectionEnd

Section -un.post UNSEC0007
    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
    InitPluginsDir
FunctionEnd

Function CreateSMGroupShortcut
    Exch $R3 ;WORK_DIR
    Exch
    Exch $R0 ;PATH
    Exch
    Exch $R1 ;NAME
    Push $R2
    StrCpy $R2 $StartMenuGroup 1
    StrCmp $R2 ">" no_smgroup
    SetOutPath $R3
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$R1.lnk" $R0
no_smgroup:
    Pop $R2
    Pop $R1
    Pop $R0
    Pop $R3
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION "Microsoft Visual C++ 2005 SP1 Redist" ${UNSEC0000}
    !insertmacro SELECT_UNSECTION "Microsoft Visual C++ 2008 SP1 Redist" ${UNSEC0001}
    !insertmacro SELECT_UNSECTION DirectX ${UNSEC0002}
    !insertmacro SELECT_UNSECTION "Nvidia PhysX System Software" ${UNSEC0003}
    !insertmacro SELECT_UNSECTION "OpenAL Redistributable" ${UNSEC0004}
    !insertmacro SELECT_UNSECTION "API Documentation" ${UNSEC0005}
    !insertmacro SELECT_UNSECTION Main ${UNSEC0006}
FunctionEnd

Function un.DeleteSMGroupShortcut
    Exch $R1 ;NAME
    Push $R2
    StrCpy $R2 $StartMenuGroup 1
    StrCmp $R2 ">" no_smgroup
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$R1.lnk"
no_smgroup:
    Pop $R2
    Pop $R1
FunctionEnd

# Section Descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0000} "The Microsoft Visual C++ 2005 SP1 redistributable install the standard C++ libraries required by the VE."
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0001} "The Microsoft Visual C++ 2008 SP1 redistributable package installs the standard C++ libraries used by the VE. It is required for the VE to function."
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0002} "Install DirectX August 2008. This is required for graphics rendering and input under Windows."
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0003} "Nvidia PhysX is a physics engine. It is required for the VE to function."
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0004} "The OpenAL audio library redistributable package."
!insertmacro MUI_DESCRIPTION_TEXT ${SEC0005} "The API Documentation for developers aiming to use the engine as a library."
!insertmacro MUI_FUNCTION_DESCRIPTION_END
