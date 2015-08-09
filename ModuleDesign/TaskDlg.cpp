// TaskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "TaskDlg.h"
#include "afxdialogex.h"
#include "RegModelDlg.h"
#include "RequirementDlg.h"
#include "ADO.h"

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
	DDX_Control(pDX, IDSUBMITTASK, CSubmitTask);
}


BEGIN_MESSAGE_MAP(CTaskDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, TaskList, &CTaskDlg::OnLvnItemchangedTasklist)
	ON_BN_CLICKED(IDCANCEL, &CTaskDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDSELECT, &CTaskDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDSELECT, &CTaskDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDSEEREQUIRE, &CTaskDlg::OnBnClickedSeerequire)
	ON_NOTIFY(NM_CLICK, TaskList, &CTaskDlg::OnNMClickTasklist)
	ON_BN_CLICKED(IDSUBMITTASK, &CTaskDlg::OnBnClickedSubmittask)
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
	//partId
	m_TaskList.InsertColumn(7,"",LVCFMT_CENTER,0,-1);
	//模型名称
	m_TaskList.InsertColumn(8,"",LVCFMT_CENTER,0,-1);
	//模型路径
	m_TaskList.InsertColumn(9,"",LVCFMT_CENTER,0,-1);
	//任务id
	m_TaskList.InsertColumn(10,"",LVCFMT_CENTER,0,-1);
	showTaskList();

	//保存模型按钮不可用


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
	if(currSelected == -1){
		MessageBox("请选择一个任务","提示");
		return;
	}

	//获得执行要求，切割字符，提取参数，封装成CMap,传递给regdlg；
	CString requirementStr = (LPCSTR)_bstr_t(m_TaskList.GetItemText(currSelected,6));
	//实例名称和实例编码去掉
	requirementStr.Delete(0,requirementStr.Find(";")+1);
	requirementStr.Delete(0,requirementStr.Find(";")+1);

	CMap<CString,LPCTSTR,CString,LPCTSTR>param_Map;
	
	CString strtmp,left,right;
	int pos=requirementStr.Find(";");
	while(-1 != pos){
		strtmp = requirementStr.Left(pos);
		left = strtmp.Left(strtmp.Find("="));
		right = strtmp.Mid(strtmp.Find("=")+1);

		param_Map.SetAt(left,right);

		requirementStr.Delete(0,pos+1);
		pos = requirementStr.Find(";");
	}
	CString temp;
	int status;
	CRegModelDlg regdlg;

	regdlg.partId = m_TaskList.GetItemText(currSelected,7);
	regdlg.filename = m_TaskList.GetItemText(currSelected,8);
	regdlg.filePath = m_TaskList.GetItemText(currSelected,9);
	regdlg.taskId = m_TaskList.GetItemText(currSelected,10);
	regdlg.param_Map = &param_Map;

	status = regdlg.DoModal();
	if(status == 0){
		AfxMessageBox(_T("对话框创建失败"));
	}
	showTaskList();
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
	CString temp = m_TaskList.GetItemText(currSelected,6);
	temp.Replace(";","\r\n");
	reqdlg.taskRequirement = temp;
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
	m_TaskList.DeleteAllItems();
	char strtmp[32];
	int indexNo=0;
	CString taskName;
	CString startDate;
	CString endDate;
	CString demo;
	CString requirement;
	CString partId; 
	CString status;
	CString filename;
	CString filePath;
	CString taskId;
	CString sql = "select * from variant_task where status = '未完成' or status = '待提交'";
	
	m_ado.OnInitADOConn();
	_RecordsetPtr record = m_ado.OpenRecordset(sql);
	int i=0;
	while(!record->adoEOF){

		taskId.Format(_T("%d"),record->GetCollect("ID").lVal);
		//任务名字
		taskName = (LPCSTR)_bstr_t(record->GetCollect("TASK_NAME"));

		//DATE>COleDateTime>CString
		//开始日期
		startDate = COleDateTime(record->GetCollect("START_DATE").date).Format(_T("%Y-%m-%d"));
		//结束日期
		endDate = COleDateTime(record->GetCollect("END_DATE").date).Format(_T("%Y-%m-%d"));
		//备注
		_variant_t varDemo= record->GetCollect("DEMO");
		if(varDemo.vt ==VT_NULL || varDemo.vt ==VT_EMPTY){
			demo = _T("");
		}else{
			demo = (LPCSTR)_bstr_t(varDemo);
		}
		//变型要求
		requirement = (LPCSTR)_bstr_t(record->GetCollect("REQUIREMENT"));
		//状态
		status =(LPCSTR)_bstr_t(record->GetCollect("STATUS"));
		partId.Format(_T("%d"),record->GetCollect("PART").lVal);

		filename = (LPCSTR)_bstr_t(record->GetCollect("FILENAME"));
		filePath = (LPCSTR)_bstr_t(record->GetCollect("FILE_PATH"));

		sprintf(strtmp,"%d",i+1);
		indexNo = m_TaskList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		m_TaskList.SetItemText(indexNo,1,taskName);
		m_TaskList.SetItemText(indexNo,2,startDate);
		m_TaskList.SetItemText(indexNo,3,endDate);
		m_TaskList.SetItemText(indexNo,4,status);
		m_TaskList.SetItemText(indexNo,5,demo);
		m_TaskList.SetItemText(indexNo,6,requirement);
		m_TaskList.SetItemText(indexNo,7,partId);
		m_TaskList.SetItemText(indexNo,8,filename);
		m_TaskList.SetItemText(indexNo,9,filePath);
		m_TaskList.SetItemText(indexNo,10,taskId);
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
	CString taskstatus = m_TaskList.GetItemText(currSelected,4);
	if(taskstatus.Compare("待提交")==0){
		CSubmitTask.EnableWindow(TRUE);
	}else{
		CSubmitTask.EnableWindow(FALSE);
	}
	*pResult = 0;
}





void CTaskDlg::OnBnClickedSubmittask()
{
	// TODO: 在此添加控件通知处理程序代码
	CString taskId = m_TaskList.GetItemText(currSelected,10);
	CString updateTask = _T("update VARIANT_TASK set STATUS = '已完成' where ID=");
	updateTask += taskId;
	ADO m_ado;
	m_ado.OnInitADOConn();
	m_ado.CmdExecute(updateTask);
	m_ado.CloseRecordset();
	m_ado.CloseConn();
	CSubmitTask.EnableWindow(FALSE);
	showTaskList();
	MessageBox("任务提交完成");
}
