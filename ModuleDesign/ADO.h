#pragma once
class ADO
{
public:
	ADO(void);
	~ADO(void);
	 void OnInitADOConn(void);  
    void CloseRecordset(void);  
    void CloseConn(void);  
    UINT GetRecordCount(_RecordsetPtr pRecordset); 
	_RecordsetPtr& ADO::CmdExecute(CString sql);
	_RecordsetPtr& OpenRecordset(CString sql);  
 public:  
    _ConnectionPtr m_pConnection;  
    _RecordsetPtr m_pRecordset;  
	_CommandPtr m_pCommand;
};

