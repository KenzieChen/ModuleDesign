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
 public:  
    _ConnectionPtr m_pConnection;  
    _RecordsetPtr m_pRecordset;  
    _RecordsetPtr& OpenRecordset(CString sql);  
};

