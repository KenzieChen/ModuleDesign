// RequirementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RequirementDlg.h"
#include "afxdialogex.h"


// CRequirementDlg �Ի���

IMPLEMENT_DYNAMIC(CRequirementDlg, CDialog)

CRequirementDlg::CRequirementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRequirementDlg::IDD, pParent)
	, taskRequirement(_T(""))
{

}

CRequirementDlg::~CRequirementDlg()
{
}

void CRequirementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CRequirement);
}


BEGIN_MESSAGE_MAP(CRequirementDlg, CDialog)
END_MESSAGE_MAP()


// CRequirementDlg ��Ϣ�������


BOOL CRequirementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRequirement.SetWindowTextA(taskRequirement);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
