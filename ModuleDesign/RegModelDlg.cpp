// RegModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RegModelDlg.h"
#include "afxdialogex.h"


// CRegModelDlg 对话框

IMPLEMENT_DYNAMIC(CRegModelDlg, CDialog)

CRegModelDlg::CRegModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegModelDlg::IDD, pParent)
{

}

CRegModelDlg::~CRegModelDlg()
{
}

void CRegModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ParamList);
}


BEGIN_MESSAGE_MAP(CRegModelDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRegModelDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CRegModelDlg 消息处理程序


BOOL CRegModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	 CenterWindow();

	cur_solid = (ProSolid)GetCurrentMdl();
	if(cur_solid == NULL){
		SendMessage(WM_CLOSE);
		return FALSE;
	}
	
	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ParamList.InsertColumn(0,"序号",LVCFMT_LEFT,40,-1);
	m_ParamList.InsertColumn(1,"名称",LVCFMT_LEFT,80,-1);
	m_ParamList.InsertColumn(2,"参数值",LVCFMT_LEFT,80,-1);
	m_ParamList.InsertColumn(3,"目标参数值",LVCFMT_LEFT,80,-1);

	ShowParamList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRegModelDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CRegModelDlg::ShowParamList(void)
{
	char strtmp[32];
	int indexNo =0;
	ProParamvalue proval;
	CString csType;
	CString csValue;

	paramList.RemoveAll();
	m_ParamList.DeleteAllItems();
	UsrGetParaOfSolid(cur_solid,paramList);
	for(int i=0;i<paramList.GetCount();i++){
		sprintf(strtmp,"%d",i+1);
		indexNo = m_ParamList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		ProWstringToString(strtmp,paramList[i].id);
		ProParameterValueGet(&paramList[i],&proval);
		switch(proval.type){
			case PRO_PARAM_DOUBLE:
				csValue.Format("%0f",proval.value.d_val);
				break;
			case PRO_PARAM_STRING:
				csValue = CString(proval.value.s_val);
				break;
			case PRO_PARAM_INTEGER:
				csValue.Format("%0d",proval.value.i_val);
				break;
			case PRO_PARAM_BOOLEAN:
				if(proval.value.l_val==1){csValue="YES";}
				if(proval.value.l_val==0){csValue="NO";}
				break;
			default:
				csValue = "";
				break;
		}
		m_ParamList.SetItemText(indexNo,1,_T(strtmp));
		m_ParamList.SetItemText(indexNo,2,csValue);
		m_ParamList.SetItemText(indexNo,3,"123");
	}

}
