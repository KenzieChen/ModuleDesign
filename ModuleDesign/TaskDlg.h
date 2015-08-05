#pragma once


// CTaskDlg 对话框

class CTaskDlg : public CDialog
{
	DECLARE_DYNAMIC(CTaskDlg)

public:
	CTaskDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskDlg();

// 对话框数据
	enum { IDD = TaskDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_TaskList;
	afx_msg void OnLvnItemchangedTasklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedSeerequire();
	virtual BOOL DestroyWindow();
	
};
