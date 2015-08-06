// TaskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "TaskDlg.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "RegModelDlg.h"
#include "RequirementDlg.h"


// CTaskDlg 对话框

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


// CTaskDlg 消息处理程序


BOOL CTaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	 CenterWindow();
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_TaskList.InsertColumn(0,"序号",LVCFMT_CENTER,40,-1);
	m_TaskList.InsertColumn(1,"任务名称",LVCFMT_CENTER,160,-1);
	m_TaskList.InsertColumn(2,"开始时间",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(3,"结束时间",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(4,"状态",LVCFMT_CENTER,80,-1);
	m_TaskList.InsertColumn(5,"备注",LVCFMT_CENTER,160,-1);
	//任务要求
	m_TaskList.InsertColumn(6,"",LVCFMT_CENTER,0,-1);
	//id
	m_TaskList.InsertColumn(7,"",LVCFMT_CENTER,0,-1);
	showTaskList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTaskDlg::OnLvnItemchangedTasklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CTaskDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnCancel();
	DestroyWindow();
}



void CTaskDlg::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int status;
	CRegModelDlg regdlg;
	status = regdlg.DoModal();
	if(status ==0){
		AfxMessageBox(_T("对话框创建失败"));
	}
}

//查看变型要求
void CTaskDlg::OnBnClickedSeerequire()
{
	// TODO: 在此添加控件通知处理程序代码
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(currSelected == -1){
		//AfxMessageBox(_T("请选择一个任务"));
		MessageBox("请选择一个任务","提示");
		return;
	}
	int status;
	CRequirementDlg reqdlg;
	reqdlg.taskRequirement = m_TaskList.GetItemText(currSelected,6);
	status = reqdlg.DoModal();
	if(status == 0){
		AfxMessageBox(_T("对话框创建失败"));
	}
}


BOOL CTaskDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::DestroyWindow();
}


void CTaskDlg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

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
		m_TaskList.SetItemText(indexNo,4,_T("未完成"));
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
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_TaskList.GetFirstSelectedItemPosition();
	currSelected = m_TaskList.GetNextSelectedItem(pos);

	*pResult = 0;
}
