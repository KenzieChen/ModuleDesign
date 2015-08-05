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
       // _bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source = Media.mdb";      //data source后添数据库文件相对路径或绝对路径均可。  
        //_bstr_t strConnect = "Provider=MSDAORA.1;Data Source=ORCL;User ID=CQZ;Password=CQZ";   
		//m_pConnection->Open(strConnect,"","",adModeUnknown);  
		_bstr_t strConnect="Provider=MSDASQL.1;Persist Security Info=False;User ID=cqz;Password=cqz;Data Source=oracle;";
		m_pConnection->Open(strConnect,"","",adModeUnknown);   
		AfxMessageBox(_T("连接成功"));
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
void ADO::CloseConn(void)  
{  
     m_pConnection->Close();  
     ::CoUninitialize();  
}  
UINT ADO::GetRecordCount(_RecordsetPtr pRecordset)  
{  
     int count = 0;  
     try  
     {  
        pRecordset->MoveFirst();  
     }  
     catch(...)  
     {  
        return 0;  
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