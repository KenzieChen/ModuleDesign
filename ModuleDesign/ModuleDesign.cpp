// ModuleDesign.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "TaskDlg.h"

#include "ProMenubar.h" 
#include "ProMenu.h" 
#include "ProUtil.h" 
#include  <ProToolkit.h> 
#pragma comment(lib,"netapi32")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CModuleDesignApp

BEGIN_MESSAGE_MAP(CModuleDesignApp, CWinApp)
END_MESSAGE_MAP()


// CModuleDesignApp 构造

CModuleDesignApp::CModuleDesignApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CModuleDesignApp 对象

CModuleDesignApp theApp;


// CModuleDesignApp 初始化

BOOL CModuleDesignApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

static uiCmdAccessState AccessDefault(uiCmdAccessMode access_mode)
{  
	return(ACCESS_AVAILABLE);

}

CTaskDlg* taskdlg;

void showCheckTaskForm();

void showRegForm();

extern "C" int user_initialize()
{
	ProError status;  
	ProFileName  MsgFile;
	ProStringToWstring(MsgFile,"Message.txt");

	uiCmdCmdId TaskButton_cmd_id,RegButton_cmd_id; 

	status=ProMenubarMenuAdd("MainMenu","VariantDesign","Help",PRO_B_TRUE,MsgFile);  

	ProCmdActionAdd("TaskButton_Act",(uiCmdCmdActFn)showCheckTaskForm,uiCmdPrioDefault,AccessDefault,PRO_B_TRUE,PRO_B_TRUE,&TaskButton_cmd_id);
	ProMenubarmenuPushbuttonAdd("MainMenu","TaskButton","CheckTask","check the task",NULL,PRO_B_TRUE,TaskButton_cmd_id,MsgFile);

	ProCmdActionAdd("RegButton_Act",(uiCmdCmdActFn)showRegForm,uiCmdPrioDefault,AccessDefault,PRO_B_TRUE,PRO_B_TRUE,&RegButton_cmd_id);
	ProMenubarmenuPushbuttonAdd("MainMenu","RegButton","RegModel","parametic design",NULL,PRO_B_TRUE,RegButton_cmd_id,MsgFile);
	return status; 
} 

extern  "C" void user_terminate()
{  
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if(taskdlg != NULL){
		delete taskdlg;
	}
}


void showCheckTaskForm()
{  
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
/*	int status;
	CTaskDlg dlg;
	status = dlg.DoModal();
	if(status ==0){
		AfxMessageBox("对话框创建失败");
	}
*/

	if(taskdlg == NULL){
		taskdlg = new  CTaskDlg();
		taskdlg->Create(TaskDialog);
		taskdlg->ShowWindow(SW_SHOW);
	}else{
		delete taskdlg;
		taskdlg = new  CTaskDlg();
		taskdlg->Create(TaskDialog);
		taskdlg->ShowWindow(SW_SHOW);
	}

	UsrActivateCurrentWindow();
}  

void showRegForm()
{
	AfxMessageBox(_T("模型再生"));
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(taskdlg == NULL){
		taskdlg = new  CTaskDlg();
		taskdlg->Create(TaskDialog);
		taskdlg->ShowWindow(SW_SHOW);
	}else{
		delete taskdlg;
		taskdlg = new  CTaskDlg();
		taskdlg->Create(TaskDialog);
		taskdlg->ShowWindow(SW_SHOW);
	}

	UsrActivateCurrentWindow();
}