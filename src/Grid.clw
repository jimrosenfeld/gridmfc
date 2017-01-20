; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGridView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Grid.h"
LastPage=0

ClassCount=6
Class1=CGridApp
Class2=CGridDoc
Class3=CGridView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME (ORIGINALMENU)
Class5=CAboutDlg
Resource2=IDR_MAINTOOLBAR
Resource3=IDD_ABOUTBOX
Resource4=IDD_CHANGESIZE
Class6=CChangeSize
Resource5=IDR_MAINFRAME

[CLS:CGridApp]
Type=0
HeaderFile=Grid.h
ImplementationFile=Grid.cpp
Filter=N

[CLS:CGridDoc]
Type=0
HeaderFile=GridDoc.h
ImplementationFile=GridDoc.cpp
Filter=N
LastObject=CGridDoc

[CLS:CGridView]
Type=0
HeaderFile=GridView.h
ImplementationFile=GridView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_ACTIONS_COLOR_CUSTOM


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Grid.cpp
ImplementationFile=Grid.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_ACTIONS_GRID
Command2=ID_ACTIONS_RUNNING
Command3=ID_ACTIONS_CHANGESIZE
Command4=ID_ACTIONS_WRAP
CommandCount=4

[MNU:IDR_MAINFRAME (ORIGINALMENU)]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_STATUS_BAR
Command3=ID_ACTIONS_WRAP
Command4=ID_ACTIONS_RUNNING
Command5=ID_ACTIONS_GRID
Command6=ID_ACTIONS_COLOR_RED
Command7=ID_ACTIONS_COLOR_GREEN
Command8=ID_ACTIONS_COLOR_BLUE
Command9=ID_ACTIONS_COLOR_BLACK
Command10=ID_ACTIONS_COLOR_CUSTOM
Command11=ID_ACTIONS_RULESET_RULE1
Command12=ID_ACTIONS_RULESET_RULE2
Command13=ID_ACTIONS_RULESET_RULE3
Command14=ID_ACTIONS_CHANGESIZE
Command15=ID_ACTIONS_RANDOMIZE
Command16=ID_ACTIONS_CLEAR
Command17=ID_APP_ABOUT
CommandCount=17

[TB:IDR_MAINTOOLBAR]
Type=1
Class=?
Command1=ID_ACTIONS_GRID
Command2=ID_ACTIONS_RUNNING
Command3=ID_ACTIONS_WRAP
Command4=ID_ACTIONS_RANDOMIZE
Command5=ID_ACTIONS_CLEAR
Command6=ID_ACTIONS_CHANGESIZE
CommandCount=6

[DLG:IDD_CHANGESIZE]
Type=1
Class=CChangeSize
ControlCount=6
Control1=IDC_EDITBOX_HEIGHT,edit,1350631552
Control2=IDC_EDITBOX_WIDTH,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CChangeSize]
Type=0
HeaderFile=ChangeSize.h
ImplementationFile=ChangeSize.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDITBOX_HEIGHT
VirtualFilter=dWC

