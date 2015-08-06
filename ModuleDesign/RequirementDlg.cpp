// RequirementDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "RequirementDlg.h"
#include "afxdialogex.h"


// CRequirementDlg 对话框

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


// CRequirementDlg 消息处理程序


BOOL CRequirementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRequirement.SetWindowTextA(taskRequirement);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
