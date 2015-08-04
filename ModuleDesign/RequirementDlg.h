#pragma once


// CRequirementDlg 对话框

class CRequirementDlg : public CDialog
{
	DECLARE_DYNAMIC(CRequirementDlg)

public:
	CRequirementDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRequirementDlg();

// 对话框数据
	enum { IDD = RequirementDIialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
