#pragma once
#include "afxwin.h"


// CRequirementDlg �Ի���

class CRequirementDlg : public CDialog
{
	DECLARE_DYNAMIC(CRequirementDlg)

public:
	CRequirementDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRequirementDlg();

// �Ի�������
	enum { IDD = RequirementDIialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString taskRequirement;
	virtual BOOL OnInitDialog();
	CEdit CRequirement;
};
