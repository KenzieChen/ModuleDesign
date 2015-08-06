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
	, currSelected(-1)
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
	ON_NOTIFY(NM_CLICK, TaskList, &CTaskDlg::OnNMClickTasklist)
END_MESSAGE_MAP()


// CTaskDlg ��Ϣ�������


BOOL CTaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 CenterWindow();
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_TaskList.InsertColumn(0,"���",LVCFMT_CENTER,40,-1);
	m_TaskList.InsertColumn(1,"��������",LVCFMT_CENTER,160,-1);
	m_TaskList.InsertColumn(2,"��ʼʱ��",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(3,"����ʱ��",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(4,"״̬",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(5,"��ע",LVCFMT_CENTER,160,-1);
	//����Ҫ��
	m_TaskList.InsertColumn(6,"",LVCFMT_CENTER,0,-1);
	//id
	m_TaskList.InsertColumn(7,"",LVCFMT_CENTER,0,-1);
	showTaskList();
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

//�鿴����Ҫ��
void CTaskDlg::OnBnClickedSeerequire()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(currSelected == -1){
		//AfxMessageBox(_T("��ѡ��һ������"));
		MessageBox("��ѡ��һ������","��ʾ");
		return;
	}
	int status;
	CRequirementDlg reqdlg;
	reqdlg.taskRequirement = m_TaskList.GetItemText(currSelected,6);
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


void CTaskDlg::showTaskList(void)
{
	char strtmp[32];
	int indexNo=0;
	CString taskName;
	CString startDate;
	CString endDate;
	CString demo;
	CString requirement;

	CString sql = "select * from variant_task";
	
	m_ado.OnInitADOConn();
	_RecordsetPtr record = m_ado.OpenRecordset(sql);
	int i=0;
	while(!record->adoEOF){
		taskName = (LPCSTR)_bstr_t(record->GetCollect("TASK_NAME"));

		//DATE>COleDateTime>CString
		startDate = COleDateTime(record->GetCollect("START_DATE").date).Format(_T("%Y-%m-%d"));
		endDate = COleDateTime(record->GetCollect("END_DATE").date).Format(_T("%Y-%m-%d"));
		
		_variant_t varDemo= record->GetCollect("DEMO");
		if(varDemo.vt ==VT_NULL || varDemo.vt ==VT_EMPTY){
			demo = _T("");
		}else{
			demo = (LPCSTR)_bstr_t(varDemo);
		}

		requirement = (LPCSTR)_bstr_t(record->GetCollect("REQUIREMENT"));

		sprintf(strtmp,"%d",i+1);
		indexNo = m_TaskList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		m_TaskList.SetItemText(indexNo,1,taskName);
		m_TaskList.SetItemText(indexNo,2,startDate);
		m_TaskList.SetItemText(indexNo,3,endDate);
		m_TaskList.SetItemText(indexNo,4,_T("δ���"));
		m_TaskList.SetItemText(indexNo,5,demo);
		m_TaskList.SetItemText(indexNo,6,requirement);
		i++;
		record->MoveNext();
	}
	m_ado.CloseRecordset();
	m_ado.CloseConn();

}


void CTaskDlg::OnNMClickTasklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_TaskList.GetFirstSelectedItemPosition();
	currSelected = m_TaskList.GetNextSelectedItem(pos);

	*pResult = 0;
}
