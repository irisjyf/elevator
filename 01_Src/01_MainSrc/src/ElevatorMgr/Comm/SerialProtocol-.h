#pragma once

#include "ConfigInfo.h"

#define LPSerialProtocol		     (CSerialProtocol::GetSerialProtocol())
//串行口通信方式
class CSerialProtocol 
{
public:
	CSerialProtocol();
	virtual ~CSerialProtocol();

	static CSerialProtocol *      GetSerialProtocol();
protected:
	HANDLE      m_hComDev;				//通信端口句柄
	int	    	m_nerrnum;				//错误次数,用于监测串口错误，自复位用
	
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