// SaveModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModuleDesign.h"
#include "SaveModelDlg.h"
#include "afxdialogex.h"


// CSaveModelDlg 对话框

IMPLEMENT_DYNAMIC(CSaveModelDlg, CDialog)

CSaveModelDlg::CSaveModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveModelDlg::IDD, pParent)
{

}

CSaveModelDlg::~CSaveModelDlg()
{
}

void CSaveModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveModelDlg, CDialog)
END_MESSAGE_MAP()


// CSaveModelDlg 消息处理程序
