#pragma once


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
};
