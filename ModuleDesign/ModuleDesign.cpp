// ModuleDesign.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CModuleDesignApp

BEGIN_MESSAGE_MAP(CModuleDesignApp, CWinApp)
END_MESSAGE_MAP()


// CModuleDesignApp ����

CModuleDesignApp::CModuleDesignApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CModuleDesignApp ����

CModuleDesignApp theApp;


// CModuleDesignApp ��ʼ��

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
		AfxMessageBox("�Ի��򴴽�ʧ��");
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
	AfxMessageBox(_T("ģ������"));
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