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


// CTaskDlg 消息处理程序


BOOL CTaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	char strtmp[32];
	int indexNo=0;
	//CString sql = "select * from ";
	//ADO m_ado;
	//m_ado.OnInitADOConn();
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_TaskList.InsertColumn(0,"序号",LVCFMT_LEFT,40,-1);
	m_TaskList.InsertColumn(1,"任务名称",LVCFMT_LEFT,80,-1);
	m_TaskList.InsertColumn(2,"开始时间",LVCFMT_LEFT,80,-1);
	m_TaskList.InsertColumn(3,"结束时间",LVCFMT_LEFT,80,-1);
	for(int i=0;i<3;i++){
		sprintf(strtmp,"%d",i+1);
		indexNo = m_TaskList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		m_TaskList.SetItemText(indexNo,1,"000");
		m_TaskList.SetItemText(indexNo,2,_T("111"));
		m_TaskList.SetItemText(indexNo,3,_T("222"));
	}

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
	CDialog::OnCancel();
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


void CTaskDlg::OnBnClickedSeerequire()
{
	// TODO: 在此添加控件通知处理程序代码
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int status;
	CRequirementDlg reqdlg;
	status = reqdlg.DoModal();
	if(status == 0){
		AfxMessageBox(_T("对话框创建失败"));
	}
	//ADO ado;
	//ado.OnInitADOConn();
	//ado.CloseConn();

}


BOOL CTaskDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//if(){}

	return CDialog::DestroyWindow();
}
