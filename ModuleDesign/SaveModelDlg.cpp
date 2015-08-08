// SaveModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "SaveModelDlg.h"
#include "afxdialogex.h"
#include "ADO.h"



// CSaveModelDlg 对话框

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


// CSaveModelDlg 消息处理程序


BOOL CSaveModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSaveModelDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码

	//查看模型是否存在
	ProMdl solid = GetCurrentMdl();
	if(solid!=NULL)


	//获取文本框的参数，判断是否为空
	UpdateData(TRUE);
	if(m_DraftName==_T("") ||m_DraftName.IsEmpty()){
		MessageBox("请填写模型名称","提示");
	}

	//需要的信息1.文件类型id（draft_type_id）(全局) 2.文件类型后缀（draft_suffix） 3.文档类型名称(type_name)
	// 4.draft_url  固定死
	// 5.part_id(全局) 6.part_uuid 
	//7.m_DraftName  8.file_name 9.m_DraftDesc
	CString type_name;
	CString draft_suffix;
	CString draft_url;
	CString part_uuid;
	//CString draft_name; 用m_DraftName代替，文本映射数据
	//m_DraftDesc
	CString file_name;

	ADO m_ado;
	m_ado.OnInitADOConn();

	//首先查询主模型信息
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


	//获得文件完整路径
	draft_url = _T("\\uploadPartModel\\");
	draft_url += file_name;

	//再查询零件的uuid
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


