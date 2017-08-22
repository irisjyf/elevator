#pragma once

#include "ConfigInfo.h"

#define LPSerialProtocol		     (CSerialProtocol::GetSerialProtocol())
//���п�ͨ�ŷ�ʽ
class CSerialProtocol 
{
public:
	CSerialProtocol();
	virtual ~CSerialProtocol();

	static CSerialProtocol *      GetSerialProtocol();
protected:
	HANDLE      m_hComDev;				//ͨ�Ŷ˿ھ��
	int	    	m_nerrnum;				//�������,���ڼ�⴮�ڴ����Ը�λ��
	
public:

	CConfigInfo  m_config;

	virtual BOOL	IsConnect();
	virtual BOOL	Connect();
	virtual void	Disconnect();
	virtual int		SendData(BYTE *pb, int nsize);
	virtual int		ReadData(BYTE *pb, int nsize);

public:
	BOOL TestConnect(CConfigInfo &config);
	void SetConfig(CConfigInfo &config) { m_config = config; }
	BOOL  DoRead(BYTE btTypeCode);
	BOOL  DoSend(BYTE btTypeCode);

public:
	short  CalaCS(BYTE *pData, int iSize);
};