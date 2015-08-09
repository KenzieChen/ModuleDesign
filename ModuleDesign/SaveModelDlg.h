#pragma once
#include "afxwin.h"


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
public:
	CString partId;
	virtual BOOL OnInitDialog();
	CString draft_type_id;
	afx_msg void OnBnClickedSave();

	CString m_DraftName;
	CString m_DraftDesc;
	ProMdl cur_solid;
	afx_msg void OnBnClickedCancel();
	CString filename;
	CString filePath;
	CString taskId;
};
