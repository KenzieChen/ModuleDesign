#pragma once


// CSaveModelDlg 对话框

class CSaveModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveModelDlg)

public:
	CSaveModelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaveModelDlg();

// 对话框数据
	enum { IDD = SaveModelDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
