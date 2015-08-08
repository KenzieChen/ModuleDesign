#pragma once
#include "afxwin.h"


// CSaveModelDlg �Ի���

class CSaveModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveModelDlg)

public:
	CSaveModelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveModelDlg();

// �Ի�������
	enum { IDD = SaveModelDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString partId;
	virtual BOOL OnInitDialog();
	CString draft_type_id;
	afx_msg void OnBnClickedSave();

	CString m_DraftName;
	CString m_DraftDesc;
};
