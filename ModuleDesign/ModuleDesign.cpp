// ModuleDesign.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "ModuleDesign.h"

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
void Test1()
{  
	AfxMessageBox(_T("��"));
}  
void Test2()
{  
	AfxMessageBox(_T("����")); 
}  
extern "C" int user_initialize()
{  
	ProError status;  
	ProFileName  MsgFile;
	ProStringToWstring(MsgFile,"IconMessage.txt");  //ע��˴���IconMessage������text�ļ����µ�IconMessage.txt�ļ���������ͬ
	uiCmdCmdId PushButton1_cmd_id,PushButton2_cmd_id; 
	status=ProMenubarMenuAdd("MainMenu","Function","Help",PRO_B_TRUE,MsgFile);  
	ProCmdActionAdd("PushButton1_Act",(uiCmdCmdActFn)Test1,12,AccessDefault,PRO_B_TRUE,PRO_B_TRUE,&PushButton1_cmd_id);
	ProMenubarmenuPushbuttonAdd("MainMenu","PushButton","FirstButton","this button will show a message",NULL,PRO_B_TRUE,PushButton1_cmd_id,MsgFile);
	ProCmdActionAdd("PushButton2_Act",(uiCmdCmdActFn)Test2,uiCmdPrioDefault,AccessDefault,PRO_B_TRUE,PRO_B_TRUE,&PushButton2_cmd_id);
	ProMenubarmenuPushbuttonAdd("MainMenu","PushButton2","SecondButton","this button will show a message",NULL,PRO_B_TRUE,PushButton2_cmd_id,MsgFile);
	return status; 
} 

extern  "C" void user_terminate()
{  
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
}
