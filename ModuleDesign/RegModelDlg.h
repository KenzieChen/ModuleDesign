#pragma once
#include "afxcmn.h"


// CRegModelDlg �Ի���

class CRegModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegModelDlg)

public:
	CRegModelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegModelDlg();

// �Ի�������
	enum { IDD = RegModelDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ParamList;
	
	ProSolid cur_solid;
	CArray<ProParameter,ProParameter> paramList;
	void ShowParamList(void);
};
