// RegModelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RegModelDlg.h"
#include "afxdialogex.h"

// CRegModelDlg �Ի���

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
}


BEGIN_MESSAGE_MAP(CRegModelDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRegModelDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CRegModelDlg ��Ϣ�������


BOOL CRegModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 CenterWindow();

	 //CString sql = _T("select * from PART part where part.id=690 union select * from CLASSIFICATION_TREE module where module.id = part.codeclass_id");
	 CString sql = _T("select * from PART part, CLASSIFICATION_TREE module where part.id=690 and module.id = part.class_id");
	 //sql+=_T("and module.ID = part.CLASS_ID");
	 m_ado.OnInitADOConn();
	 _RecordsetPtr record = m_ado.OpenRecordset(sql);
	 CString partName = (LPCSTR)_bstr_t(record->GetCollect("PART_NAME"));
	  CString CODE = (LPCSTR)_bstr_t(record->GetCollect("CODE"));

	m_ado.CloseRecordset();
	m_ado.CloseConn();








	cur_solid = (ProSolid)GetCurrentMdl();
	if(cur_solid == NULL){
		SendMessage(WM_CLOSE);
		return FALSE;
	}
	
	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ParamList.InsertColumn(0,"���",LVCFMT_LEFT,40,-1);
	m_ParamList.InsertColumn(1,"����",LVCFMT_LEFT,80,-1);
	m_ParamList.InsertColumn(2,"����ֵ",LVCFMT_LEFT,80,-1);
	m_ParamList.InsertColumn(3,"Ŀ�����ֵ",LVCFMT_LEFT,80,-1);

	ShowParamList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRegModelDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//strtmp ������
		ProWstringToString(strtmp,paramList[i].id);



		//��ȡ��������ֵ
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
