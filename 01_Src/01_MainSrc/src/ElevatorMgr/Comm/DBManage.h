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


typedef struct tagUSERINFO //�û���Ϣ
{
	CString  m_strUser;               //�û�����
	CString  m_strPsw;               //����
	CString  m_strAuth;               //�û�Ȩ��
}USERINFO, *LPUSERINFO;

//���ݿ����
class CDBManage
{
public:
	CDBManage(void);
	~CDBManage(void);
	static CDBManage *      GetDBManage();
	USERINFO  m_USERINFO;
public:
	BOOL OpenDB();


	//ƫ�Ƽ�����Ϣ
	BOOL RecordOffset(int iOffset, int iRecode);
	BOOL ReadOffset(int &iOffset, int& iRecode);
	BOOL ClearOffset();

	//��ҵ��Ϣ
	BOOL RecordAgentID(DWORD dwAgentID, LPCTSTR lpszDes);
	BOOL ReadAgentID(DWORD& dwAgentID, LPCTSTR lpszDes);
	BOOL ClearAgentID();

	// ----------------�û�����--------------------
	BOOL Login(CString strUser, CString strPsw);
	BOOL OPerUser(CString strUser, CString strPsw, CString strPsw2, CString strAuth,CString strOldPsw = _T(""));
	BOOL AddUser(CString strUser, CString strPsw, CString strAuth);
	BOOL DelUser(CString strUser);
	void GetUserList();
	CString GetCurrentUser();
	CMap<CString,LPCTSTR,CLoginset*,CLoginset*> m_mapLoginset;

	// ----------------�û�������--------------------
	BOOL QurryCustomer(CString strField,CString strKey,CArray<CYonghuset*,CYonghuset*> &arr);
	BOOL OpereCustomer(CYonghuset* pYonghuset,char cOperType);
	void GetCustermerList(CArray<CYonghuset*,CYonghuset*> &arr);
	long        GetCustermerID();// �ѱ��Ϊ��
	CYonghuset* GetCustermerByID(long lID, long& lStatus);
	CMap<long,long,CYonghuset*,CYonghuset*> m_mapCustermer;


	// ----------------����Ա����--------------------
	BOOL QurryManager(CString strField,CString strKey,CArray<Cquset*,Cquset*> &arr);
	BOOL OperManager(Cquset* pQuset,char cOperType);
	void   GetManagerList(CArray<Cquset*,Cquset*> &arr);
	long    GetManagerID();
	Cquset* GetManagerByID(long lID , long& lStatus);
	CMap<long,long,Cquset*,Cquset*> m_mapManager;


	// ----------------���ܿ�����--------------------
	BOOL QurryFunc(CString strField,CString strKey,CArray<CKeyinfoset*,CKeyinfoset*> &arr);
	BOOL OperFunc(CKeyinfoset* pKeyinfoset,char cOperType);
	void    GetFuncList(CArray<CKeyinfoset*,CKeyinfoset*> &arr);
	long    GetFuncID();
	CKeyinfoset* GetFuncByID(long lID, int& lStatus);
	CMap<long,long,CKeyinfoset*,CKeyinfoset*> m_mapFunc;


	// ----------------���ݲ���--------------------
	BOOL      QurryElevator(CString strField,CString strKey,CArray<CSuoset*,CSuoset*> &arr);
	void      GetElevatorList(CArray<CSuoset*,CSuoset*> &arr);
	//�������ӵ��ݺ��ȡ���һ��������Ϣ
	void      GetLasttElevator(CArray<CSuoset*,CSuoset*> &arr);
	//void	  GetElevatorList2(CArray<CSuoset*,CSuoset*> &arr);
	long      GetElevatorID();
	CString   GetElevatorNameByID(long lElv);
	CSuoset*  GetElevatorByID(long lElv);
	int  RemoveElevatorofID(long lElv);
	CSuoset*  GetElevatorByName(CString strElv);
	BOOL      OperElevator(CSuoset* pSuoset,char cOperType);
	CMap<long,long,CSuoset*,CSuoset*> m_mapElevator;


	// ----------------�����̲���--------------------
	BOOL QurryProxy(CString strField,CString strKey,CMap<long,long,CProxySet*,CProxySet*> &mapProxy);
	BOOL OperProxySet(CProxySet* pProxySet,char cOperType);
	void GetProxyList();
	long        GetProxyID();// �ѱ��Ϊ��
	CProxySet* GetProxyByID(long lID = 0);
	int  RemoveProxyOfID(long llD);
	CMap<long,long,CProxySet*,CProxySet*> m_mapProxy;

	// ----------------�ƿ�����-------------------------
	void           GetMakeCardList();
	CMakeCardSet*  GetMakeCardByName(CString strMakeTime);
	BOOL           OperMakeCard(CMakeCardSet* pMakeCardSet,char cOperType);
	
	CMap<CString,LPCTSTR,CMakeCardSet*,CMakeCardSet*> m_mapMakeCard;


	// ----------------�߼�������-------------------------
	void           GetAdvancCardList(CArray<CAdvancCardSet*,CAdvancCardSet*> &arr);
	CAdvancCardSet*  GetAdvancCardByID(long ID= 0);
	long           GetAdvancCardID();
	BOOL           OperAdvancCard(CAdvancCardSet* pAdvancCardSet,char cOperType);
	CMap<long,long,CAdvancCardSet*,CAdvancCardSet*> m_mapAdvancCard;     
};

