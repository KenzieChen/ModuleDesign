// SaveModelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "SaveModelDlg.h"
#include "afxdialogex.h"
#include "ADO.h"



// CSaveModelDlg �Ի���

IMPLEMENT_DYNAMIC(CSaveModelDlg, CDialog)

CSaveModelDlg::CSaveModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveModelDlg::IDD, pParent)
	, partId(_T(""))
{

	draft_type_id = _T("");
	m_DraftName = _T("");
	m_DraftDesc = _T("");
}

CSaveModelDlg::~CSaveModelDlg()
{
}

void CSaveModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDDraftName, m_DraftName);
	DDX_Text(pDX, IDDesc, m_DraftDesc);
}


BEGIN_MESSAGE_MAP(CSaveModelDlg, CDialog)
	ON_BN_CLICKED(IDSAVE, &CSaveModelDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CSaveModelDlg ��Ϣ�������


BOOL CSaveModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSaveModelDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�鿴ģ���Ƿ����
	ProMdl solid = GetCurrentMdl();
	if(solid!=NULL)


	//��ȡ�ı���Ĳ������ж��Ƿ�Ϊ��
	UpdateData(TRUE);
	if(m_DraftName==_T("") ||m_DraftName.IsEmpty()){
		MessageBox("����дģ������","��ʾ");
	}

	//��Ҫ����Ϣ1.�ļ�����id��draft_type_id��(ȫ��) 2.�ļ����ͺ�׺��draft_suffix�� 3.�ĵ���������(type_name)
	// 4.draft_url  �̶���
	// 5.part_id(ȫ��) 6.part_uuid 
	//7.m_DraftName  8.file_name 9.m_DraftDesc
	CString type_name;
	CString draft_suffix;
	CString draft_url;
	CString part_uuid;
	//CString draft_name; ��m_DraftName���棬�ı�ӳ������
	//m_DraftDesc
	CString file_name;

	ADO m_ado;
	m_ado.OnInitADOConn();

	//���Ȳ�ѯ��ģ����Ϣ
	CString getMasterType = "select * from DRAFT_TYPE type where ismaster =1";
	_RecordsetPtr masterTypeRecord = m_ado.OpenRecordset(getMasterType);
	
	draft_type_id.Format("%ld",masterTypeRecord->GetCollect("ID").lVal);
	type_name = (LPCSTR)_bstr_t(masterTypeRecord->GetCollect("TYPE_NAME"));
	draft_suffix = (LPCSTR)_bstr_t(masterTypeRecord->GetCollect("TYPE_SUFFIX")); 
	

	
	//SYSTEMTIME time =0;
	//file_name.Format("%ld",time.wMilliseconds);
	SYSTEMTIME *localtime;
    localtime=new SYSTEMTIME;
    GetLocalTime(localtime);
	file_name.Format("%ld",localtime->wMilliseconds);
	file_name +=_T(".prt");


	//����ļ�����·��
	draft_url = _T("\\uploadPartModel\\");
	draft_url += file_name;

	//�ٲ�ѯ�����uuid
	CString getPartSql = "select * from PART where id =";
	getPartSql += partId;
	_RecordsetPtr partRecord = m_ado.OpenRecordset(getPartSql);
	
	part_uuid = (LPCSTR)_bstr_t(partRecord->GetCollect("UUID"));
	CString insertDraft = "insert into Part_DRAFT(ID,DESCRIPTION,DRAFT_NAME,DRAFT_SUFFIX,DRAFT_URL,FILE_NAME,ISMASTER,TYPE_NAME,DRAFT_TYPE_ID,PART_ID,PART_UUID)values( partdraft_seq.nextval,";
	insertDraft +="'";
	insertDraft +=m_DraftDesc;
	insertDraft +="','";
	insertDraft +=m_DraftName;
	insertDraft +="','";
	insertDraft +=draft_suffix;
	insertDraft +="','";
	insertDraft +=draft_url;
	insertDraft +="','";
	insertDraft +=file_name;
	insertDraft +="',";
	insertDraft +="1";
	insertDraft +=",'";
	insertDraft +=type_name;
	insertDraft +="',";
	insertDraft +=draft_type_id;
	insertDraft +=",";
	insertDraft +=partId;
	insertDraft +=",'";
	insertDraft +=part_uuid;
	insertDraft +="')";
	m_ado.CmdExecute(insertDraft);
	m_ado.CloseRecordset();
	m_ado.CloseConn();
	
	ProName dialg_label;
	ProStringToWstring(dialg_label,"1");
	ProLine filter_string;
	ProStringToWstring(filter_string,"2");
	ProPath path;
	ProStringToWstring(path,"D:\\gnhdata");
	ProName short_cut_name;
	ProStringToWstring(short_cut_name,"3");
	ProFileName fileName;
	ProStringToWstring(short_cut_name,"3.prt");
	ProPath file;

	ProFileSave(dialg_label,filter_string,&path,&short_cut_name,path,fileName,file);
}


