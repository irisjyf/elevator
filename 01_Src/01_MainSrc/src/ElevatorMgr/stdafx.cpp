// stdafx.cpp : 只包括标准包含文件的源文件
// ElevatorMgr.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "Define.h"

CDatabase  db;
CRecordset *rs;

BOOL   LoadDbSource(CString   strSourceName,   CString   strSourceDb,   CString   strDescription)   
{   
	//存放打开的注册表键   
	HKEY   hKey;   
	DWORD   dw;   

	//存放注册表API函数执行的返回值   
	LONG   lReturn;   

	//存放要打开的子键   
	CString   strSubKey;   

	//检测是否安装了MS   Access   ODBC   driver:odbcjt32.dll   
	//获得   Windows系统目录   
	char   sysDir[MAX_PATH];   
	char   drvName[] = "\\odbcjt32.dll";   
	::GetSystemDirectory(sysDir,   MAX_PATH);   
	strcat(sysDir,drvName);   
	CFileFind   findFile;   
	if(!findFile.FindFile(sysDir))   
	{   
		AfxMessageBox("您的计算机系统中没有安装MS   Access的ODBC驱动程序odbcjt32.dll,您将无法加载该类数据源。"   ,MB_OK   |   MB_ICONSTOP);   
		return   false;   
	}   

	strSubKey.Format("SOFTWARE\\ODBC\\ODBC.INI\\%s",strSourceName);
		//创建   ODBC数据源在注册表中的子键   
	lReturn=::RegCreateKeyEx(HKEY_LOCAL_MACHINE,   (LPCTSTR)strSubKey,   0,   NULL,   REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hKey,&dw);   
	if(lReturn   !=   ERROR_SUCCESS)   
		return   false;   

	//设置数据源的各项参数   
	CString   strDbq   =   strSourceDb;   
	CString   strDriver   =   sysDir;   
	DWORD   dwDriverId   =   25;   
	CString   strFil   =   "MS   Access;";   
	CString   strPwd   =   strSourceName;   
	DWORD   dwSafeTransactions   =   0;   
	CString   strUid   =   strSourceName;   
	::RegSetValueEx(hKey,   "DBQ",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strDbq),   strDbq.GetLength());   
	::RegSetValueEx(hKey,   "Description",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strDescription),   strDescription.GetLength());   
	::RegSetValueEx(hKey,   "Driver",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strDriver),   strDriver.GetLength());  
	::RegSetValueEx(hKey,   "DriverId",   0L,   REG_DWORD,   (CONST   BYTE*)(&dwDriverId),   sizeof(dw));   
	::RegSetValueEx(hKey,   "FIL",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strFil),strFil   .GetLength   ());   
	::RegSetValueEx(hKey,   "PWD",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strPwd),strPwd.GetLength   ());   
	::RegSetValueEx(hKey,   "SafeTransactions",   0L,   REG_DWORD,   (CONST   BYTE*)(&dwSafeTransactions),   sizeof(dw));   
	::RegSetValueEx(hKey,   "UID",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strUid),strUid.GetLength());   
	::RegCloseKey(hKey);   

	//创建   ODBC数据源的Jet子键   
	strSubKey   +=   "\\Engines\\Jet";   
	lReturn   =   ::RegCreateKeyEx(HKEY_LOCAL_MACHINE,   (LPCTSTR)strSubKey,   0,   NULL,   REG_OPTION_NON_VOLATILE,   KEY_WRITE,   NULL,   &hKey,   &dw);   
	if(lReturn   !=   ERROR_SUCCESS)   
		return   false;   

	//设置该子键下的各项参数   
	CString   strImplict="";   
	CString   strUserCommit="Yes";   
	DWORD   dwPageTimeout=5;   
	DWORD   dwThreads=3;   
	DWORD   dwMaxBufferSize=2048;   
	::RegSetValueEx(hKey,   "ImplicitCommitSync",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strImplict),   strImplict.GetLength()+1);   
	::RegSetValueEx(hKey,   "MaxBufferSize",   0L,   REG_DWORD,   (CONST   BYTE*)(&dwMaxBufferSize),   sizeof(dw));   
	::RegSetValueEx(hKey,   "PageTimeout",   0L,   REG_DWORD,   (CONST   BYTE*)(&dwPageTimeout),   sizeof(dw));   
	::RegSetValueEx(hKey,   "Threads",   0L,   REG_DWORD,   (CONST   BYTE*)(&dwThreads),   sizeof(dw));   
	::RegSetValueEx(hKey,   "UserCommitSync",   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strUserCommit),   strUserCommit.GetLength());   
	::RegCloseKey(hKey);   

	//设置ODBC数据库引擎名称   
	lReturn=::RegOpenKeyEx(HKEY_LOCAL_MACHINE,   "SOFTWARE\\ODBC\\ODBC.INI\\ODBC   Data   Sources",   0L,   KEY_WRITE,   &hKey);   
	if(lReturn   !=   ERROR_SUCCESS)   
		return   false;   
	CString   strDbType="Microsoft   Access   Driver   (*.mdb)";   
	::RegSetValueEx(hKey,   strSourceName,   0L,   REG_SZ,   (CONST   BYTE*)((LPCTSTR)strDbType),   strDbType.GetLength());   

	return   true;   
}   

BOOL CheckCrc(BYTE *pDatas, long lLength)
{
	BYTE *p = pDatas;
	int i=0;
	unsigned char chPackageFlag;
	if((p[i++])!=0xef) 
		return FALSE;
	if((p[i++])!=0x01) 
		return FALSE;
	chPackageFlag = p[i++];

	i++; 
	
	int len2 = p[i++]; 

	int crc = chPackageFlag + len2;
	int j=0, k = 0;

	while(len2-2)
	{
		k = p[i++];

		crc += k;
		len2--;
	}

	crc -= (unsigned int) p[i++]*256;
	
	crc -= p[i++];
	
	if(crc == 0)
		return TRUE;
	return FALSE;

	//LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	//short shCrc = 0;
	//int iLength = lpFrameHead->chLength[0] * 256 + lpFrameHead->chLength[1];
	//BYTE *p = pDatas + sizeof(T_FRAME_RET_HEAD);
	//for (int i=0; i<iLength - 2; i++)
	//{
	//	shCrc += p[i];
	//}
	//shCrc = shCrc + lpFrameHead->chPacketType + iLength;
	//p = pDatas + sizeof(T_FRAME_RET_HEAD) + iLength;
	//shCrc = shCrc - p[0] * 256;
	//shCrc -= p[1];
	//if(shCrc != 0)
	//	return FALSE;
	//else
	//	return TRUE;
}

CString GetFunctionCardType(int iType)
{
	CString strRet;
	if((iType&0x0f)==FUNC_TYPE_FORBIDEN)
	{
		strRet = "启禁卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_CHECK_TIME)
	{
		strRet = "校时卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_SWITCH)
	{
		strRet = "开关卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_OFFSET)
	{
		strRet = "偏移卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_AGENT)
	{
		strRet = "物业识别卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_Check)
	{
		strRet = "获取内部参数卡";
	}
	else if((iType&0x0f)==FUNC_TYPE_CLEARBLACKLIST)
	{
		strRet = "清除黑名单卡";
	}
	return strRet;
}

int SplitString(const CString str, char split, CStringArray &strArray)  
{  
	strArray.RemoveAll();  
	CString strTemp = str;  
	int iIndex = 0;  
	while (1)  
	{  
		iIndex = strTemp.Find(split);  
		if(iIndex >= 0)  
		{  
			strArray.Add(strTemp.Left(iIndex));  
			strTemp = strTemp.Right(strTemp.GetLength()-iIndex-1);  
		}  
		else  
		{  
			break;  
		}  
	}  
	strArray.Add(strTemp);  

	return strArray.GetSize();  
}  
CString ParseElevatorFloor(BYTE btData, int iIndex, int iBase)
{

	CString szInfo;
	CString szTemp;
	BYTE btMask = 0x01;
	for (int i=0; i<8; i++)
	{
		if((btData & (btMask << i)) > 0)
		{
			int iFloor = i + iIndex * 8 + iBase;
			if(iFloor >= 0)
				iFloor++;
			if(iBase > 0)
				iFloor--;

			szTemp.Format("%d,", iFloor);
		}
		if(!szTemp.IsEmpty())
		{
			szInfo += szTemp;
		}

		szTemp.Empty();
	}
	return szInfo;
}
