#pragma once
#include "afxcmn.h"


// CRegModelDlg 对话框

class CRegModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegModelDlg)

public:
	CRegModelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegModelDlg();

// 对话框数据
	enum { IDD = RegModelDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ParamList;
	
	ProSolid cur_solid;
	CArray<ProParameter,ProParameter> paramList;
	void ShowParamList(void);
};
