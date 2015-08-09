#pragma once
#include "ado.h"
#include "afxwin.h"


// CTaskDlg �Ի���

class CTaskDlg : public CDialog
{
	DECLARE_DYNAMIC(CTaskDlg)

public:
	CTaskDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskDlg();

// �Ի�������
	enum { IDD = TaskDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_TaskList;
	afx_msg void OnLvnItemchangedTasklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedSeerequire();
	virtual BOOL DestroyWindow();
	
	virtual void PostNcDestroy();
	void showTaskList(void);
	int currSelected;
	afx_msg void OnNMClickTasklist(NMHDR *pNMHDR, LRESULT *pResult);
	ADO m_ado;
	CButton CSubmitTask;
	afx_msg void OnBnClickedSubmittask();
};
