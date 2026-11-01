Unicode True
!include "MUI2.nsh"
!ifndef VST3_SOURCE
 !error "Pass /DVST3_SOURCE=absolute path to built AfroLogy.vst3 directory"
!endif
OutFile "AfroLogy_Setup_Windows_x64.exe"
Name "AfroLogy"
!define PLUGIN_NAME "AfroLogy"
!define VST3_SUBDIR "VST3"
Name "AfroLogy VST3 0.2.0"
OutFile "AfroLogy_Setup_Windows_x64.exe"
InstallDir "$PROGRAMFILES64\Common Files\VST3"
RequestExecutionLevel admin
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_LANGUAGE "English"
Section "AfroLogy VST3" SecMain
 SetOutPath "$INSTDIR\AfroLogy.vst3"
 File /r "${VST3_SOURCE}\*.*"
 WriteUninstaller "$INSTDIR\AfroLogy_Uninstall.exe"
SectionEnd
Section "Uninstall"
 RMDir /r "$INSTDIR\AfroLogy.vst3"
 Delete "$INSTDIR\AfroLogy_Uninstall.exe"
SectionEnd
