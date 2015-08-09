// RegModelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RegModelDlg.h"
#include "afxdialogex.h"
#include "SaveModelDlg.h"

// CRegModelDlg �Ի���

IMPLEMENT_DYNAMIC(CRegModelDlg, CDialog)

CRegModelDlg::CRegModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegModelDlg::IDD, pParent)
	, filename(_T(""))
	, taskId(_T(""))
{

	partId = _T("");
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


// CRegModelDlg ��Ϣ�������


BOOL CRegModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 CenterWindow();

	 CString draftUrl = "D:\\gnhzbdata";
	 draftUrl += filePath;
	 //������Ҫ��ѯ��ģ�͵�url
	 //CString sql = _T("select * from PART part, CLASSIFICATION_TREE module,TREE_DRAFT draft where part.id=");
	// sql+=partId;
	// sql+=_T(" and module.id = part.class_id and draft.tree_id=module.id and draft.ismaster =1");

	 CString sql = _T("select * from PART where id=");
	 sql+=partId;
	 m_ado.OnInitADOConn();
	 _RecordsetPtr record = m_ado.OpenRecordset(sql);
	 CString partName = (LPCSTR)_bstr_t(record->GetCollect("PART_NAME"));
	 CString partNumber = (LPCSTR)_bstr_t(record->GetCollect("PART_NUMBER"));
	/* _variant_t varUrl = record->GetCollect("DRAFT_URL");
	 //��ģ��·��Ϊ�յ����
	 if(varUrl.vt == VT_NULL || varUrl.vt == VT_EMPTY){
		m_ado.CloseRecordset();
		m_ado.CloseConn();
		SendMessage(WM_CLOSE);
		MessageBox("���������ģ��������ģ�ͣ������","��ʾ");
		return FALSE;

	 }else{
			draftUrl += (LPCSTR)_bstr_t(varUrl);
	 }
	 */

	ProPath modelPath;
	char* p=(char*)draftUrl.LockBuffer();
	 ProStringToWstring(modelPath,p);
	 ProError status = ProMdlLoad(modelPath,PRO_MDL_PART,PRO_B_FALSE,&cur_solid);

	 ProMdlDisplay(cur_solid);

	 if(cur_solid == NULL){
		SendMessage(WM_CLOSE);
		MessageBox("��δ�������ģ��","��ʾ");
		return FALSE;
	}
	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ParamList.InsertColumn(0,"���",LVCFMT_CENTER,40,-1);
	m_ParamList.InsertColumn(1,"����",LVCFMT_CENTER,80,-1);
	m_ParamList.InsertColumn(2,"����ֵ",LVCFMT_CENTER,80,-1);
	m_ParamList.InsertColumn(3,"Ŀ�����ֵ",LVCFMT_CENTER,80,-1);
	CPartName.SetWindowTextA(partName);
	CPARTNUMBER.SetWindowTextA(partNumber);
	ShowParamList();
	m_ado.CloseRecordset();
	m_ado.CloseConn();

	//����ģ�Ͱ�ť������
	CSaveBtn.EnableWindow(FALSE);


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



void CRegModelDlg::OnBnClickedReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����֮ǰ����Ŀ��������ý�ȥ��
	ProParamvalue proval;
	ProName paramName;
	char paraNameC[32]="";
	CString paraNameStr;
	//�ݴ������ֵ
	CString strtmp;
	for(int i=0;i<paramList.GetCount();i++){
		//���ַ�����Ϊ��ͨ�ַ���
		ProWstringToString(paraNameC,paramList[i].id);
		//char* תCString
		paraNameStr.Format(_T("%s"),paraNameC);
		if(param_Map->Lookup(paraNameStr,strtmp)){
			//����Ϊ��������
			proval.type =PRO_PARAM_DOUBLE;
			proval.value.d_val = atof(strtmp);
			ProParameterValueSet(&paramList[i],&proval);
		}else{
			MessageBox("����ʧ�ܣ�Դ������Ŀ�������һ��","��ʾ");
			return;
		}
	}
	
	ProError status = ProSolidRegenerate((ProSolid)cur_solid,PRO_REGEN_NO_FLAGS);
	if(status !=  PRO_TK_NO_ERROR ){
		MessageBox("����ʧ�ܣ��������","��ʾ");
	}else{
		ShowParamList();
		MessageBox("���ͳɹ���","��ʾ");
		//���ͳɹ��󣬱���ģ�Ͱ�ť����
		CSaveBtn.EnableWindow(TRUE);
	}

}

void CRegModelDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int status;
	CSaveModelDlg smDlg;

	smDlg.partId = partId;
	smDlg.cur_solid =cur_solid;
	smDlg.filename = filename;
	smDlg.filePath = filePath;
	smDlg.taskId = taskId;
	status = smDlg.DoModal();
		if(status == 0){
		AfxMessageBox(_T("�Ի��򴴽�ʧ��"));
	}

}
