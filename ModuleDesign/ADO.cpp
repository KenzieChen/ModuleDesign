#include "StdAfx.h"
#include "ADO.h"


ADO::ADO(void)
{
}


ADO::~ADO(void)
{
}
void ADO::OnInitADOConn(void)  
{  
   
     ::CoInitialize(NULL);  
     try  
     {  
        m_pConnection.CreateInstance("ADODB.Connection");  
		_bstr_t strConnect="Provider=MSDASQL.1;Persist Security Info=False;User ID=cqz;Password=cqz;Data Source=oracle;";
		m_pConnection->Open(strConnect,"","",adModeUnknown);
     }  
   
     catch(_com_error t)  
     {  
        AfxMessageBox(t.Description());  
     }  
}  
   
   
_RecordsetPtr& ADO::OpenRecordset(CString sql)  
{  
     //TODO: insertreturn statement here  
     ASSERT(!sql.IsEmpty());  
     try  
     {  
         m_pRecordset.CreateInstance(__uuidof(Recordset));  
         m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(),adOpenDynamic, adLockOptimistic, adCmdText);  
     }  
     catch(_com_error t)  
     {  
         AfxMessageBox(t.Description());  
     }  
     return m_pRecordset;  
}  
void ADO::CloseRecordset(void)  
{  
    if(m_pRecordset->GetState() == adStateOpen)  
        m_pRecordset->Close();  
}  

_RecordsetPtr& ADO::CmdExecute(CString sql){
	ASSERT(!sql.IsEmpty());
	try{
		m_pCommand.CreateInstance(__uuidof(Command));
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = _bstr_t(sql);
		m_pRecordset = m_pCommand->Execute(NULL, NULL,adCmdText);
	}
	catch(_com_error t)  
    {  
        AfxMessageBox(t.Description());  
    }  
	return m_pRecordset;  
}

void ADO::CloseConn(void)  
{  
     m_pConnection->Close();  
     ::CoUninitialize();  
}  
//��ȡ��¼����
UINT ADO::GetRecordCount(_RecordsetPtr pRecordset)  
{  
     int count = 0;  
     try  
     {  
        pRecordset->MoveFirst();  
     }  
     catch(_com_error *e)  
     {  
        AfxMessageBox(e->ErrorMessage());  
     }  
       
     if(pRecordset->adoEOF)  
        return 0;  
     while(!pRecordset->adoEOF)   
     {  
        pRecordset->MoveNext();  
        count = count +1;  
     }  
     pRecordset->MoveFirst();  
     return count;  
}  