Unicode True
!include "MUI2.nsh"
!ifndef VST3_SOURCE
 !error "Pass /DVST3_SOURCE=absolute path to built AFROGRID.vst3 directory"
!endif
Name "AFROGRID VST3 0.2.0"
OutFile "AFROGRID_Setup_Windows_x64.exe"
InstallDir "$PROGRAMFILES64\Common Files\VST3"
RequestExecutionLevel admin
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_LANGUAGE "English"
Section "AFROGRID VST3" SecMain
 SetOutPath "$INSTDIR\AFROGRID.vst3"
 File /r "${VST3_SOURCE}\*.*"
 WriteUninstaller "$INSTDIR\AFROGRID_Uninstall.exe"
SectionEnd
Section "Uninstall"
 RMDir /r "$INSTDIR\AFROGRID.vst3"
 Delete "$INSTDIR\AFROGRID_Uninstall.exe"
SectionEnd
