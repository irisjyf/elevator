#pragma once
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Loginset.h"
#include "Yonghuset.h"
#include "Suoset.h"
#include "quset.h"
#include "Keyinfoset.h"
#include "ProxySet.h"
#include "MakeCardSet.h"
#include "AdvancCardSet.h"

#define  DB_REC_NUM     1000
#define  CARD_STRAT_NO  1000


#define  SAVE_NOT   1    
#define  SAVE_YES   2

#define LPDBManage			    (CDBManage::GetDBManage())


typedef struct tagUSERINFO //用户信息
{
	CString  m_strUser;               //用户名称
	CString  m_strPsw;               //密码
	CString  m_strAuth;               //用户权限
}USERINFO, *LPUSERINFO;

//数据库管理
class CDBManage
{
public:
	CDBManage(void);
	~CDBManage(void);
	static CDBManage *      GetDBManage();
	USERINFO  m_USERINFO;
public:
	BOOL OpenDB();


	//偏移加密信息
	BOOL RecordOffset(int iOffset, int iRecode);
	BOOL ReadOffset(int &iOffset, int& iRecode);
	BOOL ClearOffset();

	//物业信息
	BOOL RecordAgentID(DWORD dwAgentID, LPCTSTR lpszDes);
	BOOL ReadAgentID(DWORD& dwAgentID, LPCTSTR lpszDes);
	BOOL ClearAgentID();

	// ----------------用户操作--------------------
	BOOL Login(CString strUser, CString strPsw);
	BOOL OPerUser(CString strUser, CString strPsw, CString strPsw2, CString strAuth,CString strOldPsw = _T(""));
	BOOL AddUser(CString strUser, CString strPsw, CString strAuth);
	BOOL DelUser(CString strUser);
	void GetUserList();
	CString GetCurrentUser();
	CMap<CString,LPCTSTR,CLoginset*,CLoginset*> m_mapLoginset;

	// ----------------用户卡操作--------------------
	BOOL QurryCustomer(CString strField,CString strKey,CArray<CYonghuset*,CYonghuset*> &arr);
	BOOL OpereCustomer(CYonghuset* pYonghuset,char cOperType);
	void GetCustermerList(CArray<CYonghuset*,CYonghuset*> &arr);
	long        GetCustermerID();// 已编号为序
	CYonghuset* GetCustermerByID(long lID, long& lStatus);
	CMap<long,long,CYonghuset*,CYonghuset*> m_mapCustermer;


	// ----------------管理员操作--------------------
	BOOL QurryManager(CString strField,CString strKey,CArray<Cquset*,Cquset*> &arr);
	BOOL OperManager(Cquset* pQuset,char cOperType);
	void   GetManagerList(CArray<Cquset*,Cquset*> &arr);
	long    GetManagerID();
	Cquset* GetManagerByID(long lID , long& lStatus);
	CMap<long,long,Cquset*,Cquset*> m_mapManager;


	// ----------------功能卡操作--------------------
	BOOL QurryFunc(CString strField,CString strKey,CArray<CKeyinfoset*,CKeyinfoset*> &arr);
	BOOL OperFunc(CKeyinfoset* pKeyinfoset,char cOperType);
	void    GetFuncList(CArray<CKeyinfoset*,CKeyinfoset*> &arr);
	long    GetFuncID();
	CKeyinfoset* GetFuncByID(long lID, int& lStatus);
	CMap<long,long,CKeyinfoset*,CKeyinfoset*> m_mapFunc;


	// ----------------电梯操作--------------------
	BOOL      QurryElevator(CString strField,CString strKey,CArray<CSuoset*,CSuoset*> &arr);
	void      GetElevatorList(CArray<CSuoset*,CSuoset*> &arr);
	//用于增加电梯后获取最后一个电梯信息
	void      GetLasttElevator(CArray<CSuoset*,CSuoset*> &arr);
	//void	  GetElevatorList2(CArray<CSuoset*,CSuoset*> &arr);
	long      GetElevatorID();
	CString   GetElevatorNameByID(long lElv);
	CSuoset*  GetElevatorByID(long lElv);
	int  RemoveElevatorofID(long lElv);
	CSuoset*  GetElevatorByName(CString strElv);
	BOOL      OperElevator(CSuoset* pSuoset,char cOperType);
	CMap<long,long,CSuoset*,CSuoset*> m_mapElevator;


	// ----------------代理商操作--------------------
	BOOL QurryProxy(CString strField,CString strKey,CMap<long,long,CProxySet*,CProxySet*> &mapProxy);
	BOOL OperProxySet(CProxySet* pProxySet,char cOperType);
	void GetProxyList();
	long        GetProxyID();// 已编号为序
	CProxySet* GetProxyByID(long lID = 0);
	int  RemoveProxyOfID(long llD);
	CMap<long,long,CProxySet*,CProxySet*> m_mapProxy;

	// ----------------制卡管理-------------------------
	void           GetMakeCardList();
	CMakeCardSet*  GetMakeCardByName(CString strMakeTime);
	BOOL           OperMakeCard(CMakeCardSet* pMakeCardSet,char cOperType);
	
	CMap<CString,LPCTSTR,CMakeCardSet*,CMakeCardSet*> m_mapMakeCard;


	// ----------------高级卡管理-------------------------
	void           GetAdvancCardList(CArray<CAdvancCardSet*,CAdvancCardSet*> &arr);
	CAdvancCardSet*  GetAdvancCardByID(long ID= 0);
	long           GetAdvancCardID();
	BOOL           OperAdvancCard(CAdvancCardSet* pAdvancCardSet,char cOperType);
	CMap<long,long,CAdvancCardSet*,CAdvancCardSet*> m_mapAdvancCard;     
};

