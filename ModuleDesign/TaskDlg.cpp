// TaskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "TaskDlg.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "RegModelDlg.h"
#include "RequirementDlg.h"


// CTaskDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskDlg, CDialog)

CTaskDlg::CTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskDlg::IDD, pParent)
{

}

CTaskDlg::~CTaskDlg()
{
}

void CTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, TaskList, m_TaskList);
}


BEGIN_MESSAGE_MAP(CTaskDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, TaskList, &CTaskDlg::OnLvnItemchangedTasklist)
	ON_BN_CLICKED(IDCANCEL, &CTaskDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDSELECT, &CTaskDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDSELECT, &CTaskDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDSEEREQUIRE, &CTaskDlg::OnBnClickedSeerequire)
END_MESSAGE_MAP()


// CTaskDlg ��Ϣ�������


BOOL CTaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	char strtmp[32];
	int indexNo=0;
	//CString sql = "select * from ";
	//ADO m_ado;
	//m_ado.OnInitADOConn();
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_TaskList.InsertColumn(0,"���",LVCFMT_LEFT,40,-1);
	m_TaskList.InsertColumn(1,"��������",LVCFMT_LEFT,80,-1);
	m_TaskList.InsertColumn(2,"��ʼʱ��",LVCFMT_LEFT,80,-1);
	m_TaskList.InsertColumn(3,"����ʱ��",LVCFMT_LEFT,80,-1);
	for(int i=0;i<3;i++){
		sprintf(strtmp,"%d",i+1);
		indexNo = m_TaskList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		m_TaskList.SetItemText(indexNo,1,"000");
		m_TaskList.SetItemText(indexNo,2,_T("111"));
		m_TaskList.SetItemText(indexNo,3,_T("222"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTaskDlg::OnLvnItemchangedTasklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTaskDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnCancel();
	DestroyWindow();
}



void CTaskDlg::OnBnClickedSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int status;
	CRegModelDlg regdlg;
	status = regdlg.DoModal();
	if(status ==0){
		AfxMessageBox(_T("�Ի��򴴽�ʧ��"));
	}
}


void CTaskDlg::OnBnClickedSeerequire()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int status;
	CRequirementDlg reqdlg;
	status = reqdlg.DoModal();
	if(status == 0){
		AfxMessageBox(_T("�Ի��򴴽�ʧ��"));
	}
}


BOOL CTaskDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialog::DestroyWindow();
}


void CTaskDlg::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::PostNcDestroy();
	delete this;
}
