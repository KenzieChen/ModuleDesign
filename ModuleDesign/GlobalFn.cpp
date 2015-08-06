#include "StdAfx.h"

ProError UsrActivateCurrentWindow()
{
	int window_id;
	ProError status;
	status = ProWindowCurrentGet(&window_id);
	status = ProWindowActivate(window_id);
	return status;

}

ProMdl GetCurrentMdl(){
	ProMdl mdl;
	ProError status;
	status = ProMdlCurrentGet(&mdl);
	if(status == PRO_TK_NO_ERROR){
		return mdl;
	}
	return NULL;
}

ProError UsrParameterActionFn(ProParameter *Param,ProError status,CArray<ProParameter,ProParameter> * p_pdata)
{
	p_pdata->Add(*Param);
	return(PRO_TK_NO_ERROR);
}

ProError UsrParameterFilterFn(ProParameter *param,ProError status,CArray<ProParameter,ProParameter> *p_pdata)
{
	ProType strtmp =param->type;
	//ProWstringToString(strtmp,param->type);
	return(PRO_TK_NO_ERROR);
	
	//return(PRO_TK_CONTINUE);
}

void UsrGetParaOfSolid(ProSolid solid,CArray<ProParameter,ProParameter> &parmlist)
{
	ProModelitem modelitem;
	ProError status;
	status = ProMdlToModelitem(solid,&modelitem);
	status = ProParameterVisit(&modelitem,(ProParameterFilter)UsrParameterFilterFn,(ProParameterAction)UsrParameterActionFn,(CArray<ProParameter,ProParameter>*) &parmlist);
}