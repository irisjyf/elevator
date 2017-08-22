#pragma once

#include "ConfigInfo.h"

#define  BUFFER_LENGTH	500

//�ص�������//���ݻص�����
#define LPSerialProtocol		     (CSerialProtocol::GetSerialProtocol())

//���п�ͨ�ŷ�ʽ
class CSerialProtocol
{
private:
	CSerialProtocol();
	static CSerialProtocol* m_pSerial;
public:
	virtual ~CSerialProtocol();
	static CSerialProtocol *GetSerialProtocol();
public:
	HANDLE      m_hComDev;				//ͨ�Ŷ˿ھ��
	int	    	m_nerrnum;				//�������,���ڼ�⴮�ڴ����Ը�λ��
	BYTE		m_pRecvBufs[BUFFER_LENGTH];
	BYTE		m_pWriteBufs[BUFFER_LENGTH];

	//��ȡͨѶ�����߳�
	virtual int		SendData(BYTE *pb, int nsize);
	virtual int		ReadData(BYTE *pb, int nsize);
	BOOL			Connect(CConfigInfo &config);
public:

	CConfigInfo		m_config;
	virtual BOOL	IsConnect();
	virtual BOOL	Connect();			
	virtual void	Disconnect();
	virtual int		Send(unsigned char chPacketType, unsigned int shLength, unsigned char* pDatas);
	void			Packet(unsigned char chType, unsigned int len, unsigned char *pdata);
			void	SetParentWnd(HWND hWnd);

	BOOL	TestConnect(CConfigInfo &config);
	void	SetConfig(CConfigInfo &config)
	{ 
		m_config = config; 
	}
	CString GetConfigInfo();
	short	CalaCS(BYTE *pData, int iSize);
	void	InitComm();

	void stringToBytes(CString str,unsigned char *dat);
	void charToBytes(unsigned char *charArray,unsigned char *bitArray);
	unsigned char charToBin(unsigned char *dat) ;
};