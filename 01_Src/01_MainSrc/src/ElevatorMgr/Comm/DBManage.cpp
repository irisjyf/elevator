#include "stdafx.h"
#include "DBManage.h"
#include "Loginset.h"
#include "AgentIDRecord.h"
#include "OffsetRecord.h"
#include "..\ElevatorMgr.h"
extern CDatabase db;

CDBManage::CDBManage(void)
{
	m_mapLoginset.RemoveAll();
	m_mapCustermer.RemoveAll();
}

CDBManage::~CDBManage(void)
{
	CLoginset *pLoginset = NULL;
	CString  strTemp;
	POSITION pos = m_mapLoginset.GetStartPosition();
	while(pos)
	{
		m_mapLoginset.GetNextAssoc(pos,strTemp,pLoginset);
		ASSERT(pLoginset);

		delete pLoginset;
		pLoginset  = NULL;
	}
	m_mapLoginset.RemoveAll();

	long lCode = 0; 
	CYonghuset *pYonghuset = NULL;
	pos = m_mapCustermer.GetStartPosition();
	while(pos)
	{
		m_mapCustermer.GetNextAssoc(pos,lCode,pYonghuset);
		ASSERT(pYonghuset);

		delete pYonghuset;
		pYonghuset  = NULL;
	}
	m_mapCustermer.RemoveAll();

	CSuoset *pSuoset = NULL;
	pos = m_mapElevator.GetStartPosition();
	while(pos)
	{
		m_mapElevator.GetNextAssoc(pos,lCode,pSuoset);
		ASSERT(pSuoset);

		delete pSuoset;
		pSuoset  = NULL;
	}
	m_mapElevator.RemoveAll();

	CMakeCardSet *pMakeCard = NULL;
	pos = m_mapMakeCard.GetStartPosition();
	CString strKey;
	while(pos)
	{
		m_mapMakeCard.GetNextAssoc(pos, strKey, pMakeCard );
		ASSERT(pMakeCard);
		delete pMakeCard;
		pMakeCard = NULL;
	}
	m_mapMakeCard.RemoveAll();
}

CDBManage *      CDBManage::GetDBManage()
{
	return &theApp.m_DBManage;
}

// ������
BOOL CDBManage::OpenDB()
{
	try
	{
		TCHAR szFilePath[MAX_PATH + 1]={0};
		GetModuleFileName(NULL, szFilePath, MAX_PATH);

		CString strTemp,strTemp2;
		strTemp.Format("%s",szFilePath);
		int iPos = strTemp.ReverseFind(_T('\\'));
		strTemp = strTemp.Left(iPos);
		strTemp2.Format(_T("%s\\dzs.mdb"),strTemp);
		
		char szDesc[256]={0};
		sprintf(szDesc,"DSN=dzs;PWD=fingerlock;Description=dzs Data Source;DBQ=%s",strTemp2); 
		int nFlag=SQLConfigDataSource(/*m_hWnd*/NULL,
			ODBC_ADD_DSN,
			"Microsoft Access Driver (*.mdb)",
			(LPTSTR)szDesc);

		BOOL bRet = db.Open("dzs",FALSE,FALSE,"ODBC;PWD=fingerlock");
		if(bRet)
			return TRUE;
	}
	catch (...)
	{
		CString str="dzs";
		char strDir[150]={0};
		int nLen=GetCurrentDirectory(150,strDir);
		strcat(strDir,"\\dzs.mdb");
		char szDesc[256]={0};
		sprintf(szDesc,"DSN=dzs;PWD=fingerlock;Description=dzs Data Source;DBQ=%s",strDir); 
		int nFlag=SQLConfigDataSource(/*m_hWnd*/NULL,
			ODBC_ADD_DSN,
			"Microsoft Access Driver (*.mdb)",
			(LPTSTR)szDesc);
		if(nFlag)
			db.Open("dzs.mdb",FALSE,FALSE,"ODBC;PWD=fingerlock");
		else
		{
			AfxMessageBox("����Դ����ʧ��!",MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}

// ��½
BOOL CDBManage::Login(CString strUser, CString strPsw)
{
	CLoginset lset(&db);

	CString strSQL;
	strSQL.Format("select * from ��¼���� where �û���='%s' AND ����='%s'",strUser,strPsw);
	lset.Open(1,strSQL);
	while (!lset.IsEOF())
	{
		m_USERINFO.m_strUser  = lset.m_column1;
		m_USERINFO.m_strPsw   = lset.m_column2;
		m_USERINFO.m_strAuth  = lset.m_column3;
		return TRUE;
	}

	AfxMessageBox("��¼ʧ�ܣ�����������!",MB_OK);
	return FALSE;
}
CString CDBManage::GetCurrentUser()
{
	return m_USERINFO.m_strUser;
}
// ���ӡ��޸��û�
BOOL CDBManage::OPerUser(CString strUser, CString strPsw, CString strPsw2,CString strAuth,CString strOldPsw)
{
    CString strSQL;
    CLoginset lset(&db);

	// �ж��������Ƿ���ȷ�����޸�����ʱʹ��
	if (!strOldPsw.IsEmpty())
	{
		BOOL  bHave = FALSE;
		strSQL.Format("select * from ��¼���� where �û���='%s' AND ����='%s'",strUser,strOldPsw);
		lset.Open(1,strSQL);
		while (!lset.IsEOF())
		{
			bHave  = TRUE;
			break;
		}

		if (!bHave)
		{
			AfxMessageBox("�����벻��ȷ������������!",MB_OK);
			return FALSE;
		}

		// �����µ��û���¼
		strSQL.Format("update ��¼���� set ���� = \'%s\', Ȩ�� = \'%s\' where �û���=\'%s\'" ,strPsw,strAuth,strUser);
		db.ExecuteSQL(strSQL);
		return TRUE;
	}

	//// �жϸ��û��Ƿ����
	//strSQL.Format("select * from ��¼���� where �û���='%s'",strUser);
	//CLoginset lset2(&db);
	//lset2.Open(1,strSQL);
	//while (!lset2.IsEOF())
	//{
	//	AfxMessageBox("���û��Ѿ����ڣ�����������!",MB_OK);
	//	return FALSE;
	//}

	//// �����µ��û���¼
	//strSQL.Format("insert into ��¼����(�û���,����,Ȩ��) values(\'%s\',\'%s\',\'%s\')",strUser,strPsw,strAuth);
	//db.ExecuteSQL(strSQL);

	return TRUE;
}

BOOL CDBManage::AddUser(CString strUser, CString strPsw, CString strAuth)
{
	CString strSQL;
	CLoginset lset(&db);

	// �жϸ��û��Ƿ����
	strSQL.Format("select * from ��¼���� where �û���='%s'",strUser);
	CLoginset lset2(&db);
	lset2.Open(1,strSQL);
	while (!lset2.IsEOF())
	{
		AfxMessageBox("���û��Ѿ����ڣ�����������!",MB_OK);
		return FALSE;
	}

	// �����µ��û���¼
	strSQL.Format("insert into ��¼����(�û���,����,Ȩ��) values(\'%s\',\'%s\',\'%s\')",strUser,strPsw,strAuth);
	db.ExecuteSQL(strSQL);

	return TRUE;
}
// ��ȡ�û��б�
void CDBManage::GetUserList()
{
	CLoginset lset(&db);
	CString strSQL;

	strSQL.Format("select * from ��¼����");
	lset.Open(1,strSQL);
	while (!lset.IsEOF())
	{
		CString strName = lset.m_column1;
		strName.MakeUpper();

		CLoginset *pLoginset = NULL;  
		if (m_mapLoginset.Lookup(strName,pLoginset))
		{
			pLoginset->SetLoginset(&lset);
		}
		else
		{
			pLoginset  = new  CLoginset;
			pLoginset->SetLoginset(&lset);
			m_mapLoginset.SetAt(strName,pLoginset);
		}

		lset.MoveNext();
	}

	lset.Close();
}

// ɾ���û�
BOOL  CDBManage::DelUser(CString strUser)
{
	strUser.MakeUpper();
	CLoginset *pLoginset = NULL;  
	if (m_mapLoginset.Lookup(strUser,pLoginset))
	{
		m_mapLoginset.RemoveKey(strUser);

		if (NULL != pLoginset)
		{
			delete pLoginset;
			pLoginset = NULL;
		}

		CLoginset lset(&db);
		CString strSQL;

		// �жϸ��û��Ƿ����
		strSQL.Format("delete from ��¼���� where �û���='%s'",strUser);
	    db.ExecuteSQL(strSQL);
	}

	return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------------//
// ��ȡ�û��б�
void CDBManage::GetCustermerList(CArray<CYonghuset*,CYonghuset*> &arr)
{
	CYonghuset yset(&db);
	//CString 
	CString sql;
	sql.Format("select * from ҵ������Ϣ order by ��� DESC");
	yset.Open(1,sql);

	int i=0;
	while(!yset.IsEOF())
	{
		long iCode = yset.m_yzkh;
		CYonghuset *pYonghuset = NULL;  
		if (m_mapCustermer.Lookup(iCode,pYonghuset))
		{
			pYonghuset->SetYonghuset(&yset);
		}
		else
		{
			pYonghuset  = new  CYonghuset;
			pYonghuset->SetYonghuset(&yset);
			m_mapCustermer.SetAt(iCode,pYonghuset);
		}

		pYonghuset->m_bSave  = TRUE;

		arr.Add(pYonghuset);

		yset.MoveNext();
	}
	yset.Close();
}

// �ͻ���Ϣ��ѯ
BOOL CDBManage::QurryCustomer(CString strField,CString strKey,CArray<CYonghuset*,CYonghuset*> &arr)
{
	if (strField.IsEmpty()&&strKey.IsEmpty())
	{
		AfxMessageBox("��ϢΪ�գ�����������!",MB_OK);
		return FALSE;
	}

	CString sql,strTemp;
	strKey = "%"+strKey+"%";
	sql.Format("select * from ҵ������Ϣ where %s LIKE '%s' ",strField,strKey);

	CYonghuset yset(&db);
	yset.Open(1,sql);

	int i=0;
	while(!yset.IsEOF())
	{
		long lCode = yset.m_yzkh;

		CYonghuset *pYonghuset = NULL;  
		if (m_mapCustermer.Lookup(lCode,pYonghuset))
		{
			arr.Add(pYonghuset);
		}

		yset.MoveNext();
	}
	yset.Close();

	return TRUE;
}

long CDBManage::GetCustermerID()
{
	CString sql;
	sql.Format("select * from ҵ������Ϣ order by  ��� desc");

	CYonghuset yset(&db);
	yset.Open(1,sql);
	long iCode = 1;
	while(!yset.IsEOF())
	{
		 iCode = yset.m_yzkh + 1;
		 break;
	}
	yset.Close();

	return iCode;
}

CYonghuset* CDBManage::GetCustermerByID(long lID, long& lStatus)
{
	CYonghuset* pYonghuset = NULL; 
	if (m_mapCustermer.Lookup(lID,pYonghuset))
	{
		lStatus = MOD_TYPE;
	}
	else
	{
		pYonghuset  = new  CYonghuset;
		pYonghuset->m_ID   = lID ;
		pYonghuset->m_yzkh   = lID ;
		pYonghuset->m_bSave  = FALSE;
		m_mapCustermer.SetAt(lID,pYonghuset);
		lStatus = ADD_TYPE;
	} 
	return pYonghuset;
}

BOOL CDBManage::OpereCustomer(CYonghuset* pYonghuset,char cOperType)
{
    CString sql;

	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into ҵ������Ϣ(���, ҵ������,�ֻ�����,SN,������,ҵ������,����,����ģʽ,ʹ�ô���,��ʼ����,��������,���õ���һ,����һ���ò�,����һ���ò�����,���õ��ݶ�,���ݶ����ò�,���ݶ����ò�����,���õ�����,���������ò�,���������ò�����,���õ�����,�����Ŀ��ò�,�����Ŀ��ò�����,��״̬,������ʽ,����������) values (%d,\'%s\',\'%s\',\'%s\',%d,\'%s\',%d,%d,%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,%d,%d)",
			pYonghuset->m_ID,
			pYonghuset->m_yzmc,
			pYonghuset->m_sjhm,
			pYonghuset->m_sn,
			pYonghuset->m_fjbh,
			pYonghuset->m_yzmp,
			pYonghuset->m_yzkh,
			pYonghuset->m_xzms,
			pYonghuset->m_sycs,
			pYonghuset->m_qssj,
			pYonghuset->m_jzsj,
			pYonghuset->m_kydt1,
			pYonghuset->m_dtkyc1,
			pYonghuset->m_dtkycxz1,
			pYonghuset->m_kydt2,
			pYonghuset->m_dtkyc2,
			pYonghuset->m_dtkycxz2,
			pYonghuset->m_kydt3,
			pYonghuset->m_dtkyc3,
			pYonghuset->m_dtkycxz3,
			pYonghuset->m_kydt4,
			pYonghuset->m_dtkyc4,
			pYonghuset->m_dtkycxz4,
			pYonghuset->m_status,
			pYonghuset->m_czfs,
			pYonghuset->m_hmdcs);
	}
	else if (cOperType == MOD_TYPE)
	{
		sql.Format("update ҵ������Ϣ set ҵ������=\'%s\',�ֻ�����=\'%s\',SN=\'%s\',������=%d,ҵ������=\'%s\',����ģʽ=%d ,ʹ�ô���=%d ,��ʼ����=\'%s\' ,��������=\'%s\' ,���õ���һ=%d ,����һ���ò�=\'%s\' ,����һ���ò�����=\'%s\',���õ��ݶ�=%d ,���ݶ����ò�=\'%s\',���ݶ����ò�����=\'%s\' ,���õ�����=%d ,���������ò�=\'%s\',���������ò�����=\'%s\',���õ�����=%d ,�����Ŀ��ò�=\'%s\',�����Ŀ��ò�����=\'%s\'  ,��״̬=%d ,������ʽ=%d ,����������=%d where  ����=%d",
			pYonghuset->m_yzmc,
			pYonghuset->m_sjhm,
			pYonghuset->m_sn,
			pYonghuset->m_fjbh,
			pYonghuset->m_yzmp,
			pYonghuset->m_xzms,
			pYonghuset->m_sycs,
			pYonghuset->m_qssj,
			pYonghuset->m_jzsj,
			pYonghuset->m_kydt1,
			pYonghuset->m_dtkyc1,
			pYonghuset->m_dtkycxz1,
			pYonghuset->m_kydt2,
			pYonghuset->m_dtkyc2,
			pYonghuset->m_dtkycxz2,
			pYonghuset->m_kydt3,
			pYonghuset->m_dtkyc3,
			pYonghuset->m_dtkycxz3,
			pYonghuset->m_kydt4,
			pYonghuset->m_dtkyc4,
			pYonghuset->m_dtkycxz4,
			pYonghuset->m_status,
			pYonghuset->m_czfs,
			pYonghuset->m_hmdcs,
			pYonghuset->m_yzkh);
	}
	else  if (cOperType == DEL_TYPE)
	{
		long lID = pYonghuset->m_yzkh;
		delete pYonghuset;
		pYonghuset  = NULL;
		m_mapCustermer.RemoveKey(lID);

		sql.Format("delete from ҵ������Ϣ where ����=%d",lID);
	}
	else
	{
		return FALSE;
	}
   
    try
    {
 		db.ExecuteSQL(sql);
    }
	catch (...)
	{
		DWORD dwErr = GetLastError();
		return FALSE;
	}
  

	if (cOperType == ADD_TYPE)
	{
		pYonghuset->m_bSave  = TRUE;
	}

	return TRUE;
}

//-----------------------------------����Ա����----------------------------------------------------------------------------------------//
BOOL  CDBManage::QurryManager(CString strField,CString strKey,CArray<Cquset*,Cquset*> &arr)
{
	if (strField.IsEmpty()&&strKey.IsEmpty())
	{
		AfxMessageBox("��ϢΪ�գ�����������!",MB_OK);
		return FALSE;
	}

	CString sql,strTemp;
	strKey = "%"+strKey+"%";
	sql.Format("select * from ������Ϣ where %s LIKE '%s' ",strField,strKey);

	Cquset yset(&db);
	yset.Open(1,sql);

	int i=0;
	while(!yset.IsEOF())
	{
		long lCode = yset.m_glykh;

		Cquset *pQuset = NULL;  
		if (m_mapManager.Lookup(lCode,pQuset))
		{
			arr.Add(pQuset);
		}
		yset.MoveNext();
	}
	yset.Close();

	return TRUE;
}

BOOL  CDBManage::OperManager(Cquset* pQuset,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into ������Ϣ(���,����,����Ա����,�ֻ�����,SN,����ģʽ,ʹ�ô���,��ʼ����,��������,����Ȩ��ģʽ,���õ���һ,����һ���ò�,����һ���ò�����,���õ��ݶ�,���ݶ����ò�,���ݶ����ò�����,���õ�����,���������ò�,���������ò�����,���õ�����,�����Ŀ��ò�,�����Ŀ��ò�����,��״̬) values (%d,%d,\'%s\',\'%s\',\'%s\',%d,%d,\'%s\',\'%s\',%d,%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d,\'%s\',\'%s\',%d)",
			pQuset->m_ID,
			pQuset->m_glykh,
			pQuset->m_glymc,
			pQuset->m_sjhm,
			pQuset->m_sn,			
			pQuset->m_xzms,
			pQuset->m_sycs,
			pQuset->m_qssj,
			pQuset->m_jzsj,
			pQuset->m_ctqxms,
			pQuset->m_kydt1,
			pQuset->m_dtkyc1,
			pQuset->m_dtkycxz1,
			pQuset->m_kydt2,
			pQuset->m_dtkyc2,
			pQuset->m_dtkycxz2,
			pQuset->m_kydt3,
			pQuset->m_dtkyc3,
			pQuset->m_dtkycxz3,
			pQuset->m_kydt4,
			pQuset->m_dtkyc4,
			pQuset->m_dtkycxz4,
			pQuset->m_status);
	}
	else  if (cOperType == MOD_TYPE)
	{
		sql.Format("update ������Ϣ set ����Ա����=\'%s\',�ֻ�����=\'%s\',SN=\'%s\',����ģʽ=%d,ʹ�ô���=%d ,��ʼ����=\'%s\' ,��������=\'%s\', ����Ȩ��ģʽ=%d,���õ���һ=%d ,����һ���ò�=\'%s\' ,����һ���ò�����=\'%s\',���õ��ݶ�=%d ,���ݶ����ò�=\'%s\',���ݶ����ò�����=\'%s\' ,���õ�����=%d ,���������ò�=\'%s\',���������ò�����=\'%s\' ,���õ�����=%d ,�����Ŀ��ò�=\'%s\',�����Ŀ��ò�����=\'%s\' ,��״̬=%d where  ����=%d",
			pQuset->m_glymc,
			pQuset->m_sjhm,
			pQuset->m_sn,
			pQuset->m_xzms,
			pQuset->m_sycs,
			pQuset->m_qssj,
			pQuset->m_jzsj,
			pQuset->m_ctqxms,
			pQuset->m_kydt1,
			pQuset->m_dtkyc1,
			pQuset->m_dtkycxz1,
			pQuset->m_kydt2,
			pQuset->m_dtkyc2,
			pQuset->m_dtkycxz2,
			pQuset->m_kydt3,
			pQuset->m_dtkyc3,
			pQuset->m_dtkycxz3,
			pQuset->m_kydt4,
			pQuset->m_dtkyc4,
			pQuset->m_dtkycxz4,
			pQuset->m_status,
			pQuset->m_glykh);
	}

	else  if (cOperType == DEL_TYPE)
	{
		long lID = pQuset->m_glykh;
		delete pQuset;
		pQuset  = NULL;
		m_mapManager.RemoveKey(lID);

		sql.Format("delete from ������Ϣ where ����=%d",lID);
		db.ExecuteSQL(sql);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}


	if (cOperType == ADD_TYPE)
	{
		pQuset->m_bSave  = TRUE;
	}

	return TRUE;
}

void  CDBManage::GetManagerList(CArray<Cquset*,Cquset*> &arr)
{

	CString sql;
	sql.Format("select * from ������Ϣ order by ���");

	Cquset set(&db);
	set.Open(1,sql);

	while(!set.IsEOF())
	{
		long iCode = set.m_glykh;
		Cquset *pQuset = NULL;  
		if (m_mapManager.Lookup(iCode,pQuset))
		{
			pQuset->SetQuset(&set);
		}
		else
		{
			pQuset  = new  Cquset;
			pQuset->SetQuset(&set);
			m_mapManager.SetAt(iCode,pQuset);
		}

		pQuset->m_bSave  = TRUE;

		arr.Add(pQuset);
		set.MoveNext();
	}
	set.Close();
}

long   CDBManage::GetManagerID()
{
	CString sql;
	sql.Format("select * from ������Ϣ order by  ��� desc");

	Cquset qset(&db);
	qset.Open(1,sql);
	long iCode = 1;
	while(!qset.IsEOF())
	{
		iCode = qset.m_ID + 1;
		break;
	}
	qset.Close();
	return iCode;
}

Cquset*  CDBManage::GetManagerByID(long lID, long& lStatus)
{
	Cquset*  pQuset= NULL;  
	if (m_mapManager.Lookup(lID,pQuset))
	{
		lStatus = MOD_TYPE;
	}
	else
	{
		pQuset  = new  Cquset;
		pQuset->m_ID    = lID;
		pQuset->m_glykh = lID;
		pQuset->m_bSave  = FALSE;
		m_mapManager.SetAt(lID,pQuset);
		lStatus = ADD_TYPE;
	} 
	return pQuset;
}

//-------------------------------------------����--------------------------------------------------------------------------------//
BOOL CDBManage::QurryFunc(CString strField,CString strKey,CArray<CKeyinfoset*,CKeyinfoset*> &arr)
{
	if (strField.IsEmpty()&&strKey.IsEmpty())
	{
		AfxMessageBox("��ϢΪ�գ�����������!",MB_OK);
		return FALSE;
	}

	CString sql,strTemp;
	strKey = "%"+strKey+"%";
	sql.Format("select * from ���ܿ���Ϣ where %s LIKE '%s' ",strField,strKey);

	CKeyinfoset yset(&db);
	yset.Open(1,sql);

	int i=0;
	while(!yset.IsEOF())
	{
		long lCode = yset.m_gnkh;

		CKeyinfoset *pKeyinfoset = NULL;  
		if (m_mapFunc.Lookup(lCode,pKeyinfoset))
		{
			arr.Add(pKeyinfoset);
		}
		yset.MoveNext();
	}
	yset.Close();
	return TRUE;
}

	
BOOL CDBManage::OperFunc(CKeyinfoset* pKeyinfoset,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into ���ܿ���Ϣ (���,������,����,ʹ�ô���,�ӿ�����,��������һ,������־һ,�������Ŷ�,������־��,����������,������־��,����������,������־��,����������,������־��,����������,������־��,����������,������־��,�������Ű�,������־��,�������ž�,������־��,��������ʮ,������־ʮ,Уʱʱ��,��״̬,SN ) values(%d, %d,  %d,      %d,      %d,      %d,        %d,         %d,        %d,        %d,        %d,        %d,        %d,        %d,         %d,        %d,          %d,        %d,       %d,        %d,        %d,        %d,        %d,        %d,            %d,  \'%s\',  %d,  \'%s\') ",
			pKeyinfoset->m_id,
			pKeyinfoset->m_klx,
			pKeyinfoset->m_gnkh,
			pKeyinfoset->m_sycs,
			pKeyinfoset->m_zklx,
			pKeyinfoset->m_qjkh1,    
			pKeyinfoset->m_qjbz1,
			pKeyinfoset->m_qjkh2,     
			pKeyinfoset->m_qjbz2,  
			pKeyinfoset->m_qjkh3,
			pKeyinfoset->m_qjbz3,
			pKeyinfoset->m_qjkh4,
			pKeyinfoset->m_qjbz4, 
			pKeyinfoset->m_qjkh5,   
			pKeyinfoset->m_qjbz5,  
			pKeyinfoset->m_qjkh6,   
			pKeyinfoset->m_qjbz6,  
			pKeyinfoset->m_qjkh7,   
			pKeyinfoset->m_qjbz7,  
			pKeyinfoset->m_qjkh8,   
			pKeyinfoset->m_qjbz8,
			pKeyinfoset->m_qjkh9,   
			pKeyinfoset->m_qjbz9,
			pKeyinfoset->m_qjkh10,   
			pKeyinfoset->m_qjbz10, 
			pKeyinfoset->m_jssj,
			pKeyinfoset->m_status,
			pKeyinfoset->m_sn);
	}
	else  if (cOperType ==MOD_TYPE)
	{
		sql.Format("update ���ܿ���Ϣ set ������=%d,ʹ�ô���=%d ,�ӿ�����=%d ,��������һ=%d ,������־һ=%d ,�������Ŷ�=%d ,������־��=%d,����������=%d ,������־��=%d,����������=%d ,������־��=%d,����������=%d ,������־��=%d,����������=%d ,������־��=%d,����������=%d ,������־��=%d,�������Ű�=%d ,������־��=%d,�������ž�=%d ,������־��=%d,��������ʮ=%d ,������־ʮ=%d,Уʱʱ��=\'%s\',��״̬=%d,SN=\'%s\' where  ���=%d",
			pKeyinfoset->m_klx,
			pKeyinfoset->m_sycs,
			pKeyinfoset->m_zklx,
			pKeyinfoset->m_qjkh1,    
			pKeyinfoset->m_qjbz1,
			pKeyinfoset->m_qjkh2,     
			pKeyinfoset->m_qjbz2,  
			pKeyinfoset->m_qjkh3,
			pKeyinfoset->m_qjbz3,
			pKeyinfoset->m_qjkh4,
			pKeyinfoset->m_qjbz4,             
			pKeyinfoset->m_qjkh5,   
			pKeyinfoset->m_qjbz5,  
			pKeyinfoset->m_qjkh6,   
			pKeyinfoset->m_qjbz6,  
			pKeyinfoset->m_qjkh7,  
			pKeyinfoset->m_qjbz7,  
			pKeyinfoset->m_qjkh8,   
			pKeyinfoset->m_qjbz8,
			pKeyinfoset->m_qjkh9,   
			pKeyinfoset->m_qjbz9,
			pKeyinfoset->m_qjkh10,   
			pKeyinfoset->m_qjbz10,
			pKeyinfoset->m_jssj,
			pKeyinfoset->m_status,
			pKeyinfoset->m_sn,
			pKeyinfoset->m_gnkh);
	}
	else  if (cOperType == DEL_TYPE)
	{
		long lID = pKeyinfoset->m_gnkh;
		delete pKeyinfoset;
		pKeyinfoset  = NULL;
		m_mapFunc.RemoveKey(lID);

		sql.Format("delete from ���ܿ���Ϣ where ����=%d",lID);
		db.ExecuteSQL(sql);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}

	
	if (cOperType == ADD_TYPE)
	{
		pKeyinfoset->m_bSave = TRUE; 
	}

	return TRUE;
}
void   CDBManage::GetFuncList(CArray<CKeyinfoset*,CKeyinfoset*> &arr)
{
	CString sql;
	sql.Format("select * from ���ܿ���Ϣ order by ����");

	CKeyinfoset set(&db);	set.Open(1,sql);

	while(!set.IsEOF())
	{
		long iCode = set.m_id;
		CKeyinfoset *pKeyinfoset = NULL;  
		if (m_mapFunc.Lookup(iCode,pKeyinfoset))
		{
			pKeyinfoset->SetKeyinfoset(&set);
		}
		else
		{
			pKeyinfoset  = new  CKeyinfoset;
			pKeyinfoset->SetKeyinfoset(&set);
			m_mapFunc.SetAt(iCode,pKeyinfoset);
		}

		arr.Add(pKeyinfoset);

		pKeyinfoset->m_bSave = TRUE; 
		set.MoveNext();
	}
	set.Close();
}

long    CDBManage::GetFuncID()
{
	CString sql;
	sql.Format("select * from ���ܿ���Ϣ order by  ��� desc");

	CKeyinfoset qset(&db);
	qset.Open(1,sql);
	long iCode = 1;
	while(!qset.IsEOF())
	{
		iCode = qset.m_id + 1;
		break;
	}
	qset.Close();
	return iCode;
}

CKeyinfoset* CDBManage::GetFuncByID(long lID, int& lStatus)
{
	CKeyinfoset*  pKeyinfoset= NULL;  
	if (m_mapFunc.Lookup(lID,pKeyinfoset))
	{
		lStatus = MOD_TYPE;
	}
	else
	{
		pKeyinfoset  = new  CKeyinfoset;

		pKeyinfoset->m_id = lID;
		pKeyinfoset->m_gnkh = lID;
		pKeyinfoset->m_bSave = FALSE; 
		pKeyinfoset->m_klx = FUNC_TYPE_FORBIDEN;

		m_mapFunc.SetAt(lID,pKeyinfoset);

		lStatus = ADD_TYPE;
	} 
	return pKeyinfoset;
}


//---------------------------------------------------------------------------------------------------------------------------//
BOOL CDBManage::QurryElevator(CString strField,CString strKey,CArray<CSuoset*,CSuoset*> &arr)
{
	if (strField.IsEmpty()&&strKey.IsEmpty())
	{
		AfxMessageBox("��ϢΪ�գ�����������!",MB_OK);
		return FALSE;
	}

	CString sql,strTemp;
	strKey = "%"+strKey+"%";
	sql.Format("select * from ������Ϣ where %s LIKE '%s' ",strField,strKey);

	CYonghuset yset(&db);
	yset.Open(1,sql);

	int i=0;
	while(!yset.IsEOF())
	{
		long lCode = yset.m_yzkh;

		CSuoset *pSuoset = NULL;    
		if (m_mapElevator.Lookup(lCode,pSuoset))
		{
			arr.Add(pSuoset);
		}

		yset.MoveNext();
	}
	yset.Close();

	return TRUE;
}

void CDBManage::GetElevatorList(CArray<CSuoset*,CSuoset*> &arr)
{
	arr.RemoveAll();
	CSuoset sset(&db);
	sset.Open(1,"select * from ������Ϣ order by ���ݱ�� ");

	while(!sset.IsEOF())
	{
		long iCode = sset.m_dtbh;
		CSuoset *pSuoset = NULL;  
		if (m_mapElevator.Lookup(iCode,pSuoset))
		{
			pSuoset->SetSuoset(&sset);
		}
		else
		{
			pSuoset  = new  CSuoset;
			pSuoset->SetSuoset(&sset);
			m_mapElevator.SetAt(iCode,pSuoset);
		}

		arr.Add(pSuoset);
		pSuoset->m_bSave  = TRUE;
		sset.MoveNext();
	}
	sset.Close();
}

void CDBManage::GetLasttElevator(CArray<CSuoset*,CSuoset*> &arr)
{
	CSuoset sset(&db);
	sset.Open(1,"select * from ������Ϣ order by ���ݱ�� ");

	while(!sset.IsEOF())
	{
		long iCode = sset.m_dtbh;
		CSuoset *pSuoset = NULL;  
		if (m_mapElevator.Lookup(iCode,pSuoset))
		{
			pSuoset->SetSuoset(&sset);
		}
		else
		{
			pSuoset  = new  CSuoset;
			pSuoset->SetSuoset(&sset);
			m_mapElevator.SetAt(iCode,pSuoset);
		}

		arr.Add(pSuoset);
		pSuoset->m_bSave  = TRUE;
		sset.MoveNext();
	}
	sset.Close();
}
//
//void CDBManage::GetElevatorList2(CArray<CSuoset*,CSuoset*> &arr)
//{
//	CSuoset sset(&db);
//	sset.Open(1,"select * from ������Ϣ order by ���ݱ�� ");
//
//	while(!sset.IsEOF())
//	{
//		long iCode = sset.m_dtbh;
//		CSuoset *pSuoset = NULL;  
//		if (m_mapElevator.Lookup(iCode,pSuoset))
//		{
//			pSuoset->SetSuoset(&sset);
//		}
//		else
//		{
//			pSuoset  = new  CSuoset;
//			pSuoset->SetSuoset(&sset);
//			m_mapElevator.SetAt(iCode,pSuoset);
//		}
//
//		arr.Add(pSuoset);
//		pSuoset->m_bSave  = TRUE;
//		sset.MoveNext();
//	}
//	sset.Close();
//}

long    CDBManage::GetElevatorID()
{
	CString sql;
	sql.Format("select * from ������Ϣ order by  ���ݱ�� desc");

	CSuoset qset(&db);
	qset.Open(1,sql);
	long iCode = 1;
	while(!qset.IsEOF())
	{
		iCode = qset.m_dtbh + 1;
		break;
	}
	qset.Close();
	return iCode;
}

CSuoset*  CDBManage::GetElevatorByID(long lElv)
{
	CSuoset *pSuoset = NULL; 
	if (m_mapElevator.Lookup(lElv,pSuoset))
	{
		;
	}
	else
	{
		pSuoset  = new  CSuoset;
		pSuoset->m_dtbh   = lElv;
		pSuoset->m_bSave = FALSE; 
		m_mapElevator.SetAt(lElv,pSuoset);
	}

	return pSuoset;
}

int  CDBManage::RemoveElevatorofID(long lElv)
{
	CSuoset *pSuoset = NULL; 
	if (m_mapElevator.Lookup(lElv,pSuoset))
	{
		delete pSuoset;
		pSuoset = NULL;

		m_mapElevator.RemoveKey(lElv);
	}

	return m_mapElevator.GetSize();
}

CString  CDBManage::GetElevatorNameByID(long lElv)
{
	CString strName;
	CSuoset *pSuoset = NULL; 
	if (m_mapElevator.Lookup(lElv,pSuoset))
	{
		strName =  pSuoset->m_dtmc;
	} 
	return strName;
}

CSuoset*   CDBManage::GetElevatorByName(CString strElv)
{
	if (strElv.IsEmpty())
		return NULL;

	long lCode = 0;
	CSuoset *pSuoset = NULL;
	POSITION pos = m_mapElevator.GetStartPosition();
	while(pos)
	{
		m_mapElevator.GetNextAssoc(pos,lCode,pSuoset);
		ASSERT(pSuoset);

		if( 0== pSuoset->m_dtmc.CompareNoCase(strElv))
		{
			return pSuoset;
		}
	}
	return pSuoset;
}

BOOL CDBManage::OperElevator(CSuoset* pSuoset,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into [������Ϣ] ([���ݱ��],[��������],[��������],[�ܲ���],[��ʼ¥��],[����¥��],[¥���ʶ]) values (%d,\'%s\',%d,%d,%d,%d,\'%s\')",
			pSuoset->m_dtbh,
			pSuoset->m_dtmc,
			pSuoset->m_dtlx,
			pSuoset->m_dtcs,
			pSuoset->m_qslc,
			pSuoset->m_gglc,
			pSuoset->m_dtlcbs);
	}
	else	if (cOperType == MOD_TYPE)
	{
		sql.Format("update ������Ϣ set ��������=\'%s\',��������=%d,�ܲ���=%d,��ʼ¥��=%d,����¥��=%d ,¥���ʶ=\'%s\'  where  ���ݱ��=%d",
			pSuoset->m_dtmc,
			pSuoset->m_dtlx,
			pSuoset->m_dtcs,
			pSuoset->m_qslc,
			pSuoset->m_gglc,
			pSuoset->m_dtlcbs,
			pSuoset->m_dtbh);
	}
	else  if (cOperType == DEL_TYPE)
	{
		long lID = pSuoset->m_dtbh;
		delete pSuoset;
		pSuoset  = NULL;
		m_mapElevator.RemoveKey(lID);

		sql.Format("delete from ������Ϣ where ���ݱ��=%d",lID);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		DWORD dwErr = GetLastError();
		return FALSE;
	}

	if (cOperType == ADD_TYPE)
	{
		pSuoset->m_bSave = TRUE; 
	}


	return TRUE;
}

//---------------------------------------------------------------------------------------------------------------

BOOL CDBManage::OperProxySet(CProxySet* pProxySet,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into [��������Ϣ] ([���],[��������],[�ֻ�����],[����ID],[SN],[��ע]) values (%d, \'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			pProxySet->m_dlsbh,
			pProxySet->m_dlsmc,
			pProxySet->m_sjhm,
			pProxySet->m_dlsid,
			pProxySet->m_sn,
			pProxySet->m_bzxx);
		//sql.Format("insert into [��������Ϣ] ([���],[��������],[�绰����],[����ID],[��ע]) values (%d,\'%s\','%s\',\'%s\', \'%s\')",pProxySet->m_dlsbh,pProxySet->m_dlsmc,pProxySet->m_sjhm,pProxySet->m_dlsid,pProxySet->m_bzxx);
	}
	else  if (cOperType == MOD_TYPE)
	{

		sql.Format("update ��������Ϣ set ��������=\'%s\',�ֻ�����=\'%s\',����ID=\'%s\' ,SN=\'%s\',��ע=\'%s\' where  ���=%d",
			pProxySet->m_dlsmc,pProxySet->m_sjhm,pProxySet->m_dlsid,pProxySet->m_sn,pProxySet->m_bzxx,pProxySet->m_dlsbh);
	}
	else  if (cOperType == DEL_TYPE)
	{
		long lID = pProxySet->m_dlsbh;
		delete pProxySet;
		pProxySet  = NULL;
		m_mapProxy.RemoveKey(lID);

		sql.Format("delete from ��������Ϣ where ���=%d",lID);
		db.ExecuteSQL(sql);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

void CDBManage::GetProxyList()
{
	CProxySet sset(&db);
	sset.Open(1,"select * from ��������Ϣ order by ���");

	while(!sset.IsEOF())
	{
		long iCode = sset.m_dlsbh;
		CProxySet *pProxySet = NULL;  
		if (m_mapProxy.Lookup(iCode,pProxySet))
		{
			pProxySet->SetProxySet(&sset);
		}
		else
		{
			pProxySet  = new  CProxySet;
			pProxySet->SetProxySet(&sset);
			m_mapProxy.SetAt(iCode,pProxySet);
		}
		sset.MoveNext();
	}
	sset.Close();
}

long   CDBManage::GetProxyID()
{
	CString sql;
	sql.Format("select * from ��������Ϣ order by  ��� desc");

	CProxySet qset(&db);
	qset.Open(1,sql);
	long iCode = 1;
	while(!qset.IsEOF())
	{
		iCode = qset.m_dlsbh + 1;
		break;
	}
	qset.Close();
	return iCode;
}

CProxySet*  CDBManage::GetProxyByID(long llD)
{
	CProxySet *pProxySet = NULL; 
	if (m_mapProxy.Lookup(llD,pProxySet))
	{
		;
	}
	else
	{
		pProxySet  = new  CProxySet;
		pProxySet->m_dlsbh   = llD;
		m_mapProxy.SetAt(llD,pProxySet);
	}

	return pProxySet;
}


int  CDBManage::RemoveProxyOfID(long llD)
{
	CProxySet *pProxySet = NULL; 
	if (m_mapProxy.Lookup(llD,pProxySet))
	{
		delete pProxySet;
		pProxySet = NULL;

		m_mapProxy.RemoveKey(llD);
	}

	return m_mapProxy.GetSize();
}

//---------------------------------------------------------------------------------------------------------------

void CDBManage::GetMakeCardList()
{
	CMakeCardSet sset(&db);
	sset.Open(1,"select * from �ƿ���Ϣ");

	while(!sset.IsEOF())
	{
		CString strMakeTime= sset.m_strMakecrdTime;
		CMakeCardSet *pMakeCardSet = NULL;  
		if (m_mapMakeCard.Lookup(strMakeTime,pMakeCardSet))
		{
			pMakeCardSet->SetProxySet(&sset);
		}
		else
		{
			pMakeCardSet  = new  CMakeCardSet;
			pMakeCardSet->SetProxySet(&sset);
			m_mapMakeCard.SetAt(strMakeTime,pMakeCardSet);
		}
		sset.MoveNext();
	}
	sset.Close();
}

CMakeCardSet*  CDBManage::GetMakeCardByName(CString strMakeTime)
{
	CMakeCardSet *pMakeCardSet = NULL; 
	if (m_mapMakeCard.Lookup(strMakeTime,pMakeCardSet))
	{
		;
	}
	else
	{
		pMakeCardSet  = new  CMakeCardSet;
		m_mapMakeCard.SetAt(strMakeTime,pMakeCardSet);
	}

	return pMakeCardSet;
}

BOOL  CDBManage::OperMakeCard(CMakeCardSet* pMakeCardSet,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into [�ƿ���Ϣ] ([�ƿ�ʱ��],[�ƿ�����],[��ע]) values (\'%s\',\'%d\',\'%s\')",
			pMakeCardSet->m_strMakecrdTime,pMakeCardSet->m_iMakecrdNum,pMakeCardSet->m_strDes);


		CMakeCardSet* pMakeCard = new CMakeCardSet;
		pMakeCard->SetProxySet(pMakeCardSet);

		pMakeCard->m_ID = m_mapMakeCard.GetSize() + 1;
		pMakeCardSet->m_ID = pMakeCard->m_ID ;
		m_mapMakeCard.SetAt(pMakeCardSet->m_strMakecrdTime, pMakeCard);
		//sql.Format("insert into [��������Ϣ] ([���],[��������],[�绰����],[����ID],[��ע]) values (%d,\'%s\','%s\',\'%s\', \'%s\')",pProxySet->m_dlsbh,pProxySet->m_dlsmc,pProxySet->m_sjhm,pProxySet->m_dlsid,pProxySet->m_bzxx);
	}
	else  if (cOperType == MOD_TYPE)
	{
		CMakeCardSet* pMakeCard = NULL;
		if(m_mapMakeCard.Lookup(pMakeCardSet->m_strMakecrdTime, pMakeCard))
		{
			pMakeCard->m_iMakecrdNum = pMakeCardSet->m_iMakecrdNum;
			pMakeCard->m_strDes = pMakeCardSet->m_strDes;
			pMakeCard->m_strUser = pMakeCardSet->m_strUser;	
			sql.Format("update �ƿ���Ϣ set �ƿ�����=\'%s\',��ע=\'%s\'  where  �ƿ�ʱ��=\'%s\'",
				pMakeCardSet->m_iMakecrdNum,pMakeCardSet->m_strDes,pMakeCardSet->m_strMakecrdTime);
		}
		return FALSE;
	}
	else  if (cOperType == DEL_TYPE)
	{
		CString strMakeTime= pMakeCardSet->m_strMakecrdTime;
		delete pMakeCardSet;
		pMakeCardSet  = NULL;
		m_mapMakeCard.RemoveKey(strMakeTime);

		sql.Format("delete from �ƿ���Ϣ where �ƿ�ʱ��=\'%s\'",strMakeTime);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}


// ---------------------------------------�߼�������----------------------------------------
void    CDBManage::GetAdvancCardList(CArray<CAdvancCardSet*,CAdvancCardSet*> &arr)
{
	CAdvancCardSet sset(&db);
	sset.Open(1,"select * from �߼�����Ϣ");

	while(!sset.IsEOF())
	{
		long lID= sset.m_ID;
		CAdvancCardSet *pSet = NULL;  
		if (m_mapAdvancCard.Lookup(lID,pSet))
		{
			pSet->SetProxySet(&sset);
		}
		else
		{
			pSet  = new  CAdvancCardSet;
			pSet->SetProxySet(&sset);
			m_mapAdvancCard.SetAt(lID,pSet);
		}

		arr.Add(pSet);
		sset.MoveNext();
	}
	sset.Close();
}

CAdvancCardSet*   CDBManage::GetAdvancCardByID(long ID)
{
	CAdvancCardSet *pSet = NULL; 
	if (m_mapAdvancCard.Lookup(ID,pSet))
	{
		;
	}
	else
	{
		pSet  = new  CAdvancCardSet;
		m_mapAdvancCard.SetAt(ID,pSet);
	}
	return pSet;
}

long   CDBManage::GetAdvancCardID()
{
	CString sql;
	sql.Format("select * from �߼�����Ϣ order by  ���� desc");

	CAdvancCardSet qset(&db);
	qset.Open(1,sql);
	long iCode = 0;
	while(!qset.IsEOF())
	{
		iCode = qset.m_ID + 1;
		break;
	}
	qset.Close();
	return iCode;
}


BOOL   CDBManage::OperAdvancCard(CAdvancCardSet* pAdvancCardSet,char cOperType)
{
	CString sql;
	if (cOperType == ADD_TYPE)
	{
		sql.Format("insert into [�߼�����Ϣ] ([�ֿ���],[�ֻ�����],[SN],[�ֿ�����],[��ע]) values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			pAdvancCardSet->m_ckr,pAdvancCardSet->m_sjhm,pAdvancCardSet->m_SN,pAdvancCardSet->m_cCklc,pAdvancCardSet->m_bz);
	}
	else  if (cOperType == MOD_TYPE)
	{

		sql.Format("update �߼�����Ϣ set �ֿ���=\'%s\',�ֻ�����=\'%s\', SN=\'%s\',�ֿ�����=\'%s\',��ע=\'%s\' where  ����=%d",
			pAdvancCardSet->m_ckr,pAdvancCardSet->m_sjhm,pAdvancCardSet->m_SN,pAdvancCardSet->m_cCklc,pAdvancCardSet->m_bz,pAdvancCardSet->m_ID);
	}
	else  if (cOperType == DEL_TYPE)
	{
		long lID = pAdvancCardSet->m_ID;
		delete pAdvancCardSet; 
		pAdvancCardSet  = NULL;
		m_mapAdvancCard.RemoveKey(lID);

		sql.Format("delete from �߼�����Ϣ where ����= %d",lID);
		db.ExecuteSQL(sql);
	}
	else
	{
		return FALSE;
	}

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

//��ҵ��Ϣ
BOOL CDBManage::RecordAgentID(DWORD dwAgentID, LPCTSTR lpszDes)
{
	CString sql;
	sql.Format("insert into [AgentInfo] ([ID],[AGENTID],[AGENTDES]) values (1,%d,\'%s\')",
		dwAgentID, lpszDes);

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDBManage::ReadAgentID(DWORD& dwAgentID, LPCTSTR lpszDes)
{
	CString sql;
	sql.Format("select * from AgentInfo");

	CAgentIDRecord agentIDRecord(&db);
	agentIDRecord.Open(1,sql);
	long iCode = 0;
	while(!agentIDRecord.IsEOF())
	{
		dwAgentID = agentIDRecord.m_lAgentID;
		lpszDes = agentIDRecord.m_szAgentDes;
		break;
	}
	agentIDRecord.Close();
	return TRUE;
}


BOOL CDBManage::ClearAgentID()
{

	CString sql;
	sql.Format("delete * from AgentInfo");

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDBManage::RecordOffset(int iOffset, int iRecode)
{
	CString sql;
	sql.Format("update Offset_Section set Offset = %d,Recode = %d where ID = 1",
		iOffset, iRecode);

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}
BOOL CDBManage::ReadOffset(int &iOffset, int& iRecode)
{
	CString sql;
	sql.Format("select * from Offset_Section");

	COffsetRecord offsetRecord(&db);
	offsetRecord.Open(1,sql);
	long iCode = 0;
	while(!offsetRecord.IsEOF())
	{
		iOffset = offsetRecord.m_Offset;
		iRecode = offsetRecord.m_Recode;
		break;
	}
	offsetRecord.Close();
	return TRUE;
}

BOOL CDBManage::ClearOffset()
{

	CString sql;
	sql.Format("delete * from Offset_Section");

	try
	{
		db.ExecuteSQL(sql);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}