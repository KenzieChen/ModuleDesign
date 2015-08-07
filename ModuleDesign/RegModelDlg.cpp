// RegModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RegModelDlg.h"
#include "afxdialogex.h"
#include "SaveModelDlg.h"

// CRegModelDlg 对话框

IMPLEMENT_DYNAMIC(CRegModelDlg, CDialog)

CRegModelDlg::CRegModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegModelDlg::IDD, pParent)
	, partId(0)
{

}

CRegModelDlg::~CRegModelDlg()
{
}

void CRegModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ParamList);
	DDX_Control(pDX, IDC_EDIT1, CPartName);
	DDX_Control(pDX, IDC_EDIT2, CPARTNUMBER);
	DDX_Control(pDX, IDSAVE, CSaveBtn);
}


BEGIN_MESSAGE_MAP(CRegModelDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRegModelDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDREG, &CRegModelDlg::OnBnClickedReg)
	ON_BN_CLICKED(IDSAVE, &CRegModelDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CRegModelDlg 消息处理程序


BOOL CRegModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	 CenterWindow();

	 CString draftUrl = "D:\\gnhzbdata";
	 CString partIdStr;
	 partIdStr.Format(_T("%ld"),partId);
	// CString sql = _T("select * from PART part, CLASSIFICATION_TREE module,TREE_DRAFT draft where part.id=690 and module.id = part.class_id and draft.tree_id=module.id and draft.ismaster =1");
	 CString sql = _T("select * from PART part, CLASSIFICATION_TREE module,TREE_DRAFT draft where part.id=");
	 sql+=partIdStr;
	 sql+=_T(" and module.id = part.class_id and draft.tree_id=module.id and draft.ismaster =1");
	 m_ado.OnInitADOConn();
	 _RecordsetPtr record = m_ado.OpenRecordset(sql);
	 CString partName = (LPCSTR)_bstr_t(record->GetCollect("PART_NAME"));
	 CString partNumber = (LPCSTR)_bstr_t(record->GetCollect("PART_NUMBER"));
	 _variant_t varUrl = record->GetCollect("DRAFT_URL");
	 //主模型路径为空的情况
	 if(varUrl.vt == VT_NULL || varUrl.vt == VT_EMPTY){
		m_ado.CloseRecordset();
		m_ado.CloseConn();
		SendMessage(WM_CLOSE);
		MessageBox("该零件所属模块尚无主模型，请添加","提示");
		return FALSE;

	 }else{
			draftUrl += (LPCSTR)_bstr_t(varUrl);
	 }

	 ProPath modelPath;
	char* p=(char*)draftUrl.LockBuffer();
	 ProStringToWstring(modelPath,p);
	 ProError status = ProMdlLoad(modelPath,PRO_MDL_PART,PRO_B_FALSE,&cur_solid);

	 ProMdlDisplay(cur_solid);

	 if(cur_solid == NULL){
		SendMessage(WM_CLOSE);
		MessageBox("尚未载入零件模型","提示");
		return FALSE;
	}
	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ParamList.InsertColumn(0,"序号",LVCFMT_CENTER,40,-1);
	m_ParamList.InsertColumn(1,"名称",LVCFMT_CENTER,80,-1);
	m_ParamList.InsertColumn(2,"参数值",LVCFMT_CENTER,80,-1);
	m_ParamList.InsertColumn(3,"目标参数值",LVCFMT_CENTER,80,-1);
	CPartName.SetWindowTextA(partName);
	CPARTNUMBER.SetWindowTextA(partNumber);
	ShowParamList();
	m_ado.CloseRecordset();
	m_ado.CloseConn();

	//保存模型按钮不可用
	CSaveBtn.EnableWindow(FALSE);


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
	CString targParam;

	paramList.RemoveAll();
	m_ParamList.DeleteAllItems();
	UsrGetParaOfSolid(cur_solid,paramList);
	for(int i=0;i<paramList.GetCount();i++){
		sprintf(strtmp,"%d",i+1);
		indexNo = m_ParamList.InsertItem(LVIF_TEXT|LVIF_PARAM,i,strtmp,0,0,0,i);
		//strtmp 参数名
		ProWstringToString(strtmp,paramList[i].id);

		//获取参数变量值
		ProParameterValueGet(&paramList[i],&proval);
		switch(proval.type){
			case PRO_PARAM_DOUBLE:
				csValue.Format("%.2f",proval.value.d_val);
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

		if(param_Map->Lookup(strtmp,targParam)){
			m_ParamList.SetItemText(indexNo,3,targParam);
		}else{
			m_ParamList.SetItemText(indexNo,3,_T(""));
		}
		
	}

}



void CRegModelDlg::OnBnClickedReg()
{
	// TODO: 在此添加控件通知处理程序代码
	//变型之前，将目标参数设置进去。
	ProParamvalue proval;
	ProName paramName;
	char paraNameC[32]="";
	CString paraNameStr;
	//暂存参数数值
	CString strtmp;
	for(int i=0;i<paramList.GetCount();i++){
		//宽字符串变为普通字符串
		ProWstringToString(paraNameC,paramList[i].id);
		//char* 转CString
		paraNameStr.Format(_T("%s"),paraNameC);
		if(param_Map->Lookup(paraNameStr,strtmp)){
			//设置为浮点类型
			proval.type =PRO_PARAM_DOUBLE;
			proval.value.d_val = atof(strtmp);
			ProParameterValueSet(&paramList[i],&proval);
		}else{
			MessageBox("变型失败，源参数与目标参数不一致","提示");
			return;
		}
	}
	
	ProError status = ProSolidRegenerate((ProSolid)cur_solid,PRO_REGEN_NO_FLAGS);
	if(status !=  PRO_TK_NO_ERROR ){
		MessageBox("变型失败，请检查参数","提示");
	}else{
		ShowParamList();
		MessageBox("变型成功！","提示");
		//变型成功后，保存模型按钮可用
		CSaveBtn.EnableWindow(TRUE);
	}

}


void CRegModelDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	int status;
	CSaveModelDlg smDlg;
	status = smDlg.DoModal();
		if(status == 0){
		AfxMessageBox(_T("对话框创建失败"));
	}

}
