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
{

}

CRequirementDlg::~CRequirementDlg()
{
}

void CRequirementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRequirementDlg, CDialog)
END_MESSAGE_MAP()


// CRequirementDlg 消息处理程序
