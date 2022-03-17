# Microsoft Developer Studio Project File - Name="MultisimDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MultisimDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultisimDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultisimDemo.mak" CFG="MultisimDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultisimDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MultisimDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultisimDemo - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\Bin/MultisimDemo.exe"

!ELSEIF  "$(CFG)" == "MultisimDemo - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\Bin/MultisimDemoD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MultisimDemo - Win32 Release"
# Name "MultisimDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BPMActTaskShape.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeEditDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\DirDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ETAPDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtListBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtTabModel.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtTabModelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FOHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\FOMatherDotShape.cpp
# End Source File
# Begin Source File

SOURCE=.\FOMatherLineShape.cpp
# End Source File
# Begin Source File

SOURCE=..\ExtSource\FOPGDIPlusHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\ExtSource\FOPGDIPlusProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FOPPropList.cpp
# End Source File
# Begin Source File

SOURCE=.\FOProjectApp.cpp
# End Source File
# Begin Source File

SOURCE=.\FOVertMatherLineShape.cpp
# End Source File
# Begin Source File

SOURCE=.\GWExtBmpListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\HMIBalloonWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\HMIDupSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HMITrsOpenPageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LinePropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MatPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MATRelinkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg6.cpp
# End Source File
# Begin Source File

SOURCE=.\MultisimDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\MultisimDemo.rc
# End Source File
# Begin Source File

SOURCE=.\MultisimDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MultisimDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyBackShape.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCorsssLineShape.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCustomProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\MyExtFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewPort.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectMain.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage0.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\NewVisualProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.cpp
# End Source File
# Begin Source File

SOURCE=.\notepadreFile.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizableDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptFileObj.cpp
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TableBar.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowManager.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkSpaceObj.cpp
# End Source File
# Begin Source File

SOURCE=.\XdgFileObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BPMActTaskShape.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CodeEditDoc.h
# End Source File
# Begin Source File

SOURCE=.\CodeEditView.h
# End Source File
# Begin Source File

SOURCE=.\DirDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ETAPDemoView.h
# End Source File
# Begin Source File

SOURCE=.\ExtListBar.h
# End Source File
# Begin Source File

SOURCE=.\ExtTabModel.h
# End Source File
# Begin Source File

SOURCE=.\ExtTabModelManager.h
# End Source File
# Begin Source File

SOURCE=.\FOHyperLink.h
# End Source File
# Begin Source File

SOURCE=.\FOMatherDotShape.h
# End Source File
# Begin Source File

SOURCE=.\FOMatherLineShape.h
# End Source File
# Begin Source File

SOURCE=.\FOPHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FOPPropList.h
# End Source File
# Begin Source File

SOURCE=.\FOProjectApp.h
# End Source File
# Begin Source File

SOURCE=.\FOVertMatherLineShape.h
# End Source File
# Begin Source File

SOURCE=..\..\FO\Include\GdiplusH.h
# End Source File
# Begin Source File

SOURCE=.\GWExtBmpListBox.h
# End Source File
# Begin Source File

SOURCE=.\HMIBalloonWnd.h
# End Source File
# Begin Source File

SOURCE=.\HMIDupSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\HMITrsOpenPageDlg.h
# End Source File
# Begin Source File

SOURCE=.\LinePropDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\MATRelinkDlg.h
# End Source File
# Begin Source File

SOURCE=.\MBEventEditDlg6.h
# End Source File
# Begin Source File

SOURCE=.\MultisimDemo.h
# End Source File
# Begin Source File

SOURCE=.\MultisimDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\MultisimDemoView.h
# End Source File
# Begin Source File

SOURCE=.\MyBackShape.h
# End Source File
# Begin Source File

SOURCE=.\MyCorsssLineShape.h
# End Source File
# Begin Source File

SOURCE=.\MyCustomProperties.h
# End Source File
# Begin Source File

SOURCE=.\MyExtFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewPort.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectMain.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage0.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage3.h
# End Source File
# Begin Source File

SOURCE=.\NewVisualProxy.h
# End Source File
# Begin Source File

SOURCE=.\NewWizDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewWizPage.h
# End Source File
# Begin Source File

SOURCE=.\notepadreFile.h
# End Source File
# Begin Source File

SOURCE=.\OutputDlg.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\ResizableDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScriptFileObj.h
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TableBar.h
# End Source File
# Begin Source File

SOURCE=.\WindowManager.h
# End Source File
# Begin Source File

SOURCE=.\WorkSpaceObj.h
# End Source File
# Begin Source File

SOURCE=.\XdgFileObj.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap_n.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp283.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00003.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00004.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00005.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00006.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00007.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00008.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00009.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00010.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00011.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00012.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00013.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00014.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00015.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00016.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00017.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00018.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00019.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00020.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00021.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00022.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00023.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00024.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00025.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00026.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00027.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00028.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00029.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00030.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00031.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00032.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00033.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor_1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor_d.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor_g.cur
# End Source File
# Begin Source File

SOURCE=.\res\fo_toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\font_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_mult.ico
# End Source File
# Begin Source File

SOURCE=.\res\link_cur.cur
# End Source File
# Begin Source File

SOURCE=.\res\mather_c.cur
# End Source File
# Begin Source File

SOURCE=.\res\mb_comp_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mb_trs_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mintitle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MultisimDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\MultisimDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MultisimDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\comp130.sid
# End Source File
# Begin Source File

SOURCE=.\res\comp131.sid
# End Source File
# Begin Source File

SOURCE=.\res\comp132.sid
# End Source File
# Begin Source File

SOURCE=.\res\comp133.sid
# End Source File
# Begin Source File

SOURCE=.\res\comp134.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1001.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1002.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1003.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1004.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1005.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1006.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1007.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1008.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1009.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1010.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1011.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1012.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1013.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1014.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1015.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1016.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1017.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1018.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1019.sid
# End Source File
# Begin Source File

SOURCE=.\res\p_1020.sid
# End Source File
# End Target
# End Project
